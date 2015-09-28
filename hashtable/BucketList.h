#ifndef _BUCKETLIST_H
#define _BUCKETLIST_H

#include "BucketNode.h"

#include <iostream>
using std::cout;

namespace Seven
{
	// linkedlist,used in HashTable
        /*
	< requirements >
	1. type T should support default constructor
	2. type T should support operator =
	*/
	template<class T>
	class BucketList
	{
	private:
		BucketNode<T> * _head;  // addtional head node
		size_t _size;           // size of the list
	private:
		BucketNode<T> * find(const string & key)const;  // find corresponding node   (ok)
	public:
		// test:
		void print(void(*showT)(const T & value))const; // test print                (ok)

		// attributes:
		bool empty()const;                              // whether is empty          (ok)
		size_t size()const;                             // size of the list          (ok)

		// constructors:
		BucketList();                                   // default constructor       (ok)

		// about clear:
		void clear();                                   // clear the whole list      (ok)
		~BucketList();                                  // deconstructor             (ok)

		// CURD:
		void addPair(const Pair<T> & para);             // add or update a pair      (ok)
		T * search(const string & key)const;            // search value based on key (ok)
		bool rmPair(const string & key);                // remove value based on key (ok)
	};

	//----------------------------------------
	// implements:

	// test print
	/*
	inform: parament showT is a function pointor,used for print the value of type T
	1. test empty
	2. test size
	3. test real head node
	4. test the whole list
	*/
	template<class T>
	void BucketList<T>::print(void(*showT)(const T & value))const
	{
		cout << '\n';
		cout << (empty() ? "list is empty" : "list is not empty") << '\n';
		cout << "size: " << size() << '\n';
		if (_head->getNext())
		{
			cout << "real head:\n";
			_head->getNext()->print(showT);
		}
		else
			cout << "real head: null\n";
		cout << "the whole list:\n";
		const BucketNode<T> * p = _head->getNext();
		while (p)
		{
			p->print(showT);
			p = p->getNext();
		}
	}

	// whether the list is empty
	template<class T>
	bool BucketList<T>::empty()const
	{
		return _size == 0;
	}

	// get the size of the list
	template<class T>
	size_t BucketList<T>::size()const
	{
		return _size;
	}

	// default constructor
	/*
	1. create addtional head node
	2. make the size is zero
	*/
	template<class T>
	BucketList<T>::BucketList()
	{
		_head = new BucketNode<T>();
		_size = 0;
	}

	// clear the whole list
	/*
	while( size > 0 )
	{
	  use addtional head node to remove its next node
	  decrease the size
	}
	*/
	template<class T>
	void BucketList<T>::clear()
	{
		while (_size > 0)
		{
			_head->removeNext();
			_size--;
		}
	}

	// deconstructor
	/*
	1. clear the whole list
	2. delete the addtional head node
	*/
	template<class T>
	BucketList<T>::~BucketList()
	{
		clear();
		delete _head;
	}

	// find corresponding node based on key
	template<class T>
	BucketNode<T> * BucketList<T>::find(const string & key)const
	{
		BucketNode<T> * p = _head->getNext();
		while (p)
		{
			if (p->getPair()->getKey() == key)
				return p;
			p = p->getNext();
		}
		return nullptr;
	}

	// add or update a pair
	/*
	if current list has such a node which has the same key
	   then update its value
	else
	   then use the addtional head node to add a next node with the pair
	   increase the size
	*/
	template<class T>
	void BucketList<T>::addPair(const Pair<T> & para)
	{
		BucketNode<T> * p = find(para.getKey());
		if (p)
			p->getPair()->setValue(para.getValue());
		else
		{
			_head->addNext(para);
			_size++;
		}
	}

	// search value based on key
	/*
	if current list has such a node which has the same key
	   then return its value's address
	else
	   then return null
	*/
	template<class T>
	T * BucketList<T>::search(const string & key)const
	{
		BucketNode<T> * p = find(key);
		if (p)
			return p->getPair()->getValueAddress();
		return nullptr;
	}

	// remove value based on key
	/*
	1. note the addtional head node as "sentry"
	2. note the real head node as "p"
	3. while p is not null
	   {
	      if p.key == "key"
		  {
		     use "sentry" to remove its next node
			 decrease size
			 return true
		  }
		  move p to its next
		  move sentry to its next
	   }
	   return false
	*/
	template<class T>
	bool BucketList<T>::rmPair(const string & key)
	{
		BucketNode<T> * sentry = _head;
		BucketNode<T> * p = _head->getNext();
		while (p)
		{
			if (p->getPair()->getKey() == key)
			{
				sentry->removeNext();
				_size--;
				return true;
			}
			p = p->getNext();
			sentry = sentry->getNext();
		}
		return false;
	}

}

#endif