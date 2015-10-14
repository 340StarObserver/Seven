#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include "LinkedNode.h"

#include <iostream>
using std::cout;

namespace Seven
{
	// linkedlist
	/*
	< requirements >
	1. type T should support default constructor
	2. type T should support operator =
	*/
	template<class T>
	class LinkedList
	{
	private:
		LinkedNode<T> * _head;  // addtional head node
		LinkedNode<T> * _tail;  // addtional tail node
		size_t _size;           // size of the list
	public:
		// declare class Iterator
		class Iterator;

		// test print:
		void print(void(*showT)(const T & value))const;  // test print                  (ok)

		// constructors:
		static LinkedList<T> * create();                 // create a list               (ok)
		LinkedList();                                    // default constructor         (ok)
		LinkedList(const LinkedList<T> & list);          // copy construcor             (ok)
		LinkedList<T> & operator = (const LinkedList<T> & list);// operator =           (ok)

		// clear:
		void clear();                                    // clear the whole list        (ok)
		~LinkedList();                                   // deconstructor               (ok)

		// attributes:
		bool empty()const;                               // whether the list is empty   (ok)
		size_t size()const;                              // get the size of the list    (ok) 

		// C:
		void insertHead(const T & value);                // add a node to list head     (ok)
		void insertTail(const T & value);                // add a node to list tail     (ok)

		// U:
		bool updateHead(const T & value);                // update value of real head   (ok)
		bool updateTail(const T & value);                // update value of real tail   (ok)

		// R:
		T * readHead();                                  // get value address of head   (ok)
		T * readTail();                                  // get value address of tail   (ok)
		T head()const;                                   // get value of head           (ok)
		T tail()const;                                   // get value of tail           (ok)

		// D:
		bool removeHead();                               // remove the real head node   (ok)
		bool removeTail();                               // remove the real tail node   (ok)

		// iterators:
		Iterator begin()                                 // iterator begin              (ok)
		{
			return Iterator(_head->getNext(), _size);
		}
		Iterator end()                                   // iterator end                (ok)
		{
			return Iterator(_tail, _size);
		}

		// the Iterator
		class Iterator
		{
		private:
			LinkedNode<T> * _location;  // iterator current location
			size_t & _curSize;          // iterator current size
		public:
			// constructor
			Iterator(LinkedNode<T> * location, size_t & curSize);
			// operators:
			void operator ++ ();                        // to next location(prefix)        (ok)
			void operator ++ (int);                     // to next location(suffic)        (ok)
			void operator -- ();                        // to pre location(prefix)         (ok)
			void operator -- (int);                     // to pre location(suffix)         (ok)
			bool operator == (const Iterator & it)const;// iterator equal                  (ok)
			bool operator != (const Iterator & it)const;// iterator not equal              (ok)
			// C:
			bool addPre(const T & value);               // cur location add pre node       (ok)
			bool addNext(const T & value);              // cur location add next node      (ok)
			// U:
			bool update(const T & value);               // update value of cur location    (ok)
			// R:
			T * read();                                 // get value of current location   (ok)
			// D:
			bool remove();                              // remove the current location     (ok)
		};
	};

	//----------------------------------------
	// implements:

	// test print
	/*
	1. test emtpy()
	2. test size()
	3. test the real head node
	4. test the real tail node
	5. test the whole list
	*/
	template<class T>
	void LinkedList<T>::print(void(*showT)(const T & value))const
	{
		cout << "\n< test print >\n";

		cout << (empty() ? "list is empty" : "list is not empty") << '\n';
		cout << "size: " << size() << '\n';
		
		if (_head->getNext() != _tail)
		{
			cout << "the real head node:\n";
			_head->getNext()->print(showT);
		}
		else
			cout << "the real head node: null\n";

		if (_tail->getPre() != _head)
		{
			cout << "the real tail node:\n";
			_tail->getPre()->print(showT);
		}
		else
			cout << "the real tail node: null\n";

		cout << "the whole list:\n";
		LinkedNode<T> * p = _head->getNext();
		while (p != _tail)
		{
			p->print(showT);
			p = p->getNext();
		}
	}


	// create a list
	template<class T>
	LinkedList<T> * LinkedList<T>::create()
	{
		return new LinkedList<T>();
	}


