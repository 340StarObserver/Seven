#ifndef _QUEUE_H
#define _QUEUE_H

#include "LinkedList.h"

namespace Seven
{
	// queue
	/*
	< requirements >
	1. type T should support default constructor
	2. type T should support operator =
	*/
	template<class T>
	class Queue
	{
	private:
		LinkedList<T> * _list; // the linkedlist for agency
	public:
		// constructors:
		static Queue<T> * create();         // create a queue                    (ok)
		Queue();                            // default constructor               (ok)
		Queue(const Queue<T> & Q);          // copy constructor                  (ok)
		Queue<T> & operator = (const Queue<T> & Q); // operator =                (ok)

		// clears:
		void clear();                       // clear the whole queue             (ok)
		~Queue();                           // deconstructor                     (ok)

		// attributes:
		bool empty()const;                  // whether the queue is empty        (ok)
		size_t size()const;                 // get the size of the queue         (ok)

		// CURD:
		void push(const T & value);         // push a node to queue tail         (ok)
		bool pop();                         // pop a node from queue top         (ok)
		T * peek();                         // read the queue top                (ok)
		T front()const;                     // read the queue top                (ok)
		bool update(const T & value);       // update the queue top              (ok)
	};

	//----------------------------------------
	// implements:

	// create a queue
	template<class T>
	Queue<T> * Queue<T>::create()
	{
		return new Queue<T>();
	}


	// default constructor
	/*
	create a linkedlist, and assign the list for agency with it
	*/
	template<class T>
	Queue<T>::Queue()
	{
		_list = LinkedList<T>::create();
	}


	// copy constructor
	/*
	use the linkedlist for agency to copy
	*/
	template<class T>
	Queue<T>::Queue(const Queue<T> & Q)
	{
		_list = new LinkedList<T>(*(Q._list));
	}


	// operator =
	/*
	if current this object is not the parament "Q":
	{
	   then use the linkedlist for agency to exec operator =
	}
	return this object
	*/
	template<class T>
	Queue<T> & Queue<T>::operator = (const Queue<T> & Q)
	{
		if (this != &Q)
			_list->operator=(*(Q._list));
		return *this;
	}


	// clear the whole queue
	/*
	use the linkedlist for agency to clear
	*/
	template<class T>
	void Queue<T>::clear()
	{
		_list->clear();
	}


	// deconstructor
	/*
	1. clear the whole queue
	2. delete the linkedlist for agency
	inform: when delete the linkedlist,it will exec clear() inner,
	        so step 1 is not necessary,
	        that is to say,only step 2 is enough
	*/
	template<class T>
	Queue<T>::~Queue()
	{
		delete _list;
	}


	// whether the queue is empty
	template<class T>
	bool Queue<T>::empty()const
	{
		return _list->empty();
	}


	// get the size of the queue
	template<class T>
	size_t Queue<T>::size()const
	{
		return _list->size();
	}


	// push a node to queue tail
	/*
	use the linkedlist for agency to insert a node to the tail
	*/
	template<class T>
	void Queue<T>::push(const T & value)
	{
		_list->insertTail(value);
	}


	// pop a node from queue top
	/*
	use the linkedlist for agency to remove its real head node
	*/
	template<class T>
	bool Queue<T>::pop()
	{
		return _list->removeHead();
	}


	// read the queue top
	/*
	use the linkedlist for agency to get value of its real head node
	*/
	template<class T>
	T * Queue<T>::peek()
	{
		return _list->readHead();
	}


	// read the queue top
	/*
	different from "peek()",this function return value rather than address
	*/
	template<class T>
	T Queue<T>::front()const
	{
		return _list->head();
	}


	// update the queue top
	/*
	use the linkedlist for agency to update value of its real head node
	*/
	template<class T>
	bool Queue<T>::update(const T & value)
	{
		return _list->updateHead(value);
	}

}

#endif