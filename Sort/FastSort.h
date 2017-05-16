/*
 * Author 	: 	Lv Yang
 * Create 	: 	15 May 2017
 * Modify 	: 	15 May 2017
 * Version 	: 	1.0
 */

#ifndef _FASTSORT_H
#define _FASTSORT_H

#include "Sort.h"

namespace Seven
{
	template<class T>
	class FastSort : public Sort<T>
	{
	private:
		void swap(T & lhs, T & rhs) const;

		void work(T * data, std::size_t idx_l, std::size_t idx_r, int(*cmp)(const T & lhs, const T & rhs)) const;

	public:
		virtual ~FastSort(){}

		virtual void sort(T * data, std::size_t n, int(*cmp)(const T & lhs, const T & rhs)) const;
	};


	template<class T>
	void FastSort<T>::sort(T * data, std::size_t n, int(*cmp)(const T & lhs, const T & rhs)) const
	{
		if(data != NULL && n > 1 && cmp != NULL)
			work(data, 0, n - 1, cmp);
	}


	template<class T>
	void FastSort<T>::swap(T & lhs, T & rhs) const
	{
		T tmp = lhs;
		lhs = rhs;
		rhs = tmp;
	}


	template<class T>
	void FastSort<T>::work(T * data, std::size_t idx_l, std::size_t idx_r, int(*cmp)(const T & lhs, const T & rhs)) const
	{
		std::size_t i = idx_l + 1;
		std::size_t j = idx_r;

		T base = data[idx_l];
		while(i < j)
		{
			while(i <= idx_r && cmp(data[i], base) <= 0)
				i++;
			while(j > idx_l && cmp(data[j], base) >= 0)
				j--;
			if(i < j)
				this->swap(data[i], data[j]);
		}

		if(cmp(base, data[j]) > 0)
			this->swap(data[idx_l], data[j]);

		if(idx_l + 1 < j)
			work(data, idx_l, j - 1, cmp);
		if(j + 1 < idx_r)
			work(data, j + 1, idx_r, cmp);
	}

}

#endif
