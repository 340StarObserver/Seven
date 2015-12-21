#ifndef _SORT_H
#define _SORT_H

using std::_Copy_impl;

#include <xutility>
using std::fill;

namespace Seven
{
	// various strategys of sort
	/*
	< requirements >
	1.type T should support default constructor
	2.type T should support operator =

	< tips >
	1."data":
		the list you want to sort,and the index of it begins with zero
	2."N":
		the number of elements in the list
	3."compare":
		the strategy of comparing two elements.
		compare(left,right)<0 : left<right
		compare(left,right)=0 : left=right
		compare(left,right)>0 : left>right
	*/
	template<class T>
	class Sort
	{
	private:
		// swap two elements
		static void swap(T & left, T & right);


		// inner implements of quick sort
		// data[leftIndex : rightIndex] is to sort
		static void quickImplement(T * data, size_t leftIndex, size_t rightIndex, int(*compare)(const T & left, const T & right));


		// merge two sorted lists
		/*
		initlist[l:m] and initlist[m+1:n] are two already sorted list
		mergelist is the result of the merge of initlist[l:m] and initlist[m+1:n]
		*/
		static void merge(T * initlist, T * mergelist, size_t l, size_t m, size_t n, int(*compare)(const T & left, const T & right));


		// sublists of size S are merged from initlist to resultlist
		static void mergePass(T * initlist, T * resultlist, size_t N, size_t S, int(*compare)(const T & left, const T & right));


		// adjust a sub heap whose root's index is "root" and max index is "size"
		static void adjustHeap(T * data, size_t root, size_t size, int(*compare)(const T & left, const T & right));
	public:
		// insert sort
		static void insertSort(T * data, size_t N, int(*compare)(const T & left, const T & right));

		// quick sort
		static void quickSort(T * data, size_t N, int(*compare)(const T & left, const T & right));
	
		// merge sort
		static void mergeSort(T * data, size_t N, int(*compare)(const T & left, const T & right));
	
		// heap sort
		static void heapSort(T * data, size_t N, int(*compare)(const T & left, const T & right));

		// shell sort
		/*
		1."data"     : list you want to sort
		2."N"        : size of "data"
		3."intervals": intervals you use in the shellsort. N > better intervals[i] > intervals[i+1]
		4."m"        : size of "intervals"
		5."compare"  : strategy to compare two elements
		*/
		static void shellSort(T * data, size_t N, size_t * intervals, size_t m, int(*compare)(const T & left, const T & right));
	
		// radix sort
		/*
		1."data" : list you want to sort
		2."link" : the result order of elements, for example:
			after the function,link[]={4,1,2,3,0},that is to say:
			the sort result is: data[4],data[1],data[2],data[3],data[0]
		3."d"    : the number of keys
		4."r"    : the radix of each key
		5."N"    : the size of "data"
		6."digit": for example,digit(97,2,10) is to calculate the index of the 2st key in the 10 keys,that is 9
		*/
		static size_t radixSort(const T * data, size_t * link, size_t d, size_t r, size_t N, size_t(*digit)(const T & element, size_t index, size_t radix));
	};


	//--------------------------------------------------
	// implements:


	/*
	method:
	originally,data[0:0] is a sorted sub list
	then insert data[1] into data[0:0],to make data[0:1] become a sorted sub list
	then insert data[2] into data[0:1],to make data[0:2] become a sorted sub list
	...
	then insert data[N-1] into data[0:N-2],to make data[0:N-1] become a sorted sub list
	*/
	template<class T>
	void Sort<T>::insertSort(T * data, size_t N, int(*compare)(const T & left, const T & right))
	{
		size_t move = 0;
		T e;
		for (size_t k = 1; k < N; k++)
		{
			e = data[k];
			move = k;
			while (move > 0 && compare(e, data[move - 1]) < 0)
			{
				data[move] = data[move - 1];
				move--;
			}
			data[move] = e;
		}
	}


	template<class T>
	void Sort<T>::quickSort(T * data, size_t N, int(*compare)(const T & left, const T & right))
	{
		if (N > 1)
			quickImplement(data, 0, N - 1, compare);
	}


	template<class T>
	void Sort<T>::swap(T & left, T & right)
	{
		T tmp = left;
		left = right;
		right = tmp;
	}


	/*
	method:
	for example: {26,5,37,1,61,11,59,15,48,19} is the list we want to sort
	take action to make 26 is at the right location,
	that is,elements before 26 is smaller than 26,elements after 26 is bigger than 26
	like this: {11,5,19,1,15,26,59,61,48,37}
	then use the same method to deal with the two sub lists {11,5,19,1,15} and {59,61,48,37}
	*/
	template<class T>
	void Sort<T>::quickImplement(T * data, size_t leftIndex, size_t rightIndex, int(*compare)(const T & left, const T & right))
	{
		size_t i = leftIndex, j = rightIndex + 1;
		T pivot = data[leftIndex];
		do{
			do{
				i++;
			} while (compare(data[i], pivot) < 0);
			do{
				j--;
			} while (compare(data[j], pivot) > 0);
			if (i < j)
				swap(data[i], data[j]);
		} while (i < j);
		swap(data[leftIndex], data[j]);
		if (leftIndex + 1 < j)
			quickImplement(data, leftIndex, j - 1, compare);
		if (j + 1 < rightIndex)
			quickImplement(data, j + 1, rightIndex, compare);
	}


