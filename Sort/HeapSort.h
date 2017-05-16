/*
 * Author 	: 	Lv Yang
 * Create 	: 	16 May 2017
 * Modify 	: 	16 May 2017
 * Version 	: 	1.0
 */

#ifndef _HEAPSORT_H
#define _HEAPSORT_H

#include "Sort.h"

namespace Seven
{
	template<class T>
	class HeapSort : public Sort<T>
	{
	private:
		/*
		 * adjust a sub part of a whole maxheap
		 * ! -- pay attention to such three parameters
		 *     data : the start index is 0
		 *     root : the index of a sub heap
		 *     n    : the size of a whole maxheap, not a sub heap
		 */
		void adjust(T * data, std::size_t root, std::size_t n, int(*cmp)(const T & lhs, const T & rhs)) const;

		void swap(T & lhs, T & rhs) const;

	public:
		virtual ~HeapSort(){}

		virtual void sort(T * data, std::size_t n, int(*cmp)(const T & lhs, const T & rhs)) const;
	};


	template<class T>
	void HeapSort<T>::sort(T * data, std::size_t n, int(*cmp)(const T & lhs, const T & rhs)) const
	{
		std::size_t k, m = (n >> 1) - 1;
		for(k = 0; k <= m; k++)
			adjust(data, m - k, n, cmp);

		for(k = n - 1; k > 0; k--)
		{
			this->swap(data[0], data[k]);
			adjust(data, 0, k, cmp);
		}
	}


	template<class T>
	void HeapSort<T>::swap(T & lhs, T & rhs) const
	{
		T tmp = lhs;
		lhs = rhs;
		rhs = tmp;
	}


	template<class T>
	void HeapSort<T>::adjust(T * data, std::size_t root, std::size_t n, int(*cmp)(const T & lhs, const T & rhs)) const
	{
		T base = data[root];

		std::size_t j;
		for(j = (root << 1) + 1; j < n; j = (j << 1) + 1)
		{
			if(j + 1 < n && cmp(data[j], data[j + 1]) < 0)
				j++;
			if(cmp(base, data[j]) >= 0)
				break;
			data[(j - 1) >> 1] = data[j];
		}

		data[(j - 1) >> 1] = base;
	}

}

#endif
