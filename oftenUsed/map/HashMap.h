/*
Author 		: 	Lv Yang
Created 	: 	26 April 2017
Modified 	: 	27 April 2017
Version 	: 	1.0
*/

#ifndef SEVEN_HASHMAP_H
#define SEVEN_HASHMAP_H

#include <cstring>

#include "Map.h"

namespace Seven
{
	/*
	 * Linked Node in HashMap
	 * < require >
	 * 1. type K, V support default constructor
	 * 2. type K, V support copy constructor
	 * 3. type K, V support operator =
	 */
	template<class K, class V>
	class HashNode
	{
	private:
		K _key;
		V _value;
		HashNode<K, V> * _next;
	public:
		HashNode();

		HashNode(const K & key, const V & value);

		K getKey()const;

		V getValue()const;

		HashNode<K, V> * getNext()const;

		void setKey(const K & key);

		void setValue(const V & value);
		
		void setNext(HashNode<K, V> * next);
	};

	template<class K, class V>
	HashNode<K, V>::HashNode()
	{

	}

	template<class K, class V>
	HashNode<K, V>::HashNode(const K & key, const V & value) : _key(key), _value(value), _next(NULL)
	{

	}

	template<class K, class V>
	K HashNode<K, V>::getKey()const
	{
		return _key;
	}

	template<class K, class V>
	V HashNode<K, V>::getValue()const
	{
		return _value;
	}

	template<class K, class V>
	HashNode<K, V> * HashNode<K, V>::getNext()const
	{
		return _next;
	}

	template<class K, class V>
	void HashNode<K, V>::setKey(const K & key)
	{
		_key = key;
	}

	template<class K, class V>
	void HashNode<K, V>::setValue(const V & value)
	{
		_value = value;
	}

	template<class K, class V>
	void HashNode<K, V>::setNext(HashNode<K, V> * next)
	{
		_next = next;
	}


	/*
	 * Memory Pool for HashNode
	 * < require >
	 * 1. type K, V support default constructor
	 * 2. type K, V support copy constructor
	 * 3. type K, V support operator =
	 */
	template<class K, class V>
	class HashPool
	{
	private:
		HashNode<K, V> * _head; 		// the head node of this list
	private:
		static std::size_t InitSize; 		// the init size of this list
		static HashPool<K, V> * _instance; 	// the single instance
		HashPool();
		~HashPool();
	public:
		// get the single instance
		static HashPool<K, V> * getInstance();

		// delete the single instance
		static void destroyInstance();

		// reset the init size
		static void setInitSize(std::size_t initsize);

		// push a node into pool
		void push(HashNode<K, V> * node);

		// push a whole list into pool
		void push(HashNode<K, V> * begin, HashNode<K, V> * end);

		// fetch a node from pool
		HashNode<K, V> * fetch();
	};

	template<class K, class V>
	std::size_t HashPool<K, V>::InitSize = 0;

	template<class K, class V>
	HashPool<K, V> * HashPool<K, V>::_instance = NULL;

	template<class K, class V>
	HashPool<K, V>::HashPool()
	{
		_head = NULL;
		for(std::size_t i = 0; i < InitSize; i++){
			HashNode<K, V> * p = new HashNode<K, V>();
			p->setNext(_head);
			_head = p;
		}
	}

	template<class K, class V>
	HashPool<K, V>::~HashPool()
	{
		HashNode<K, V> * p = _head;
		while(p){
			_head = p->getNext();
			delete p;
			p = _head;
		}
	}

	template<class K, class V>
	HashPool<K, V> * HashPool<K, V>::getInstance()
	{
		if(_instance == NULL)
			_instance = new HashPool();
		return _instance;
	}

	template<class K, class V>
	void HashPool<K, V>::destroyInstance()
	{
		if(_instance){
			delete _instance;
			_instance = NULL;
		}
	}

	template<class K, class V>
	void HashPool<K, V>::setInitSize(std::size_t initsize)
	{
		InitSize = initsize;
	}

	template<class K, class V>
	void HashPool<K, V>::push(HashNode<K, V> * node)
	{
		if(node){
			node->setNext(_head);
			_head = node;
		}
	}

	template<class K, class V>
	void HashPool<K, V>::push(HashNode<K, V> * begin, HashNode<K, V> * end)
	{
		if(begin && end){
			end->setNext(_head);
			_head = begin;
		}
	}

	template<class K, class V>
	HashNode<K, V> * HashPool<K, V>::fetch()
	{
		if(_head){
			HashNode<K, V> * p = _head;
			_head = _head->getNext();
			p->setNext(NULL);
			return p;
		}
		return NULL;
	}


	/*
	 * HashMap
	 * < require >
	 * 1. type K, V support default constructor
	 * 2. type K, V support copy constructor
	 * 3. type K, V support operator =
	 * 4. you should provide a function to calculate hashcode
	 *     // 0 <= hashcode < range
	 * 5. you should provide a function to compare two keys
	 *     // lvs < rvs : return -1
	 *     // lvs = rvs : return 0
	 *     // lvs > rvs : return 1
	 */
	template<class K, class V>
	class HashMap : public Map<K, V>
	{
	private:
		// algorithm for calc hash code
		std::size_t (*_hash)(const K & key, std::size_t range);

