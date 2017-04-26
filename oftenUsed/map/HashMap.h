/*
Author 		: 	Lv Yang
Created 	: 	26 April 2017
Modified 	: 	26 April 2017
Version 	: 	1.0
*/

#ifndef SEVEN_HASHMAP_H
#define SEVEN_HASHMAP_H

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
}

#endif
