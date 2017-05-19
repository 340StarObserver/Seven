/*
 * Author 	: 	Lv Yang
 * Create 	: 	19 May 2017
 * Modify 	: 	19 May 2017
 * Version 	: 	1.0
 */

#ifndef _SEVEN_PRIORITYQUEUE_H
#define _SEVEN_PRIORITYQUEUE_H

#include "Queue.h"

namespace Seven
{
	template<class T>
	class PriorityQueue : public Queue<T>
	{
	private:
		/*
		 * 1. _elements[_capacity]
		 * 2. at the begin, _size is 0
		 */
		T * _elements;
		std::size_t _capacity;
		std::size_t _size;

		/*
		 * whether the queue's capacity can be changed
		 * _fixed = true  : can not be changed, when queue is full, it refuse new elements
		 * _fixed = false : can be changed, when queue is full, it will expand automically
		 */
		bool _fixed;

		/*
		 * strategy to compare two elements' priority, the return value :
		 * < 0 : lhs < rhs
		 * = 0 : lhs = rhs
		 * > 0 : lhs > rhs
		 */
		int (*_cmp)(const T & lhs, const T & rhs);

	private:
		// when queue is unfixed and full, expand the capacity
		void expand();

	public:
		PriorityQueue(int (*cmp)(const T & lhs, const T & rhs), std::size_t capacity = 16, bool fixed = false);

		virtual ~PriorityQueue();

		virtual void clear();

		virtual std::size_t size() const;

		virtual bool empty() const;

		virtual void push(const T & value);

		virtual void pop(bool mode = true);

		virtual T front(bool mode = true) const;
	};


	template<class T>
	PriorityQueue<T>::PriorityQueue(int (*cmp)(const T & lhs, const T & rhs), std::size_t capacity, bool fixed) : Queue<T>(), _capacity(capacity), _size(0), _fixed(fixed), _cmp(cmp)
	{
		_elements = new T[_capacity];
	}


	template<class T>
	PriorityQueue<T>::~PriorityQueue()
	{
		delete []_elements;
	}


	template<class T>
	void PriorityQueue<T>::expand()
	{
		T * tmp = new T[_capacity << 1];
		for(std::size_t i = 0; i < _capacity; i++)
			tmp[i] = _elements[i];
		delete []_elements;
		_elements = tmp;
		_capacity = (_capacity << 1);
	}


	template<class T>
	void PriorityQueue<T>::clear()
	{
		_size = 0;
	}


	template<class T>
	std::size_t PriorityQueue<T>::size() const
	{
		return _size;
	}


	template<class T>
	bool PriorityQueue<T>::empty() const
	{
		return _size == 0;
	}


	template<class T>
	void PriorityQueue<T>::push(const T & value)
	{
		if(_size == _capacity)
		{
			if(_fixed)
				return;
			expand();
		}

		std::size_t idx = _size++;
		while(idx != 0 && _cmp(_elements[(idx - 1) >> 1], value) < 0)
		{
			_elements[idx] = _elements[(idx - 1) >> 1];
			idx = (idx - 1) >> 1;
		}

		_elements[idx] = value;
	}


	template<class T>
	void PriorityQueue<T>::pop(bool mode)
	{
		if(_size == 0)
			return;

		// swap E[0], E[_size - 1]
		_size--;
		T t = _elements[0];
		_elements[0] = _elements[_size];
		_elements[_size] = t;

		// adjust the max heap
		T base = _elements[0];
		std::size_t j;
		for(j = 1; j < _size; j = (j << 1) + 1)
		{
			if(j + 1 < _size && _cmp(_elements[j], _elements[j + 1]) < 0)
				j++;
			if(_cmp(base, _elements[j]) >= 0)
				break;
			_elements[(j - 1) >> 1] = _elements[j];
		}
		_elements[(j - 1) >> 1] = base;
	}


	template<class T>
	T PriorityQueue<T>::front(bool mode) const
	{
		if(_size != 0)
			return _elements[0];
		throw QueueEmptyException();
	}

}

#endif
