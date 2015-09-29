#ifndef _SORT_H
#define _SORT_H

namespace Seven
{
	// class for sort
	/*
	< requirements >
	1. type T should support default constructor
	2. type T should support operator =
	--------------------------------------------------
	< help >
	1. _array[]   : the array which waits to be sorted
	2. N          : the size of the array
	3. smallerThan: used to compare elements. if t1<t2,return true
	*/
	template<class T>
	class Sort
	{
	private:
		// merge two arrays              (ok)
		static void merge(T * _array1, size_t N1, T * _array2, size_t N2, bool(*smallerThan)(const T & t1, const T & t2));

		// partition                     (ok)
		// make array[left...right] to: array[left...c-1] <= array[c] <= array[c+1...right]
		static size_t partition(T * _array, size_t left, size_t right, bool(*smallerThan)(const T & t1, const T & t2));

		// inner implement of fast sort  (ok)
		static void fastImplement(T * _array, size_t left, size_t right, bool(*smallerThan)(const T & t1, const T & t2));

	public:
		// bubble sort                   (ok)
		static void bubbleSort(T * _array, size_t N, bool(*smallerThan)(const T & t1, const T & t2));

		// select sort                   (ok)
		static void selectSort(T * _array, size_t N, bool(*smallerThan)(const T & t1, const T & t2));

		// insert sort                   (ok)
		static void insertSort(T * _array, size_t N, bool(*smallerThan)(const T & t1, const T & t2));

		// merge sort                    (ok)
		static void mergeSort(T * _array, size_t N, bool(*smallerThan)(const T & t1, const T & t2));

		// fast sort                     (ok)
		static void fastSort(T * _array, size_t N, bool(*smallerThan)(const T & t1, const T & t2));
	};

	//--------------------------------------------------
	// implements:

	// bubble sort
	template<class T>
	void Sort<T>::bubbleSort(T * _array, size_t N, bool(*smallerThan)(const T & t1, const T & t2))
	{
		bool w = true;
		T tmp;
		for (size_t k = 0; k < N - 1 && w; k++)
		{
			w = false;
			for (size_t i = 0; i < N - 1 - k; i++)
			{
				if (smallerThan(_array[i + 1], _array[i]))
				{
					w = true;
					tmp = _array[i];
					_array[i] = _array[i + 1];
					_array[i + 1] = tmp;
				}
			}
		}
	}


	// select sort
	template<class T>
	void Sort<T>::selectSort(T * _array, size_t N, bool(*smallerThan)(const T & t1, const T & t2))
	{
		T tmp, min;
		size_t j = 0;
		for (size_t k = 0; k < N - 1; k++)
		{
			j = k;
			min = _array[k];
			for (size_t i = k + 1; i < N; i++)
			{
				if (smaller(_array[i], min))
				{
					j = i;
					min = _array[i];
				}
			}
			if (j != k)
			{
				tmp = _array[j];
				_array[j] = _array[k];
				_array[k] = tmp;
			}
		}
	}


	// insert sort
	template<class T>
	void Sort<T>::insertSort(T * _array, size_t N, bool(*smallerThan)(const T & t1, const T & t2))
	{
		size_t move = 0;
		T insert;
		for (size_t k = 1; k < N; k++)
		{
			insert = _array[k];
			move = k;
			while (move > 0 && smaller(insert, _array[move - 1]))
			{
				_array[move] = _array[move - 1];
				move--;
			}
			_array[move] = insert;
		}
	}


	// merge two arrays
	template<class T>
	void Sort<T>::merge(T * _array1, size_t N1, T * _array2, size_t N2, bool(*smallerThan)(const T & t1, const T & t2))
	{
		T * tmp = new T[N1 + N2];
		size_t p = 0, q = 0, c = 0;
		while (p < N1 && q < N2)
		{
			if (smallerThan(_array1[p], _array2[q]))
				tmp[c++] = _array1[p++];
			else
				tmp[c++] = _array2[q++];
		}
		while (p < N1)
			tmp[c++] = _array1[p++];
		while (q < N2)
			tmp[c++] = _array2[q++];
		for (size_t i = 0; i < N1; i++)
			_array1[i] = tmp[i];
		for (size_t i = 0; i < N2; i++)
			_array2[i] = tmp[i + N1];
		delete[]tmp;
	}


	// merge sort
	template<class T>
	void Sort<T>::mergeSort(T * _array, size_t N, bool(*smallerThan)(const T & t1, const T & t2))
	{
		if (N > 1)
		{
			size_t center = N / 2;
			mergeSort(_array, center, smallerThan);
			mergeSort(_array + center, N - center, smallerThan);
			merge(_array, center, _array + center, N - center, smallerThan);
		}
	}


	// partition
	// make array[left...right] to: array[left...c-1] <= array[c] <= array[c+1...right]
	template<class T>
	size_t Sort<T>::partition(T * _array, size_t left, size_t right, bool(*smallerThan)(const T & t1, const T & t2))
	{
		size_t key = right;
		if (left < right)
		{
			size_t p = left, q = right;
			T tmp;
			while (p < q)
			{
				while (p < key && !smallerThan(_array[key], _array[p]))
					p++;
				if (p != key)
				{
					tmp = _array[p];
					_array[p] = _array[key];
					_array[key] = tmp;
					key = p;
					q--;
				}
				while (key < q && !smallerThan(_array[q], _array[key]))
					q--;
				if (q != key)
				{
					tmp = _array[q];
					_array[q] = _array[key];
					_array[key] = tmp;
					key = q;
					p++;
				}
			}
		}
		return key;
	}


	// inner implement of fast sort
	template<class T>
	void Sort<T>::fastImplement(T * _array, size_t left, size_t right, bool(*smallerThan)(const T & t1, const T & t2))
	{
		if (left < right)
		{
			size_t key = partition(_array, left, right, smallerThan);
			if (left + 1 < key)
				fastImplement(_array, left, key - 1, smallerThan);
			if (key + 1 < right)
				fastImplement(_array, key + 1, right, smallerThan);
		}
	}


	// fast sort
	template<class T>
	void Sort<T>::fastSort(T * _array, size_t N, bool(*smallerThan)(const T & t1, const T & t2))
	{
		fastImplement(_array, 0, N - 1, smallerThan);
	}

}

#endif