	// default constructor
	/*
	1. create addtional head node( _head )
	2. create addtional tail node( _tail )
	3. connect the two node,as a result: _head <--> _tail
	4. make the size is zero
	*/
	template<class T>
	LinkedList<T>::LinkedList()
	{
		_head = new LinkedNode<T>();
		_tail = new LinkedNode<T>();
		_head->setNext(_tail);
		_tail->setPre(_head);
		_size = 0;
	}


	// copy construcor
	/*
	1. create a empty list
	2. use values in parament "list" to create nodes,
	   and insert these nodes to the empty list
	*/
	template<class T>
	LinkedList<T>::LinkedList(const LinkedList<T> & list)
	{
		_head = new LinkedNode<T>();
		_tail = new LinkedNode<T>();
		_head->setNext(_tail);
		_tail->setPre(_head);
		_size = 0;
		LinkedNode<T> * p = list._head->getNext();
		while (p != list._tail)
		{
			insertTail(*(p->getValue()));
			p = p->getNext();
		}
	}


	// operator =
	/*
	if parament list is not this:
	{
	   1. clear the current whole list
	   2. use values in parament "list" to create nodes,
	      and insert these nodes to the list
	}
	*/
	template<class T>
	LinkedList<T> & LinkedList<T>::operator = (const LinkedList<T> & list)
	{
		if (this != &list)
		{
			clear();
			LinkedNode<T> * p = list._head->getNext();
			while (p != list._tail)
			{
				insertTail(*(p->getValue()));
				p = p->getNext();
			}
		}
		return *this;
	}


	// clear the whole list
	/*
	while size > 0
	{
	   use the addtional head node to remove its next node
	   decrease the size
	}
	*/
	template<class T>
	void LinkedList<T>::clear()
	{
		while (_size > 0){
			_head->rmNext();
			_size--;
		}
	}


	// deconstructor
	/*
	1. clear the whole list
	2. delete the addtional head node
	3. delete the addtional tail node
	*/
	template<class T>
	LinkedList<T>::~LinkedList()
	{
		clear();
		delete _head;
		delete _tail;
	}


	// whether the list is empty
	template<class T>
	bool LinkedList<T>::empty()const
	{
		return _size == 0;
	}


	// get the size of the list
	template<class T>
	size_t LinkedList<T>::size()const
	{
		return _size;
	}


	// add a node to list head
	/*
	1. use the addtional head node to add a next node
	2. increase the size
	*/
	template<class T>
	void LinkedList<T>::insertHead(const T & value)
	{
		_head->addNext(value);
		_size++;
	}


	// add a node to list tail
	/*
	1. use the addtional tail node to add a pre node
	2. increase the size
	*/
	template<class T>
	void LinkedList<T>::insertTail(const T & value)
	{
		_tail->addPre(value);
		_size++;
	}


	// get value address of real head node
	/*
	if the list is empty:
	   return null
	else:
	   return the address of value of the real head node
	*/
	template<class T>
	T * LinkedList<T>::readHead()
	{
		if (_size > 0)
			return _head->getNext()->getValue();
		return nullptr;
	}


	// get value address of real tail node
	/*
	if the list is empty:
	   return null
	else:
	   return the address of value of the real tail node
	*/
	template<class T>
	T * LinkedList<T>::readTail()
	{
		if (_size > 0)
			return _tail->getPre()->getValue();
		return nullptr;
	}


	// get head value
	template<class T>
	T LinkedList<T>::head()const
	{
		return _head->getNext()->value();
	}


	// get tail value
	template<class T>
	T LinkedList<T>::tail()const
	{
		return _tail->getPre()->value();
	}


	// update value of real head
	/*
	if the list is empty:
	   return false
	else:
	   update the value of the real head node
	   return true
	*/
	template<class T>
	bool LinkedList<T>::updateHead(const T & value)
	{
		if (_size == 0)
			return false;
		_head->getNext()->setValue(value);
		return true;
	}


	// update value of real tail
	/*
	if the list is empty:
	   return false
	else:
	   update the value of the real tail node
	   return true
	*/
	template<class T>
	bool LinkedList<T>::updateTail(const T & value)
	{
		if (_size == 0)
			return false;
		_tail->getPre()->setValue(value);
		return true;
	}


