#ifndef _BUCKETNODE_H
#define _BUCKETNODE_H

#include "Pair.h"

#include <iostream>
using std::cout;

namespace Seven
{
	// node used in bucketlist of a bucket,which is a part of HashTable
        /*
	< requirements >
	1. type T should support default constructor
	2. type T should support operator =
	*/
	template<class T>
	class BucketNode
	{
	private:
		Pair<T> _pair;           // the pair of (key,value) in the node
		BucketNode<T> * _next;   // address of its next node
	public:
		// test:
		void print(void(*showT)(const T & value))const;     // test this node                (ok)
		void printList(void(*showT)(const T & value))const; // test from this node to null   (ok)

		// get:
		Pair<T> * getPair();                                // get the pair                  (ok)
		BucketNode<T> * getNext()const;                     // get address of its next node  (ok)

		// set:
		void setPair(const Pair<T> & para);                 // set the pair                  (ok)
		void setNext(BucketNode<T> * next);                 // set its next node             (ok)

		// constructors:
		BucketNode();                                       // default constructor           (ok)
		BucketNode(const Pair<T> & para);                   // constructor with parament     (ok)

		// add:
		void addNext(const Pair<T> & para);                 // add a node,insert to its next (ok)

		// remove:
		void removeNext();                                  // remove its next node          (ok)
	};

	//----------------------------------------
	// implements:

	// test this node
	/*
	inform: parament showT is a function pointor,used for print the value of its pair
	1. print its (key,value)
	2. print address of itself
	3. print address of its next node
	*/
	template<class T>
	void BucketNode<T>::print(void(*showT)(const T & value))const
	{
		cout << "\nkey  : " << _pair.getKey() << '\n';
		cout << "value: ";
		showT(_pair.getValue());
		cout << "this address: " << static_cast<const void * const>(this) << '\n';
		cout << "next address: " << static_cast<void *>(_next) << "\n\n";
	}

	// print from itself to null
	/*
	inform: parament showT is a function pointor,used for print the value of its pair
	print itself
	print its next node
	print its next next node
	... until to the tail
	*/
	template<class T>
	void BucketNode<T>::printList(void(*showT)(const T & value))const
	{
		const BucketNode<T> * p = this;
		while (p)
		{
			p->print(showT);
			p = p->_next;
		}
	}

	// get the pair
	template<class T>
	Pair<T> * BucketNode<T>::getPair()
	{
		return &_pair;
	}

	// get address of its next node
	template<class T>
	BucketNode<T> * BucketNode<T>::getNext()const
	{
		return _next;
	}

	// set the pair
	template<class T>
	void BucketNode<T>::setPair(const Pair<T> & para)
	{
		_pair.setKey(para.getKey());
		_pair.setValue(para.getValue());
	}

	// set address of its next node
	template<class T>
	void BucketNode<T>::setNext(BucketNode<T> * next)
	{
		_next = next;
	}

	// default constructor
	template<class T>
	BucketNode<T>::BucketNode()
	{
		_next = nullptr;
	}

	// constructor using para,whose type is Pair<T>
	template<class T>
	BucketNode<T>::BucketNode(const Pair<T> & para)
	{
		_pair.setKey(para.getKey());
		_pair.setValue(para.getValue());
		_next = nullptr;
	}

	// add a node,insert to its next
	/*
	origin:     this --> next
	after add:  this --> newnode --> next
	*/
	template<class T>
	void BucketNode<T>::addNext(const Pair<T> & para)
	{
		BucketNode<T> * newnode = new BucketNode(para);
		BucketNode<T> * next = _next;
		_next = newnode;
		newnode->_next = next;
	}

	// remove its next node
	/*
	if its next node exists:
	{
	   that is for example: this --> next --> tmp
	   after rm its next  : this --> tmp
	}
	*/
	template<class T>
	void BucketNode<T>::removeNext()
	{
		if (_next)
		{
			BucketNode<T> * tmp = _next->_next;
			delete _next;
			_next = tmp;
		}
	}
}

#endif