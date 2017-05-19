/*
 * Author 	: 	Lv Yang
 * Create 	: 	19 May 2017
 * Modify 	: 	19 May 2017
 * Version 	: 	1.0
 */

#ifndef _SEVEN_QUEUE_H
#define _SEVEN_QUEUE_H

namespace Seven
{
	/*
	 * Queue interface
	 * !-- type T should satisfy :
	 *     a. default constructor
	 *     b. copy constructor
	 *     c. operator =
	 */

	template<class T>
	class Queue
	{
	public:
		virtual ~Queue(){}

		virtual void clear() = 0;

		virtual std::size_t size() const = 0;

		virtual bool empty() const = 0;

		virtual void push(const T & value) = 0;

		/*
		 * !-- pay attention to parameter 'mode'
		 * 1. CommonQueue
		 *    no matter what mode, choose queue's head
		 * 2. PriorityQueue
		 *    no matter what mode, choose the max priority element
		 * 3. MaxMinQueue
		 *    mode = true  : choose the max priority element
		 *    mode = false : choose the min priority element
		 */

		virtual T front(bool mode) const = 0;

		virtual void pop(bool mode) = 0;
	};

	class QueueEmptyException : public std::exception
	{
	private:
		static const char * msg;
	public:
		QueueEmptyException() : std::exception()
		{

		}
		virtual const char * what() const throw()
		{
			return msg;
		}
	};

	const char * QueueEmptyException::msg = "Exception queue empty";

}

#endif
