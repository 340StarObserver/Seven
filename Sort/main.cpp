/*
 * Author 	: 	Lv Yang
 * Created 	: 	15 May 2017
 * Modified : 	15 May 2017
 * Version 	: 	1.0
 */

/*
 * This file used to test the sort module, includes :
 * 1. Sort<T>
 * 2. FastSort<T>
 * 3. HeapSort<T>
 * 4. MergeSort<T>
 */

#include <iostream>
using std::cout;

#include "Sort.h"
using Seven::Sort;

#include "FastSort.h"
using Seven::FastSort;


int cmp_int(const int & lhs, const int & rhs)
{
	if(lhs < rhs)
		return -1;
	if(lhs > rhs)
		return 1;
	return 0;
}


void print_int(const int * data, std::size_t n)
{
	for(std::size_t i = 0; i < n; i++)
	{
		cout << data[i] << '\t';
		if((i + 1) % 5 == 0)
			cout << '\n';
	}
	cout << '\n';
}


int main()
{
	// test FastSort<T>
	{
		int data[] = {15, 2, 14, 13, 5, 6, 0, 3, 1, 16, 10, 17, 4, 11, 18, 7, 8, 12, 9, 19};
		std::size_t n = sizeof(data) / sizeof(int);

		cout << "before sort :\n";
		print_int(data, n);

		Sort<int> * handler = new FastSort<int>();
		handler->sort(data, n, cmp_int);
		delete handler;

		cout << "\nafter sort :\n";
		print_int(data, n);
	}

	return 0;
}
