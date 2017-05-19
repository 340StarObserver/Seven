/*
 * Author 	: 	Lv Yang
 * Create 	: 	19 May 2017
 * Modify 	: 	19 May 2017
 * Version 	: 	1.0
 */

#include <iostream>
using std::cout;

#include "Queue.h"
using Seven::Queue;
using Seven::QueueEmptyException;

int main()
{
	Queue<int> * queue = NULL;
	cout << (void *)queue << '\n';

	try {
		throw QueueEmptyException();
	} catch(const std::exception & e) {
		cout << e.what() << '\n';
	}

	return 0;
}