	// remove the real head node
	/*
	if the list is empty:
	   return false
	else:
	   use the addtional head node to remove its next node
	   decrease size
	   return true
	*/
	template<class T>
	bool LinkedList<T>::removeHead()
	{
		if (_size == 0)
			return false;
		_head->rmNext();
		_size--;
		return true;
	}


	// remove the real tail node
	/*
	if the list is empty:
	   return fasle
	else:
	   use the addtional tail node to remove its pre node
	   decrease size
	   return true
	*/
	template<class T>
	bool LinkedList<T>::removeTail()
	{
		if (_size == 0)
			return false;
		_tail->rmPre();
		_size--;
		return true;
	}

	//----------------------------------------
	// Iterator implements:

	// constructor
	template<class T>
	LinkedList<T>::Iterator::Iterator(LinkedNode<T> * location, size_t & curSize) :_curSize(curSize)
	{
		_location = location;
	}


	// to next location(prefix)
	/*
	if current location is not the tail:
	   then move to its next location
	*/
	template<class T>
	void LinkedList<T>::Iterator::operator ++ ()
	{
		if (_location->getNext())
			_location = _location->getNext();
	}


	// to next location(suffix)
	/*
	if current location is not the tail:
	   then move to its next location
	*/
	template<class T>
	void LinkedList<T>::Iterator::operator ++ (int)
	{
		if (_location->getNext())
			_location = _location->getNext();
	}


	// to pre location(prefix)
	/*
	if current location is not the begin location:
	   then move to its pre location
	*/
	template<class T>
	void LinkedList<T>::Iterator::operator -- ()
	{
		if (_location->getPre()->getPre())
			_location = _location->getPre();
	}


	// to pre location(suffix)
	/*
	if current location is not the begin location:
	then move to its pre location
	*/
	template<class T>
	void LinkedList<T>::Iterator::operator -- (int)
	{
		if (_location->getPre()->getPre())
			_location = _location->getPre();
	}


	// iterator equal
	/*
	if current location equal, they are equal
	*/
	template<class T>
	bool LinkedList<T>::Iterator::operator == (const Iterator & it)const
	{
		return _location == it._location;
	}


	// iterator not equal
	/*
	if current location not equal, they are not equal
	*/
	template<class T>
	bool LinkedList<T>::Iterator::operator != (const Iterator & it)const
	{
		return _location != it._location;
	}


	// get value of current location
	/*
	if current node has next node,that is it isn't the addtional tail node
	   return its value
	else
	   return null
	*/
	template<class T>
	T * LinkedList<T>::Iterator::read()
	{
		if (_location->getNext())
			return _location->getValue();
		return nullptr;
	}


	// update value of the current location
	/*
	if current node has next node,that is it isn't the addtional tail node
	   update its value
	   return true
	else
	   return false
	*/
	template<class T>
	bool LinkedList<T>::Iterator::update(const T & value)
	{
		if (_location->getNext())
		{
			_location->setValue(value);
			return true;
		}
		return false;
	}


	// remove the current location
	/*
	if the current location is not the "end"
	{
	   note its next location as "next"
	   use "next" to remove its pre node
	   update the location to "next"
	   decrease the size
	   return true
	}
	else:
	   return false
	*/
	template<class T>
	bool LinkedList<T>::Iterator::remove()
	{
		LinkedNode<T> * next = _location->getNext();
		if (next)
		{
			next->rmPre();
			_location = next;
			_curSize--;
			return true;
		}
		return false;
	}


	// current location add a pre node
	/*
	any location ¡Ê [ begin, end ] all can add a pre node
	1. use the current location to add a pre node
	2. increase the size
	3. return true
	*/
	template<class T>
	bool LinkedList<T>::Iterator::addPre(const T & value)
	{
		_location->addPre(value);
		_curSize++;
		return true;
	}


	// current location add a next node
	/*
	any location ¡Ê [ begin, end ) can add a next node, that is,
	if current location is not the "end",it can add a next node
	so, the process:
	if current location is not the "end"
	{
	   use the current location to add a next node
	   increase the size
	   return true
	}
	else
	   return false
	*/
	template<class T>
	bool LinkedList<T>::Iterator::addNext(const T & value)
	{
		if (_location->getNext())
		{
			_location->addNext(value);
			_curSize++;
			return true;
		}
		return false;
	}

}

#endif