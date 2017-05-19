/*
 * Author 	: 	Lv Yang
 * Create 	: 	19 May 2017
 * Modify 	: 	19 May 2017
 * Version 	: 	1.0
 */

#ifndef _SEVEN_COMMONQUEUE_H
#define _SEVEN_COMMONQUEUE_H

#include "../List/List.h"
#include "Queue.h"

namespace Seven
{
	template<class T>
	class CommonQueue : public Queue<T>
	{
	private:
		List<T> _list;
	
	public:
		CommonQueue();

		virtual ~CommonQueue(){}
		virtual void clear();

		virtual std::size_t size() const;
		virtual bool empty() const;

		virtual void push(const T & value);
		virtual void pop(bool mode = true);
		virtual T front(bool mode = true) const;
	};

	template<class T>
	CommonQueue<T>::CommonQueue() : Queue<T>(), _list()
	{

	}

	template<class T>
	void CommonQueue<T>::clear()
	{
		_list.clear();
	}

	template<class T>
	std::size_t CommonQueue<T>::size() const
	{
		return _list.size();
	}

	template<class T>
	bool CommonQueue<T>::empty() const
	{
		return _list.empty();
	}

	template<class T>
	void CommonQueue<T>::push(const T & value)
	{
		_list.addTail(value);
	}

	template<class T>
	void CommonQueue<T>::pop(bool mode)
	{
		_list.rmHead();
	}

	template<class T>
	T CommonQueue<T>::front(bool mode) const
	{
		if(_list.empty() == false)
			return _list.readHead();
		throw QueueEmptyException();
	}

}

#endif
