#ifndef _LINKEDNODE_H
#define _LINKEDNODE_H

#include <iostream>
using std::cout;

namespace Seven
{
	// linkednode used for linkedlist
	/*
	< requirements >
	1. type T should support default constructor
	2. type T should support operator =
	*/
	template<class T>
	class LinkedNode
	{
	private:
		T _value;                // the value
		LinkedNode<T> * _pre;    // address of its pre node
		LinkedNode<T> * _next;   // address of its next node
	public:
		// test:
		void print(void(*showT)(const T & value))const;   // test print                     (ok)
		void toHead(void(*showT)(const T & value))const;  // print from itself to head      (ok)
		void toTail(void(*showT)(const T & value))const;  // print from itself to tail      (ok)

		// get:
		T * getValue();                                   // get value                      (ok)
		LinkedNode<T> * getPre()const;                    // get address of its pre node    (ok)
		LinkedNode<T> * getNext()const;                   // get address of its next node   (ok)

		// set:
		void setValue(const T & value);                   // set value                      (ok)
		void setPre(LinkedNode<T> * pre);                 // set address of its pre node    (ok)
		void setNext(LinkedNode<T> * next);               // set address of its next node   (ok)

		// constructors:
		LinkedNode();                                     // default constructor            (ok)
		LinkedNode(const T & value);                      // construct by value             (ok)

		// add:
		void addPre(const T & value);                     // add a node,insert to its pre   (ok)
		void addNext(const T & value);                    // add a node,insert to its next  (ok)

		// remove:
		void rmPre();                                     // remove its pre node            (ok)
		void rmNext();                                    // remove its next node           (ok)
	};

	//----------------------------------------
	// implements:

	// test print
	template<class T>
	void LinkedNode<T>::print(void(*showT)(const T & value))const
	{
		cout << "value: ";
		showT(_value);
		cout << "its  address: " << (const void * const)this << '\n';
		cout << "pre  address: " << (void *)_pre << '\n';
		cout << "next address: " << (void *)_next << "\n\n";
	}

	// print from itself to head
	template<class T>
	void LinkedNode<T>::toHead(void(*showT)(const T & value))const
	{
		const LinkedNode<T> * p = this;
		while (p)
		{
			p->print(showT);
			p = p->getPre();
		}
	}

	// print from itself to tail
	template<class T>
	void LinkedNode<T>::toTail(void(*showT)(const T & value))const
	{
		const LinkedNode<T> * p = this;
		while (p)
		{
			p->print(showT);
			p = p->getNext();
		}
	}

	// get value
	template<class T>
	T * LinkedNode<T>::getValue()
	{
		return &_value;
	}

	// get address of its pre node
	template<class T>
	LinkedNode<T> * LinkedNode<T>::getPre()const
	{
		return _pre;
	}

	// get address of its next node
	template<class T>
	LinkedNode<T> * LinkedNode<T>::getNext()const
	{
		return _next;
	}

	// set value
	template<class T>
	void LinkedNode<T>::setValue(const T & value)
	{
		_value = value;
	}

	// set address of its pre node
	template<class T>
	void LinkedNode<T>::setPre(LinkedNode<T> * pre)
	{
		_pre = pre;
	}

	// set address of its next node
	template<class T>
	void LinkedNode<T>::setNext(LinkedNode<T> * next)
	{
		_next = next;
	}

	// default constructor
	template<class T>
	LinkedNode<T>::LinkedNode()
	{
		_pre = nullptr;
		_next = nullptr;
	}

	// construct by value
	template<class T>
	LinkedNode<T>::LinkedNode(const T & value)
	{
		_value = value;
		_pre = nullptr;
		_next = nullptr;
	}

	// add a node,insert to its pre
	/*
	if its pre node is null, that is: NULL <-- this
	{
	   after add: NULL <-- newnode <--> this
	}
	else, that is: pre <--> this
	{
	   after add: pre <--> newnode <--> this
	}
	*/
	template<class T>
	void LinkedNode<T>::addPre(const T & value)
	{
		LinkedNode<T> * newnode = new LinkedNode<T>(value);
		LinkedNode<T> * pre = _pre;
		newnode->_pre = pre;
		newnode->_next = this;
		_pre = newnode;
		if (pre)
			pre->_next = newnode;
	}

	// add a node,insert into its next
	/*
	if its next node is null, that is: this --> next
	{
	   after add: this <--> newnode --> NULL
	}
	else, that is: this <--> next
	{
	   after add: this <--> newnode <--> next
	}
	*/
	template<class T>
	void LinkedNode<T>::addNext(const T & value)
	{
		LinkedNode<T> * newnode = new LinkedNode<T>(value);
		LinkedNode<T> * next = _next;
		newnode->_pre = this;
		newnode->_next = next;
		_next = newnode;
		if (next)
			next->_pre = newnode;
	}

	// remove its pre node
	/*
	if its pre node is null
	{
	   do nothing
	}
	if origin is: pre.pre <--> pre <--> this
	{
	   after remove: pre.pre <--> this
	}
	if origin is: NULL <-- pre <--> this
	{
	   after remove: NULL <-- this
	}
	*/
	template<class T>
	void LinkedNode<T>::rmPre()
	{
		LinkedNode<T> * pre = _pre;
		if (!pre)
			return;
		LinkedNode<T> * tmp = pre->_pre;
		delete pre;
		_pre = tmp;
		if (tmp)
			tmp->_next = this;
	}


	// remove its next node
	/*
	if its next node is null
	{
	   do nothing
	}
	if origin is: this <--> next <--> next.next
	{
	   after remove: this <--> next.next
	}
	if origin is: this <--> next --> NULL
	{
	   after remove: this --> NULL
	}
	*/
	template<class T>
	void LinkedNode<T>::rmNext()
	{
		LinkedNode<T> * next = _next;
		if (!next)
			return;
		LinkedNode<T> * tmp = next->_next;
		delete next;
		_next = tmp;
		if (tmp)
			tmp->_pre = this;
	}
}

#endif