/*
 * Author 	: 	Lv Yang
 * Create 	: 	16 May 2017
 * Modify 	: 	16 May 2017
 * Version 	: 	1.0
 */

#ifndef _MERGESORT_H
#define _MERGESORT_H

#include "Sort.h"

namespace Seven
{
	template<class T>
	class MergeSort : public Sort<T>
	{
	private:
		/*
		 * mergesort a list by a given step
		 * !-- for example :
		 *     n = 8, step = 2
		 *     merge datafrom[0:1] & datafrom[2:3] -> datato[0:3]
		 *     merge datafrom[4:5] & datafrom[6:7] -> datato[4:7]
		 */
		void work(T * datafrom, T * datato, std::size_t n, std::size_t step, int(*cmp)(const T & lhs, const T & rhs)) const;

		/*
		 * merge two sorted sub lists
		 * from : datafrom[l:m], datafrom[m+1:r]
		 * to   : datato[l:n]
		 */
		void merge(T * datafrom, T * datato, std::size_t l, std::size_t m, std::size_t r, int(*cmp)(const T & lhs, const T & rhs)) const;

	public:
		virtual ~MergeSort(){}

		virtual void sort(T * data, std::size_t n, int(*cmp)(const T & lhs, const T & rhs)) const;
	};


	template<class T>
	void MergeSort<T>::sort(T * data, std::size_t n, int(*cmp)(const T & lhs, const T & rhs)) const
	{
		T * tmp = new T[n];
		for(std::size_t l = 1; l < n; l = (l << 1))
		{
			work(data, tmp, n, l, cmp);
			l = (l << 1);
			work(tmp, data, n, l, cmp);
		}
		delete []tmp;
	}


	template<class T>
	void MergeSort<T>::merge(T * datafrom, T * datato, std::size_t l, std::size_t m, std::size_t r, int(*cmp)(const T & lhs, const T & rhs)) const
	{
		std::size_t c = l;
		std::size_t p1 = l;
		std::size_t p2 = m + 1;

		while(p1 <= m && p2 <= r)
		{
			if(cmp(datafrom[p1], datafrom[p2]) <= 0)
				datato[c++] = datafrom[p1++];
			else
				datato[c++] = datafrom[p2++];
		}

		while(p1 <= m)
			datato[c++] = datafrom[p1++];
		while(p2 <= r)
			datato[c++] = datafrom[p2++];
	}


	template<class T>
	void MergeSort<T>::work(T * datafrom, T * datato, std::size_t n, std::size_t step, int(*cmp)(const T & lhs, const T & rhs)) const
	{
		std::size_t i;
		std::size_t delta = (step << 1);

		for(i = 0; i + delta <= n; i += delta)
			merge(datafrom, datato, i, i + step - 1, i + delta - 1, cmp);

		if(i + step < n)
			merge(datafrom, datato, i, i + step - 1, n - 1, cmp);
		else
		{
			while(i < n)
			{
				datato[i] = datafrom[i];
				i++;
			}
		}
	}

}

#endif
