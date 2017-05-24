/*
 * Author 	: 	Lv Yang
 * Create 	: 	24 May 2017
 * Modify 	: 	24 May 2017
 * Version 	: 	1.0
 */

#ifndef _SEVEN_MAXMINQUEUE_H
#define _SEVEN_MAXMINQUEUE_H

#include <cmath>

#include "Queue.h"

namespace Seven
{
	template<class T>
	class MaxMinQueue : public Queue<T>
	{
	private:
		/*
		 * 1. _elements[_capacity + 1], index really in use begin with 1
		 * 2. at the begin, _size is 0
		 */
		T * _elements;
		std::size_t _capacity;
		std::size_t _size;

		/*
		 * whether the queue's capacity can be changed
		 * _fixed = true  : refuse new element when full
		 * _fixed = false : expand automically when full
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

		// adjust max levels
		void adjustMax(std::size_t i, const T & value);

		// adjust min levels
		void adjustMin(std::size_t i, const T & value);

		// whether node i is in max level
		bool is_max_level(std::size_t i) const;

	public:
		MaxMinQueue(int (*cmp)(const T & lhs, const T & rhs), std::size_t capacity = 16, bool fixed = false);

		virtual ~MaxMinQueue();

		virtual void clear();

		virtual std::size_t size() const;

		virtual bool empty() const;

		virtual void push(const T & value);

		/*
		 * mode = true  : choose the max priority one
		 * mode = false : choose the min priority one
		 */

		virtual void pop(bool mode = true);

		virtual T front(bool mode = true) const;
	};


	template<class T>
	MaxMinQueue<T>::MaxMinQueue(int (*cmp)(const T & lhs, const T & rhs), std::size_t capacity, bool fixed) : Queue<T>(), _capacity(capacity), _size(0), _fixed(fixed), _cmp(cmp)
	{
		_elements = new T[_capacity + 1];
	}


	template<class T>
	MaxMinQueue<T>::~MaxMinQueue()
	{
		delete []_elements;
	}


	template<class T>
	void MaxMinQueue<T>::expand()
	{
		T * tmp = new T[(_capacity << 1) + 1];
		for(std::size_t i = 1; i <= _capacity; i++)
			tmp[i] = _elements[i];
		delete []_elements;
		_elements = tmp;
		_capacity = (_capacity << 1);
	}


	template<class T>
	void MaxMinQueue<T>::clear()
	{
		_size = 0;
	}


	template<class T>
	std::size_t MaxMinQueue<T>::size() const
	{
		return _size;
	}


	template<class T>
	bool MaxMinQueue<T>::empty() const
	{
		return _size == 0;
	}


	template<class T>
	T MaxMinQueue<T>::front(bool mode) const
	{
		if(_size == 0)
			throw QueueEmptyException();

		if(mode || _size == 1)
			return _elements[1];

		if(_size == 2 || _cmp(_elements[2], _elements[3]) <= 0)
			return _elements[2];
		
		return _elements[3];
	}


	template<class T>
	void MaxMinQueue<T>::push(const T & value)
	{
		// if queue is full
		if(_size == _capacity)
		{
			if(_fixed)
				return;
			expand();
		}

		// p = new-node's parent
		std::size_t p = (++_size) >> 1;

		// if queue is empty
		if(p == 0)
		{
			_elements[1] = value;
			return;
		}

		if(is_max_level(p))
		{
			if(_cmp(_elements[p], value) < 0)
			{
				_elements[_size] = _elements[p];
				adjustMax(p, value);
			}
			else
				adjustMin(_size, value);
		}
		else
		{
			if(_cmp(value, _elements[p]) < 0)
			{
				_elements[_size] = _elements[p];
				adjustMin(p, value);
			}
			else
				adjustMax(_size, value);
		}
	}


	template<class T>
	void MaxMinQueue<T>::adjustMax(std::size_t i, const T & value)
	{
		for(std::size_t gp = i >> 2; gp > 0 && _cmp(_elements[gp], value) < 0; gp = gp >> 2)
		{
			_elements[i] = _elements[gp];
			i = gp;
		}
		_elements[i] = value;
	}


	template<class T>
	void MaxMinQueue<T>::adjustMin(std::size_t i, const T & value)
	{
		for(std::size_t gp = i >> 2; gp > 0 && _cmp(value, _elements[gp]) < 0; gp = gp >> 2)
		{
			_elements[i] = _elements[gp];
			i = gp;
		}
		_elements[i] = value;
	}


	template<class T>
	bool MaxMinQueue<T>::is_max_level(std::size_t i) const
	{
		// log2(i) is even
		i = std::size_t(log10(i) / log10(2));
		i = i & 1;
		return i == 0;
	}


	template<class T>
	void MaxMinQueue<T>::pop(bool mode)
	{
		// wait implement ...
	}

}

#endif
