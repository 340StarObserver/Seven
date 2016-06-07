#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include "HashPool.h"

#include <cstring>
using std::memset;

/*
I come up of two improve plans, if you are interested in, you can realize them, they are:

1.	when visit(get or replace) one node, you can move this node to the head of that linked-list.
Because in real environment, our program tend to visit several data very frequently. An advantage of
this method is that you can find the data faster in the future.

2.	combine N linked-list into one linkedlist. And in logic, use subsection, it can be seen as N lists.
One advantage is you can deconstruct this hashtable faster, because you can push this big list into the
HashPool with O(1) cost. Another advantage is your iterator will become easier and faster.
*/

/*
我想了两个提升性能的方案，如果你有兴趣，可以实现它们，它们是:
1.	当访问(查询or更新)某个结点的时候，你可以把这个结点移动到那条链表的头部。因为在真实环境下，程序往往会
很频繁地访问少数的几项数据，这个方案的一个好处就是之后你可以更快地找到那些高频的数据。

2.	把N条链表合成为一个大链表。但是又要保证在"逻辑上"仍然有N条链表，怎么办的?可以用分段的方法。
比如，在构造哈希表的时候，就立即创建N个结点并把它们串成一个链表，形如:
node0 -> node1 -> node2 ... -> nodeN-1
然后创建一些指针，比如p0指向node0，q0指向node1，则p0到q0之间的这一段就是逻辑上的第一条链表的空间，
之后往第一个桶里插入数据就直接插入到这一段区间里。
这样的好处有两个:
第一个好处是在析构哈希表的时候，你可以把整个一条大链表在O(1)时间内接到回收池里，而你在原来有N条链表时候则需要0(N)。
第二个好处是你的迭代器的遍历变得更简单，真的变成了一条链表的遍历。
*/

// here is the current version
namespace Seven
{
	// template of hash table
	/*
	< requirements >
	1. type K,V should support default constructor
	2. type K,V should support operator =
	*/
	template<class K,class V>
	class HashTable
	{
	private:
		unsigned int (*_hash)(const K & key,unsigned int range);	// hash strategy
		int (*_compare)(const K & left,const K & right);		// key compare strategy

		unsigned int _bucketNum;		// the number of buckets
		HashNode<K,V> ** _heads;		// point to head node of each bucket
		HashNode<K,V> ** _tails;		// point to tail node of each bucket
	private:
		// constructor
		HashTable(unsigned int bucketNum,unsigned int (*hash)(const K & key,unsigned int range),int (*compare)(const K & left,const K & right));
	public:
		// create a new instance
		static HashTable<K,V> * newInstance(unsigned int bucketNum,unsigned int (*hash)(const K & key,unsigned int range),int (*compare)(const K & left,const K & right));

		// deconstructor
		~HashTable();

		// get value by a given key
		V * get(const K & key);

		// put a <key,value> into table
		void put(const K & key,const V & value);

		// replace the old value with a new value when key exists
		bool replace(const K & key,const V & value);

		// add a new <key,value> when key not exists
		bool add(const K & key,const V & value);

		// remove a <key,value>
		void remove(const K & key);

		// declare Iterator
		class Iterator;

		// get the iterator
		Iterator iterator(){
			return Iterator(_bucketNum,_heads);
		}

		// Iterator
		class Iterator
		{
		private:
			unsigned int _bucketNum;	// the number of buckets of hashtable
			HashNode<K,V> ** _heads;	// the heads of each bucket

			unsigned int _curBucket;	// now iterator is in which bucket
			HashNode<K,V> * _curPos;	// now iterator point to which node

			unsigned int _nextBucket;	// next step,iterator will be in which bucket
			HashNode<K,V> * _nextPos;	// next step,iterator will point to which node
		public:
			// constructor
			Iterator(unsigned int bucketNum,HashNode<K,V> ** heads);

			// whether has next element
			bool hasNext()const;

			// go to the next position
			void toNext();

			// get key of current position
			K getKey()const;

			// get value of current position
			V * getValue();
		};

	};

	// --------------------------------------------------
	// implements

	// constructor
	/*
	input
	{
		bucketNum : the number of buckets,recommend a large prime such as 1023
		hash           : point to a function that transfer a key into a integer
		compare     : point to a function that compare two keys
			// compare(left,right)<0 : left<right
			// compare(left,right)=0 : left=right
			// compare(left,right)>0 : left>right
	}
	*/
	template<class K,class V>
	HashTable<K,V>::HashTable(unsigned int bucketNum,unsigned int (*hash)(const K & key,unsigned int range),int (*compare)(const K & left,const K & right))
	{
		_hash=hash;
		_compare=compare;
		_bucketNum=bucketNum;
		_heads=new HashNode<K,V>*[_bucketNum];
		_tails=new HashNode<K,V>*[_bucketNum];
		memset(_heads,0,sizeof(HashNode<K,V> *)*_bucketNum);
		memset(_tails,0,sizeof(HashNode<K,V> *)*_bucketNum);
	}


	// create a new instance
	template<class K,class V>
	HashTable<K,V> * HashTable<K,V>::newInstance(unsigned int bucketNum,unsigned int (*hash)(const K & key,unsigned int range),int (*compare)(const K & left,const K & right))
	{
		return new HashTable<K,V>(bucketNum,hash,compare);
	}


	// deconstructor
	/*
	1. push each bucket(the whole linkedlist) into the Node recycle pool
	2. delete head array & tail array
	*/
	template<class K,class V>
	HashTable<K,V>::~HashTable()
	{
		HashPool<K,V> * pool=HashPool<K,V>::getInstance();
		for(unsigned int i=0;i<_bucketNum;i++)
			pool->push(_heads[i],_tails[i]);
		delete []_heads;
		delete []_tails;
	}


