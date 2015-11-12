#ifndef _PRIORITYQUEUE_H
#define _PRIORITYQUEUE_H

#include "MaxHeap.h"

namespace Seven
{
	// priority queue
	/*
	< requirements >
	1. type T should support default constructor
	2. type T should support operator =
	*/
	template<class T>
	class PriorityQueue
	{
	private:
		MaxHeap<T> * _heap;  // the max heap
		bool _isfixed;       // whether the length of queue is fixed
	public:
		// constructor
		PriorityQueue(size_t capacity, bool isfixed = false); // default constructor       (ok)

		// attribute
		bool empty()const;                                    // judge empty               (ok)
		bool full()const;                                     // judge full                (ok)
		size_t size()const;                                   // get current size          (ok)

		// clear
		void clear();                                         // clean the priority queue  (ok)
		~PriorityQueue();                                     // deconstructor             (ok)

		// CURD
		                                                      // push an element           (ok)
		bool push(const T & value, int(*compare)(const T & left, const T & right));
		T * peek();                                           // peek                      (ok)
		T top()const;                                         // top                       (ok)
		                                                      // pop                       (ok)
		bool pop(int(*compare)(const T & left, const T & right));
	};

	//----------------------------------------
	// implements:

	// default constructor
	/*
	"capacity" is the origin capacity of the priority queue
	"isfixed" represents that whether the queue is fixed-length
	*/
	template<class T>
	PriorityQueue<T>::PriorityQueue(size_t capacity, bool isfixed)
	{
		_heap = new MaxHeap<T>(capacity);
		_isfixed = isfixed;
	}

	// judge empty
	template<class T>
	bool PriorityQueue<T>::empty()const
	{
		return _heap->empty();
	}

	// judge full
	/*
	if queue is not fixed:
		anytime it is not full
	if queue is fixed and the inner heap full:
		it is full
	*/
	template<class T>
	bool PriorityQueue<T>::full()const
	{
		return _isfixed && _heap->full();
	}

	// current size of this priority queue
	template<class T>
	size_t PriorityQueue<T>::size()const
	{
		return _heap->size();
	}

	// clean the priority queue
	template<class T>
	void PriorityQueue<T>::clear()
	{
		_heap->clear();
	}

	// deconstructor
	template<class T>
	PriorityQueue<T>::~PriorityQueue()
	{
		delete _heap;
	}

	// push an element
	template<class T>
	bool PriorityQueue<T>::push(const T & value, int(*compare)(const T & left, const T & right))
	{
		if (this->full())
			return false;
		_heap->push(value, compare);
		return true;
	}

	// peek
	template<class T>
	T * PriorityQueue<T>::peek()
	{
		return _heap->peek();
	}

	// top
	template<class T>
	T PriorityQueue<T>::top()const
	{
		return _heap->top();
	}

	// pop
	template<class T>
	bool PriorityQueue<T>::pop(int(*compare)(const T & left, const T & right))
	{
		return _heap->pop(compare);
	}

}

#endif