	/*
	merge two already sorted lists into one list
	*/
	template<class T>
	void Sort<T>::merge(T * initlist, T * mergelist, size_t l, size_t m, size_t n, int(*compare)(const T & left, const T & right))
	{
		size_t c = l, p1 = l, p2 = m + 1;
		while (p1 <= m && p2 <= n){
			if (compare(initlist[p1], initlist[p2]) <= 0)
				mergelist[c++] = initlist[p1++];
			else
				mergelist[c++] = initlist[p2++];
		}
		if (p1 <= m)
			_Copy_impl(initlist + p1, initlist + m + 1, mergelist + c);
		if (p2 <= n)
			_Copy_impl(initlist + p2, initlist + n + 1, mergelist + c);
	}


	template<class T>
	void Sort<T>::mergePass(T * initlist, T * resultlist, size_t N, size_t S, int(*compare)(const T & left, const T & right))
	{
		size_t delta = (S << 1), i;
		for (i = 0; i + delta <= N; i += delta)
			merge(initlist, resultlist, i, i + S - 1, i + delta - 1, compare);
		if (i + S < N)
			merge(initlist, resultlist, i, i + S - 1, N - 1, compare);
		else
			_Copy_impl(initlist + i, initlist + N, resultlist + i);
	}


	template<class T>
	void Sort<T>::mergeSort(T * data, size_t N, int(*compare)(const T & left, const T & right))
	{
		T * tmp = new T[N];
		for (size_t l = 1; l < N; l = (l << 1))
		{
			mergePass(data, tmp, N, l, compare);
			l = (l << 1);
			mergePass(tmp, data, N, l, compare);
		}
		delete[]tmp;
	}


	template<class T>
	void Sort<T>::heapSort(T * data, size_t N, int(*compare)(const T & left, const T & right))
	{
		size_t k;
		for (k = (N >> 1) - 1; k >= 0 && k < N; k--)
			adjustHeap(data, k, N, compare);
		for (k = N - 1; k > 0; k--)
		{
			swap(data[0], data[k]);
			adjustHeap(data, 0, k, compare);
		}
	}


	template<class T>
	void Sort<T>::adjustHeap(T * data, size_t root, size_t size, int(*compare)(const T & left, const T & right))
	{
		T e = data[root];
		size_t j;
		for (j = (root << 1) + 1; j < size; j = (j << 1) + 1)
		{
			if (j < size - 1 && compare(data[j], data[j + 1]) < 0)
				j++;
			if (compare(e, data[j]) >= 0)
				break;
			data[(j - 1) >> 1] = data[j];
		}
		data[(j - 1) >> 1] = e;
	}


	/*
	method:
	1. swap elements by intervals, to create better environment for insert sort
	2. insert sort
	*/
	template<class T>
	void Sort<T>::shellSort(T * data, size_t N, size_t * intervals, size_t m, int(*compare)(const T & left, const T & right))
	{
		for (size_t k = 0; k < m; k++)
		{
			for (size_t i = 0; i + intervals[k] < N; i++)
			{
				if (compare(data[i], data[i + intervals[k]])>0)
					swap(data[i], data[i + intervals[k]]);
			}
		}
		insertSort(data, N, compare);
	}


	// radix sort
	/*
	1."data" : list you want to sort
	2."link" : the result order of elements, for example:
	after the function,link[]={4,1,2,3,0},that is to say:
	the sort result is: data[4],data[1],data[2],data[3],data[0]
	3."d"    : the number of keys
	4."r"    : the radix of each key
	5."N"    : the size of "data"
	6."digit": for example,digit(97,2,10) is to calculate the index of the 2st key in the 10 keys,that is 9
	*/
	template<class T>
	size_t Sort<T>::radixSort(const T * data, size_t * link, size_t d, size_t r, size_t N, size_t(*digit)(const T & element, size_t index, size_t radix))
	{
		size_t * front = new size_t[r];
		size_t * end = new size_t[r];

		size_t i, first = 0, current, k, j, last;
		for (i = 0; i < N; i++)
			link[i] = i + 1;

		for (i = 0; i < d; i++)
		{
			fill(front, front + r, N);
			for (current = first; current < N; current = link[current])
			{
				k = digit(data[current], i, r);
				if (front[k] == N)
					front[k] = current;
				else
					link[end[k]] = current;
				end[k] = current;
			}

			for (j = 0; front[j] == N; j++);
			first = front[j];
			last = end[j];
			for (k = j + 1; k < r; k++)
			{
				if (front[k] < N)
				{
					link[last] = front[k];
					last = end[k];
				}
			}
			link[last] = N;
		}

		delete[]front;
		delete[]end;
		return first;
	}

}

#endif