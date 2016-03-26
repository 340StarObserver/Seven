#ifndef _HASHPOOL_H
#define _HASHPOOL_H

#include "HashNode.h"

namespace Seven
{
	/*
	recycle pool for HashNode
	<requirements>
	1. type K,V should support default constructor
	2. type K,V should support operator =
	*/
	template<class K,class V>
	class HashPool
	{
	private:
		HashNode<K,V> * _top;		// point to the top node in the pool
	private:
		static HashPool<K,V> * _instance;	// the single instance
		HashPool();				// constructor
		~HashPool();				// deconstructor
	public:
		// get the single instance
		static HashPool<K,V> * getInstance();

		// delete the single instance
		static void destroyInstance();

		// push a node into pool
		void push(HashNode<K,V> * node);

		// push a node list into pool
		void push(HashNode<K,V> * begin,HashNode<K,V> * end);

		// fetch a node from pool
		HashNode<K,V> * fetch();
	};

	// --------------------------------------------------
	// implements

	// constructor
	template<class K,class V>
	HashPool<K,V>::HashPool()
	{
		_top=0;
	}


	// deconstructor
	template<class K,class V>
	HashPool<K,V>::~HashPool()
	{
		HashNode<K,V> * p=_top;
		while(p){
			_top=p->getNext();
			delete p;
			p=_top;
		}
	}


	// initialize the static single instance
	template<class K,class V>
	HashPool<K,V> * HashPool<K,V>::_instance=0;


	// get the single instance
	template<class K,class V>
	HashPool<K,V> * HashPool<K,V>::getInstance()
	{
		if(_instance==0)
			_instance=new HashPool();
		return _instance;
	}


	// delete the single instance
	template<class K,class V>
	void HashPool<K,V>::destroyInstance()
	{
		if(_instance){
			delete _instance;
			_instance=0;
		}
	}


	// push a node into pool
	template<class K,class V>
	void HashPool<K,V>::push(HashNode<K,V> * node)
	{
		if(node){
			node->setNext(_top);
			_top=node;
		}
	}


	// push a node list into pool
	/*
	begin : point to the head node of the list
	end : point to the tail node of the list
	*/
	template<class K,class V>
	void HashPool<K,V>::push(HashNode<K,V> * begin,HashNode<K,V> * end)
	{
		if(begin && end){
			end->setNext(_top);
			_top=begin;
		}
	}


	// fetch a node from pool
	/*
	if pool is not empty, it will return the top node
	if pool is empty, it will return NULL
	*/
	template<class K,class V>
	HashNode<K,V> * HashPool<K,V>::fetch()
	{
		HashNode<K,V> * p=_top;
		if(_top)
			_top=_top->getNext();
		return p;
	}

}

#endif