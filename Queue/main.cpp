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

#include "CommonQueue.h"
using Seven::CommonQueue;

int main()
{
	// test CommonQueue<T>
	{
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
	}

	return 0;
}
