#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include "BucketList.h"
#include "HashStrategy.h"
#include "STLHashStrategy.h"

namespace Seven
{
	// hash table
	template<class T>
	class HashTable
	{
	private:
		size_t _bucketNum;         // the number of buckets
		BucketList<T> * _buckets;  // the buckets
		HashStrategy * _strategy;  // the hash strategy
	public:
		// base functions:
		HashTable(size_t bucketNum = 512, HashStrategy * strategy = new STLHashStrategy());
		~HashTable();                                   // deconstructor            (ok)
		void clear();                                   // clear all buckets        (ok)

		// CURD:
		void set(const string & key, const T & value);  // add or update a pair     (ok)
		T * get(const string & key)const;               // get value based on key   (ok)
		bool remove(const string & key);                // remove pair based on key (ok)
	};

	//----------------------------------------
	// implements:

	// default constructor
	/*
	inform:
	1. bucketNum should be a bit large
	2. strategy can be any object which inherit the class "HashStrategy"
	*/
	template<class T>
	HashTable<T>::HashTable(size_t bucketNum, HashStrategy * strategy)
	{
		_bucketNum = (bucketNum > 0 ? bucketNum : 512);
		_buckets = new BucketList<T>[_bucketNum];
		_strategy = (strategy ? strategy : new STLHashStrategy());
	}

	// deconstructor
	/*
	1. delete all the buckets
	   ( in BucketList deconstructor ,it will clear the bucket )
	2. delete the hash strategy
	*/
	template<class T>
	HashTable<T>::~HashTable()
	{
		delete[]_buckets;
		delete _strategy;
	}

	// clear all the buckets of the hash table
	template<class T>
	void HashTable<T>::clear()
	{
		for (size_t i = 0; i < _bucketNum; i++)
			_buckets[i].clear();
	}

	// add or update a pair of (key,value)
	/*
	1. calculate a integer "index" based on the key
	2. use the corresponding bucket to add or update the pair
	*/
	template<class T>
	void HashTable<T>::set(const string & key, const T & value)
	{
		size_t index = _strategy->hash(key, _bucketNum);
		_buckets[index].addPair(Pair<T>(key, value));
	}

	// get value based on key
	/*
	1. calculate a integer "index" based on the key
	2. use the corresponding bucket to get the value
	*/
	template<class T>
	T * HashTable<T>::get(const string & key)const
	{
		size_t index = _strategy->hash(key, _bucketNum);
		return _buckets[index].search(key);
	}

	// remove pair based on key
	/*
	1. calculate a integer "index" based on the key
	2. use the corresponding bucket to remove the pair
	*/
	template<class T>
	bool HashTable<T>::remove(const string & key)
	{
		size_t index = _strategy->hash(key, _bucketNum);
		return _buckets[index].rmPair(key);
	}

}

#endif