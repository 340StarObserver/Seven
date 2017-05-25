/*
 * Author 	: 	Lv Yang
 * Create 	: 	19 May 2017
 * Modify 	: 	25 May 2017
 * Version 	: 	1.0
 */

#include <iostream>
using std::cout;

#include "Queue.h"
using Seven::Queue;

#include "CommonQueue.h"
using Seven::CommonQueue;

#include "PriorityQueue.h"
using Seven::PriorityQueue;

#include "MaxMinQueue.h"
using Seven::MaxMinQueue;


int cmp_int(const int & lhs, const int & rhs)
{
	if(lhs < rhs) return -1;
	if(lhs > rhs) return 1;
	return 0;
}


int main()
{
	// test CommonQueue<T>
	{
		cout << "test CommonQueue<T>\n\n";

		Queue<int> * queue = new CommonQueue<int>();
		for(int i = 1; i <= 5; i++)
			queue->push(i);

		while(queue->empty() == false)
		{
			int e = queue->front();
			queue->pop();
			cout << "pop : " << e << '\n';
		}

		try {
			cout << "current queue head : " << queue->front() << '\n';
		} catch(const std::exception & e) {
			cout << e.what() << '\n';
		}

		delete queue;

		cout << "--------------------\n\n";
	}


	// test PriorityQueue<T>
	{
		cout << "test PriorityQueue<T>\n\n";

		Queue<int> * queue = new PriorityQueue<int>(cmp_int, 8);
		for(int i = 1; i <= 12; i++)
			queue->push(i);

		while(queue->empty() == false)
		{
			int e = queue->front();
			queue->pop();
			cout << "pop : " << e << '\n';
		}

		try {
			cout << "current queue head : " << queue->front() << '\n';
		} catch(const std::exception & e) {
			cout << e.what() << '\n';
		}

		delete queue;

		cout << "--------------------\n\n";
	}


	// test MaxMinQueue<T>
	{
		cout << "test MaxMinQueue<T>\n\n";

		Queue<int> * queue = new MaxMinQueue<int>(cmp_int, 4, false);

		int data[] = {5, 10, 0, 15, 12, 18, 30, 50, 22, 33};
		for(int i = 0; i < sizeof(data) / sizeof(int); i++)
			queue->push(data[i]);

		try {
			int e = queue->front(true);
			queue->pop(true);
			cout << "pop max : " << e << '\n';
		} catch(const std::exception & e) {
			cout << e.what() << '\n';
		}

		try {
			int e = queue->front(false);
			queue->pop(false);
			cout << "pop min : " << e << '\n';
		} catch(const std::exception & e) {
			cout << e.what() << '\n';
		}

		try {
			int e = queue->front(true);
			queue->pop(true);
			cout << "pop max : " << e << '\n';
		} catch(const std::exception & e) {
			cout << e.what() << '\n';
		}

		try {
			int e = queue->front(false);
			queue->pop(false);
			cout << "pop min : " << e << '\n';
		} catch(const std::exception & e) {
			cout << e.what() << '\n';
		}

		delete queue;

		cout << "--------------------\n\n";
	}

	return 0;
}
