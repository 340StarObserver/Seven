#ifndef _STACK_H
#define _STACK_H

#include "LinkedList.h"

namespace Seven
{
	// stack
	/*
	< requirements >
	1. type T should support default constructor
	2. type T should support operator =
	*/
	template<class T>
	class Stack
	{
	private:
		LinkedList<T> * _list; // the linkedlist for agency
	public:
		// constructors:
		static Stack<T> * create();         // create a stack               (ok)
		Stack();                            // default constructor          (ok)
		Stack(const Stack<T> & S);          // copy constructor             (ok)
		Stack<T> & operator = (const Stack<T> & S); // operator =           (ok)

		// clears:
		void clear();                       // clear the whole stack        (ok)
		~Stack();                           // deconstructor                (ok)

		// attributes:
		bool empty()const;                  // whether the stack is empty   (ok)
		size_t size()const;                 // get the size of the stack    (ok)
		
		// CURD:
		void push(const T & value);         // push a node to the stack     (ok)
		bool pop();                         // pop a node from stack top    (ok)
		T * peek();                         // read the stack top           (ok)
		T top()const;                       // read the stack top           (ok)
		bool update(const T & value);       // update the stack top         (ok)
	};

	//----------------------------------------
	// implements:

	// create a stack
	template<class T>
	Stack<T> * Stack<T>::create()
	{
		return new Stack<T>();
	}


	// default constructor
	/*
	create a linkedlist, and assign the list for agency with it
	*/
	template<class T>
	Stack<T>::Stack()
	{
		_list = LinkedList<T>::create();
	}


	// copy constructor
	/*
	use the linkedlist for agency to copy
	*/
	template<class T>
	Stack<T>::Stack(const Stack<T> & S)
	{
		_list = new LinkedList<T>(*(S._list));
	}


	// operator =
	/*
	if current this object is not the parament "S":
	{
	   then use the linkedlist for agency to exec operator =
	}
	return this object
	*/
	template<class T>
	Stack<T> & Stack<T>::operator = (const Stack<T> & S)
	{
		if (this != &S)
			_list->operator=(*(S._list));
		return *this;
	}


	// clear the whole stack
	/*
	use the linkedlist for agency to clear
	*/
	template<class T>
	void Stack<T>::clear()
	{
		_list->clear();
	}


	// deconstructor
	/*
	1. clear the whole stack
	2. delete the linkedlist for agency
	inform: when delete the linkedlist,it will exec clear() inner,
	        so step 1 is not necessary,
			that is to say,only step 2 is enough
	*/
	template<class T>
	Stack<T>::~Stack()
	{
		delete _list;
	}


	// whether the stack is empty
	template<class T>
	bool Stack<T>::empty()const
	{
		return _list->empty();
	}


	// get the size of the stack
	template<class T>
	size_t Stack<T>::size()const
	{
		return _list->size();
	}


	// push a node to the stack
	/*
	use the linkedlist for agency to insert a node before the real head node
	*/
	template<class T>
	void Stack<T>::push(const T & value)
	{
		_list->insertHead(value);
	}


	// pop a node from stack top
	/*
	use the linkedlist for agency to remove its real head node
	*/
	template<class T>
	bool Stack<T>::pop()
	{
		return _list->removeHead();
	}


	// read the stack top
	/*
	use the linkedlist for agency to get value address of the real head node
	*/
	template<class T>
	T * Stack<T>::peek()
	{
		return _list->readHead();
	}


	// read the stack top
	/*
	different from "peek()", this function return the value rather than address
	*/
	template<class T>
	T Stack<T>::top()const
	{
		return _list->head();
	}


	// update the stack top
	/*
	use the linkedlist for agency to update its real head node
	*/
	template<class T>
	bool Stack<T>::update(const T & value)
	{
		return _list->updateHead(value);
	}

}

#endif