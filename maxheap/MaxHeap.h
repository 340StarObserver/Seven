#ifndef _MAXHEAP_H
#define _MAXHEAP_H

#include <iostream>
using std::cout;

using std::_Copy_impl;

namespace Seven
{
	// max heap
	/*
	< requirements >
	1. type T should support default constructor
	2. type T should support operator =
	*/
	template<class T>
	class MaxHeap
	{
	private:
		T * _elements;     // elements of the max heap
		size_t _capacity;  // capacity of the max heap
		size_t _size;      // current size of the max heap
		void expand();     // expand the capacity
	public:
		// test
		void print(void(*show)(const T & value))const;    // test print           (ok)

		// constructor
		MaxHeap(size_t capacity = 16);                    // default constructor  (ok)
		MaxHeap(const MaxHeap<T> & heap);                 // copy constructor     (ok) 
		MaxHeap<T> & operator = (const MaxHeap<T> & heap);// operator = overwrite (ok)

		// clear
		void clear();                                     // clear the max heap   (ok)
		~MaxHeap();                                       // deconstructor        (ok)

		// attribute
		bool empty()const;                                // judge empty          (ok)
		size_t size()const;                               // get current size     (ok)

		// CURD
		                                                  // push an element      (ok)
		void push(const T & value, int(*compare)(const T & left, const T & right));
		T * peek();                                       // peek                 (ok)
		T top()const;                                     // top                  (ok)
		                                                  // pop                  (ok)
		bool pop(int(*compare)(const T & left, const T & right));
	};

	//----------------------------------------
	// implements:

	// test print
	template<class T>
	void MaxHeap<T>::print(void(*show)(const T & value))const
	{
		cout << "capacity: " << _capacity << '\n';
		cout << "size    : " << _size << '\n';
		cout << "elements:\n";
		for (size_t i = 1; i <= _size; i++)
			show(_elements[i]);
		cout << '\n';
	}


	// default constructor
	/*
	the _elements[0] is not used,because e1,e2,e3...,
	then e[i]'s parent is e[i/2]
	*/
	template<class T>
	MaxHeap<T>::MaxHeap(size_t capacity)
	{
		_capacity = (capacity > 0 ? capacity : 16);
		_elements = new T[_capacity + 1];
		_size = 0;
	}


	// copy constructor
	template<class T>
	MaxHeap<T>::MaxHeap(const MaxHeap<T> & heap)
	{
		_capacity = heap._capacity;
		_size = heap._size;
		_elements = new T[_capacity + 1];
		_Copy_impl(heap._elements, heap._elements + _size + 1, _elements);
	}


	// operator = overwrite
	template<class T>
	MaxHeap<T> & MaxHeap<T>::operator = (const MaxHeap<T> & heap)
	{
		if (this != &heap)
		{
			_capacity = heap._capacity;
			_size = heap._size;
			delete[]_elements;
			_elements = new T[_capacity + 1];
			_Copy_impl(heap._elements, heap._elements + _size + 1, _elements);
		}
		return *this;
	}


	// clear the max heap
	/*
	only change size,not delete the array
	*/
	template<class T>
	void MaxHeap<T>::clear()
	{
		_size = 0;
	}


	// deconstructor
	template<class T>
	MaxHeap<T>::~MaxHeap()
	{
		delete[]_elements;
	}


	// judge empty
	template<class T>
	bool MaxHeap<T>::empty()const
	{
		return _size == 0;
	}


	// get the current size of the max heap
	template<class T>
	size_t MaxHeap<T>::size()const
	{
		return _size;
	}


	// expand the capacity when capacity is not enough
	template<class T>
	void MaxHeap<T>::expand()
	{
		T * tmp = new T[_capacity * 2 + 1];
		_Copy_impl(_elements, _elements + _capacity + 1, tmp);
		_capacity = _capacity * 2;
		delete[]_elements;
		_elements = tmp;
	}


	// push an element
	template<class T>
	void MaxHeap<T>::push(const T & value, int(*compare)(const T & left, const T & right))
	{
		if (_size == _capacity)
			expand();
		size_t index = ++_size;
		while (index != 1 && compare(_elements[index / 2], value) < 0){
			_elements[index] = _elements[index / 2];
			index = index / 2;
		}
		_elements[index] = value;
	}


	// get the address of the top
	/*
	when use this function :
		try not to use its return value to modify its real value,
		to avoid destroy the characteristic of max heap.
	That is,make the value bigger is ok,while make the value is with risk
	*/
	template<class T>
	T * MaxHeap<T>::peek()
	{
		return (_size > 0 ? &_elements[1] : nullptr);
	}


	// get the top element
	/*
	not use exception,so when use this function,make sure the heap is not empty
	*/
	template<class T>
	T MaxHeap<T>::top()const
	{
		return _elements[1];
	}


	// pop from the max heap
	template<class T>
	bool MaxHeap<T>::pop(int(*compare)(const T & left, const T & right))
	{
		if (_size == 0)
			return false;
		T last = _elements[_size--];
		size_t p = 1, q = 2;
		while (q <= _size){
			if (q < _size && compare(_elements[q], _elements[q + 1]) < 0)
				q++;
			if (compare(last, _elements[q]) >= 0)
				break;
			_elements[p] = _elements[q];
			p = q;
			q = q * 2;
		}
		_elements[p] = last;
		return true;
	}

}

#endif