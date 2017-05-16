/*
 * Author 	: 	Lv Yang
 * Create 	: 	16 May 2017
 * Modify 	: 	16 May 2017
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

#include "HeapSort.h"
using Seven::HeapSort;

#include "MergeSort.h"
using Seven::MergeSort;


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


void test_case(const Sort<int> * handler)
{
	int data[] = {15, 2, 14, 13, 5, 6, 0, 3, 1, 16, 10, 17, 4, 11, 18, 7, 8, 12, 9, 19};
	// int data[] = {19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	std::size_t n = sizeof(data) / sizeof(int);

	cout << "before sort :\n";
	print_int(data, n);

	handler->sort(data, n, cmp_int);

	cout << "\nafter sort :\n";
	print_int(data, n);
}


int main()
{
	// test FastSort<T>
	{
		Sort<int> * handler = new FastSort<int>();
		test_case(handler);
		delete handler;
	}

	// test HeapSort<T>
	{
		Sort<int> * handler = new HeapSort<int>();
		test_case(handler);
		delete handler;
	}

	// test MergeSort<T>
	{
		Sort<int> * handler = new MergeSort<int>();
		test_case(handler);
		delete handler;
	}

	return 0;
}