	// put a <key,value> into table
	/*
	if key exists, then update the value
	if key not exist, then insert this <key,value>
	method:
	{
		1. calculate the <key,value> should be in which bucket
		2. traverse that bucket, if find the same key, then update the value and return
		3. fetch a node from Node pool and set its key,value
		4. add this node to the head of that bucket
	}
	*/
	template<class K,class V>
	void HashTable<K,V>::put(const K & key,const V & value)
	{
		unsigned int index=_hash(key,_bucketNum);

		HashNode<K,V> * p=_heads[index];
		while(p){
			if(_compare(key,p->getKey())==0){
				p->setValue(value);
				return;
			}
			p=p->getNext();
		}

		p=HashPool<K,V>::getInstance()->fetch();
		if(p==0)
			p=new HashNode<K,V>(key,value);
		else{
			p->setKey(key);
			p->setValue(value);
		}

		if(_heads[index]==0)
			_tails[index]=p;
		p->setNext(_heads[index]);
		_heads[index]=p;
	}


	// get value by a given key
	/*
	if key exists, then it will return the address of value
	if key not exist, then it will return NULL
	*/
	template<class K,class V>
	V * HashTable<K,V>::get(const K & key)
	{
		unsigned int index=_hash(key,_bucketNum);
		HashNode<K,V> * p=_heads[index];
		while(p){
			if(_compare(key,p->getKey())==0)
				return p->getValue();
			p=p->getNext();
		}
		return 0;
	}


	// replace the old value with a new value when key exists
	/*
	if key exists, then it will update the value and return true
	if key not exist, then it will return false
	*/
	template<class K,class V>
	bool HashTable<K,V>::replace(const K & key,const V & value)
	{
		unsigned int index=_hash(key,_bucketNum);
		HashNode<K,V> * p=_heads[index];
		while(p){
			if(_compare(key,p->getKey())==0){
				p->setValue(value);
				return true;
			}
			p=p->getNext();
		}
		return false;
	}


	// add a new <key,value> when key not exists
	/*
	if key exists, then it will return false
	if key not exist, then it will insert this <key,value> and return true
	*/
	template<class K,class V>
	bool HashTable<K,V>::add(const K & key,const V & value)
	{
		unsigned int index=_hash(key,_bucketNum);

		HashNode<K,V> * p=_heads[index];
		while(p){
			if(_compare(key,p->getKey())==0)
				return false;
			p=p->getNext();
		}

		p=HashPool<K,V>::getInstance()->fetch();
		if(p==0)
			p=new HashNode<K,V>(key,value);
		else{
			p->setKey(key);
			p->setValue(value);
		}

		if(_heads[index]==0)
			_tails[index]=p;
		p->setNext(_heads[index]);
		_heads[index]=p;
		return true;
	}


	// remove a <key,value>
	/*
	1. calculate the <key,value> should be in which bucket
	2. search in that bucket to find the location of this <key,value>
	3. push that node into recycle pool
	4. reconnect that bucket
	*/
	template<class K,class V>
	void HashTable<K,V>::remove(const K & key)
	{
		unsigned int index=_hash(key,_bucketNum);
		HashNode<K,V> * p=_heads[index];
		if(p==0)
			return;

		if(_compare(key,p->getKey())==0){
			_heads[index]=p->getNext();
			if(_heads[index]==0)
				_tails[index]=0;
			HashPool<K,V>::getInstance()->push(p);
			return;
		}

		HashNode<K,V> * pp=p;
		p=p->getNext();
		while(p && _compare(key,p->getKey())!=0){
			pp=p;
			p=p->getNext();
		}
		if(p){
			pp->setNext(p->getNext());
			if(p->getNext()==0)
				_tails[index]=pp;
			HashPool<K,V>::getInstance()->push(p);
		}
	}


	// --------------------------------------------------
	// Iterator implements

	// constructor
	/*
	1. make curPos point to NULL
	2. make nextPos point to the first node of the hashtable
	*/
	template<class K,class V>
	HashTable<K,V>::Iterator::Iterator(unsigned int bucketNum,HashNode<K,V> ** heads)
	{
		_bucketNum=bucketNum;
		_heads=heads;
		_curBucket=0;
		_curPos=0;
		_nextPos=0;
		for(_nextBucket=0;_nextBucket<_bucketNum;_nextBucket++){
			if(_heads[_nextBucket]){
				_nextPos=_heads[_nextBucket];
				break;
			}
		}
	}

	// whether has next element
	template<class K,class V>
	bool HashTable<K,V>::Iterator::hasNext()const
	{
		return _nextPos!=0;
	}

	// go the the next position
	template<class K,class V>
	void HashTable<K,V>::Iterator::toNext()
	{
		_curBucket=_nextBucket;
		_curPos=_nextPos;
		_nextPos=_nextPos->getNext();
		if(_nextPos==0){
			for(_nextBucket=_curBucket+1;_nextBucket<_bucketNum;_nextBucket++){
				if(_heads[_nextBucket]){
					_nextPos=_heads[_nextBucket];
					break;
				}
			}
		}
	}

	// get key of current position
	template<class K,class V>
	K HashTable<K,V>::Iterator::getKey()const
	{
		return _curPos->getKey();
	}

	// get value of current position
	template<class K,class V>
	V * HashTable<K,V>::Iterator::getValue()
	{
		return _curPos->getValue();
	}

}

#endif