		// algorithm for compare two keys
		int (*_cmp)(const K & lvs, const K & rvs);
	private:
		// the number of buckets
		std::size_t _bucketNum;

		// array with each element points to a bucket's head
		HashNode<K, V> ** _heads;

		// array with each element points to a bucket's tail
		HashNode<K, V> ** _tails;
	private:
		HashMap(std::size_t bucketNum, std::size_t (*hash)(const K & key, std::size_t range), int (*cmp)(const K & lvs, const K & rvs));
	public:
		static HashMap<K, V> * create(std::size_t bucketNum, std::size_t (*hash)(const K & key, std::size_t range), int (*cmp)(const K & lvs, const K & rvs));
		
		virtual ~HashMap();

		virtual V get(const K & key)const;

		virtual void set(const K & key, const V & value);

		virtual bool exist(const K & key)const;

		virtual void remove(const K & key);
	};

	template<class K, class V>
	HashMap<K, V>::HashMap(std::size_t bucketNum, std::size_t (*hash)(const K & key, std::size_t range), int (*cmp)(const K & lvs, const K & rvs))
	{
		_hash = hash;
		_cmp = cmp;
		_bucketNum = bucketNum;
		_heads = new HashNode<K, V>*[_bucketNum];
		_tails = new HashNode<K, V>*[_bucketNum];
		std::memset(_heads, 0, sizeof(HashNode<K, V> *) * _bucketNum);
		std::memset(_tails, 0, sizeof(HashNode<K, V> *) * _bucketNum);
	}

	template<class K, class V>
	HashMap<K, V> * HashMap<K, V>::create(std::size_t bucketNum, std::size_t (*hash)(const K & key, std::size_t range), int (*cmp)(const K & lvs, const K & rvs))
	{
		return new HashMap<K, V>(bucketNum, hash, cmp);
	}

	template<class K, class V>
	HashMap<K, V>::~HashMap()
	{
		HashPool<K, V> * pool = HashPool<K, V>::getInstance();
		for(std::size_t i = 0; i < _bucketNum; i++)
			pool->push(_heads[i], _tails[i]);
		delete []_heads;
		delete []_tails;
	}

	template<class K, class V>
	V HashMap<K, V>::get(const K & key)const
	{
		std::size_t idx = _hash(key, _bucketNum);
		HashNode<K, V> * p = _heads[idx];
		while(p){
			if(_cmp(key, p->getKey()) == 0)
				return p->getValue();
			p = p->getNext();
		}
		throw KeyNotFoundException();
	}

	template<class K, class V>
	bool HashMap<K, V>::exist(const K & key)const
	{
		std::size_t idx = _hash(key, _bucketNum);
		HashNode<K, V> * p = _heads[idx];
		while(p){
			if(_cmp(key, p->getKey()) == 0)
				return true;
			p = p->getNext();
		}
		return false;
	}

	template<class K, class V>
	void HashMap<K, V>::set(const K & key, const V & value)
	{
		std::size_t idx = _hash(key, _bucketNum);

		// key exist, only need to update value
		HashNode<K, V> * p = _heads[idx];
		while(p){
			if(_cmp(key, p->getKey()) == 0){
				p->setValue(value);
				return;
			}
			p = p->getNext();
		}

		// key not exist, first, create a new node
		p = HashPool<K, V>::getInstance()->fetch();
		if(p == NULL)
			p = new HashNode<K, V>(key, value);
		else{
			p->setKey(key);
			p->setValue(value);
		}

		// key not exist, second, insert this new node at the corresponding linkedlist's head
		if(_heads[idx] == NULL)
			_tails[idx] = p;
		p->setNext(_heads[idx]);
		_heads[idx] = p;
	}

	template<class K, class V>
	void HashMap<K, V>::remove(const K & key)
	{
		std::size_t idx = _hash(key, _bucketNum);

		// 1. if empty linkedlist
		HashNode<K, V> * p = _heads[idx];
		if(p == NULL)
			return;

		// 2. if linkedlist's head is to be removed
		if(_cmp(key, p->getKey()) == 0){
			_heads[idx] = p->getNext();
			if(_heads[idx] == NULL)
				_tails[idx] = NULL;
			HashPool<K, V>::getInstance()->push(p);
			return;
		}

		// 3. if linkedlist's center or tail is to be removed
		HashNode<K, V> * pp = p;
		p = p->getNext();
		while(p && _cmp(key, p->getKey()) != 0){
			pp = p;
			p = p->getNext();
		}
		if(p){
			pp->setNext(p->getNext());
			if(p->getNext() == NULL)
				_tails[idx] = pp;
			HashPool<K, V>::getInstance()->push(p);
		}
	}

}

#endif
