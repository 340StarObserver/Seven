/*
 * Author 	: 	Lv Yang
 * Create 	: 	24 May 2017
 * Modify 	: 	25 May 2017
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
		/*
		 * following several functions used in push
		 */

		// when queue is unfixed and full, expand the capacity
		void expand();

		// adjust max levels
		void adjustMax(std::size_t i, const T & value);

		// adjust min levels
		void adjustMin(std::size_t i, const T & value);

		// whether node i is in max level
		bool is_max_level(std::size_t i) const;

	private:
		/*
		 * following several functions used in pop
		 */

		// pop max
		void pop_max();

		// pop min
		void pop_min();

		// swap two elements
		void swap(T & lhs, T & rhs);

		// idx of the max in i's childs, return 0 if not exist
		std::size_t child_max(std::size_t i) const;

		// idx of the min in i's childs, return 0 if not exist
		std::size_t child_min(std::size_t i) const;

		// idx of the max in i's grand childs, return 0 if not exist
		std::size_t grand_max(std::size_t i) const;

		// idx of the min in i's grand childs, return 0 if not exist
		std::size_t grand_min(std::size_t i) const;

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
		// i is in max level  <==>  log2(i) is even
		i = std::size_t(std::log10(i) / std::log10(2));
		i = i & 1;
		return i == 0;
	}


	template<class T>
	void MaxMinQueue<T>::pop(bool mode)
	{
		if(mode)
			pop_max();
		else
			pop_min();
	}


	template<class T>
	void MaxMinQueue<T>::swap(T & lhs, T & rhs)
	{
		T tmp = lhs;
		lhs = rhs;
		rhs = tmp;
	}


	template<class T>
	std::size_t MaxMinQueue<T>::child_max(std::size_t i) const
	{
		std::size_t c = (i << 1);
		if(i > 0 && c <= _size)
		{
			if(c + 1 > _size || _cmp(_elements[c], _elements[c + 1]) >= 0)
				return c;
			return c + 1;
		}
		return 0;
	}


	template<class T>
	std::size_t MaxMinQueue<T>::child_min(std::size_t i) const
	{
		std::size_t c = (i << 1);
		if(i > 0 && c <= _size)
		{
			if(c + 1 > _size || _cmp(_elements[c], _elements[c + 1]) <= 0)
				return c;
			return c + 1;
		}
		return 0;
	}


	template<class T>
	std::size_t MaxMinQueue<T>::grand_max(std::size_t i) const
	{
		std::size_t c = (i << 2);
		if(i > 0 && c <= _size)
		{
			std::size_t p = c;
			for(i = c + 1; i <= c + 3 && i <= _size; i++)
			{
				if(_cmp(_elements[p], _elements[i]) < 0)
					p = i;
			}
			return p;
		}
		return 0;
	}


	template<class T>
	std::size_t MaxMinQueue<T>::grand_min(std::size_t i) const
	{
		std::size_t c = (i << 2);
		if(i > 0 && c <= _size)
		{
			std::size_t p = c;
			for(i = c + 1; i <= c + 3 && i <= _size; i++)
			{
				if(_cmp(_elements[p], _elements[i]) > 0)
					p = i;
			}
			return p;
		}
		return 0;
	}


	template<class T>
	void MaxMinQueue<T>::pop_max()
	{
		if(_size == 0)
			return;

		_elements[1] = _elements[_size--];

		std::size_t p = 1, q;
		bool w = true;
		while(w)
		{
			w = false;

			q = child_max(p);
			if(q != 0 && _cmp(_elements[p], _elements[q]) < 0)
				this->swap(_elements[p], _elements[q]);

			q = grand_max(p);
			if(q != 0 && _cmp(_elements[p], _elements[q]) < 0)
			{
				this->swap(_elements[p], _elements[q]);
				p = q;
				w = true;
			}
		}
	}


	template<class T>
	void MaxMinQueue<T>::pop_min()
	{
		if(_size <= 1)
		{
			_size = 0;
			return;
		}

		std::size_t p = child_min(1);
		_elements[p] = _elements[_size--];

		std::size_t q;
		bool w = true;
		while(w)
		{
			w = false;

			q = child_min(p);
			if(q != 0 && _cmp(_elements[p], _elements[q]) > 0)
				this->swap(_elements[p], _elements[q]);

			q = grand_min(p);
			if(q != 0 && _cmp(_elements[p], _elements[q]) > 0)
			{
				this->swap(_elements[p], _elements[q]);
				p = q;
				w = true;
			}
		}
	}

}

#endif
