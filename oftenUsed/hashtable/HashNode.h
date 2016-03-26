#ifndef _HASHNODE_H
#define _HASHNODE_H

namespace Seven
{
	/*
	Node used in buckets of hash table
	<requirements>
	1. type K,V should support default constructor
	2. type K,V should support operator =
	*/
	template<class K,class V>
	class HashNode
	{
	private:
		K _key;						// the key
		V _value;					// the value
		HashNode<K,V> * _next;			// the next node
	public:
		HashNode(const K & key,const V & value);	// constructor

		K getKey()const;				// get key
		void setKey(const K & key);			// set key

		V * getValue();					// get value
		void setValue(const V & value);		// set value

		HashNode<K,V> * getNext()const;		// get next node
		void setNext(HashNode<K,V> * next);	// set next node
	};

	// --------------------------------------------------
	// implements

	template<class K,class V>
	HashNode<K,V>::HashNode(const K & key,const V & value)
	{
		_key=key;
		_value=value;
		_next=0;
	}

	template<class K,class V>
	K HashNode<K,V>::getKey()const
	{
		return _key;
	}

	template<class K,class V>
	void HashNode<K,V>::setKey(const K & key)
	{
		_key=key;
	}

	template<class K,class V>
	V * HashNode<K,V>::getValue()
	{
		return &_value;
	}

	template<class K,class V>
	void HashNode<K,V>::setValue(const V & value)
	{
		_value=value;
	}

	template<class K,class V>
	HashNode<K,V> * HashNode<K,V>::getNext()const
	{
		return _next;
	}

	template<class K,class V>
	void HashNode<K,V>::setNext(HashNode<K,V> * next)
	{
		_next=next;
	}
	
}

#endif