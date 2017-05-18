/*
 * Author 	: 	Lv Yang
 * Create 	: 	18 May 2017
 * Modify 	: 	18 May 2017
 * Version 	: 	1.0
 */

#ifndef _SEVEN_LIST_H
#define _SEVEN_LIST_H

namespace Seven
{
	/*
	 * The following is the implement of single-direction-linkedlist
	 * !-- type T should satisfy :
	 *     a. default constructor
	 *     b. copy constructor
	 *     c. operator =
	 */

	template<class T>
	class ListNode
	{
	private:
		T _value;
		ListNode<T> * _next;

	public:
		ListNode();
		ListNode(const T & value);

		T getValue() const;
		ListNode<T> * getNext() const;

		void setValue(const T & value);
		void setNext(ListNode<T> * next);
	};


	template<class T>
	ListNode<T>::ListNode() : _next(NULL)
	{

	}


	template<class T>
	ListNode<T>::ListNode(const T & value) : _value(value), _next(NULL)
	{

	}


	template<class T>
	T ListNode<T>::getValue() const
	{
		return _value;
	}


	template<class T>
	ListNode<T> * ListNode<T>::getNext() const
	{
		return _next;
	}


	template<class T>
	void ListNode<T>::setValue(const T & value)
	{
		_value = value;
	}


	template<class T>
	void ListNode<T>::setNext(ListNode<T> * next)
	{
		_next = next;
	}


	// --------------------------------------------------


	class ListEmptyException : public std::exception
	{
	private:
		static const char * msg;
	public:
		ListEmptyException() : std::exception()
		{

		}
		virtual const char * what() const throw()
		{
			return msg;
		}
	};

	const char * ListEmptyException::msg = "Exception list empty";


	// --------------------------------------------------


	template<class T>
	class List
	{
	private:
		ListNode<T> * _head;
		ListNode<T> * _tail;
		std::size_t _size;

	public:
		List();
		List(const List<T> & list);
		List<T> & operator = (const List<T> & list);

		~List();
		void clear();

		bool empty() const;
		std::size_t size() const;

		void addHead(const T & value);
		void addTail(const T & value);

		/*
		 * be careful to use function rmTail()
		 * !-- its cost time is O(n)
		 */
		bool rmHead();
		bool rmTail();

		bool updateHead(const T & value);
		bool updateTail(const T & value);

		T readHead() const;
		T readTail() const;
	};


	template<class T>
	List<T>::List() : _head(NULL), _tail(NULL), _size(0)
	{

	}


	template<class T>
	List<T>::List(const List<T> & list)
	{
		if(list.empty())
		{
			_head = NULL;
			_tail = NULL;
			_size = 0;
			return;
		}

		_head = new ListNode<T>(list._head->getValue());

		ListNode<T> * p = _head;
		ListNode<T> * q = list._head->getNext();
		while(q != NULL)
		{
			p->setNext(new ListNode<T>(q->getValue()));
			p = p->getNext();
			q = q->getNext();
		}
		_tail = p;
		_size = list._size;
	}


	template<class T>
	List<T> & List<T>::operator = (const List<T> & list)
	{
		if(this != &list)
		{
			/*
			 * for exception safety
			 * !-- I first copy a temp list, then swap it with *this
			 * !-- the temp list will auto release when leave the code block
			 */

			// 1. copy a temp list
			List<T> tmplist(list);

			// 2. swap head
			ListNode<T> * p = _head;
			_head = tmplist._head;
			tmplist._head = p;

			// 3. swap tail
			p = _tail;
			_tail = tmplist._tail;
			tmplist._tail = p;

			// 4. swap size
			std::size_t t = _size;
			_size = tmplist._size;
			tmplist._size = t;
		}
		return *this;
	}


	template<class T>
	List<T>::~List()
	{
		clear();
	}


	template<class T>
	void List<T>::clear()
	{
		ListNode<T> * p = _head;
		ListNode<T> * q = NULL;
		while(p != NULL)
		{
			q = p->getNext();
			delete p;
			p = q;
		}
		_head = NULL;
		_tail = NULL;
		_size = 0;
	}


	template<class T>
	bool List<T>::empty() const
	{
		return _size == 0;
	}


	template<class T>
	std::size_t List<T>::size() const
	{
		return _size;
	}


	template<class T>
	void List<T>::addHead(const T & value)
	{
		ListNode<T> * p = new ListNode<T>(value);
		p->setNext(_head);
		_head = p;
		if(_tail == NULL)
			_tail = p;
		_size++;
	}


	template<class T>
	void List<T>::addTail(const T & value)
	{
		ListNode<T> * p = new ListNode<T>(value);
		if(_head == NULL)
			_head = p;
		else
			_tail->setNext(p);
		_tail = p;
		_size++;
	}


	template<class T>
	bool List<T>::rmHead()
	{
		if(empty())
			return false;

		ListNode<T> * p = _head;
		_head = _head->getNext();
		delete p;

		_size--;
		if(_size == 0)
			_tail = NULL;

		return true;
	}


	template<class T>
	bool List<T>::rmTail()
	{
		if(empty())
			return false;

		ListNode<T> * p = _tail;

		_size--;
		if(_size == 0)
		{
			_head = NULL;
			_tail = NULL;
		}
		else
		{
			ListNode<T> * q = _head;
			while(q->getNext() != _tail)
				q = q->getNext();
			q->setNext(NULL);
			_tail = q;
		}

		delete p;
		return true;
	}


	template<class T>
	bool List<T>::updateHead(const T & value)
	{
		if(empty())
			return false;
		_head->setValue(value);
		return true;
	}


	template<class T>
	bool List<T>::updateTail(const T & value)
	{
		if(empty())
			return false;
		_tail->setValue(value);
		return true;
	}


	template<class T>
	T List<T>::readHead() const
	{
		if(empty() == false)
			return _head->getValue();
		throw ListEmptyException();
	}


	template<class T>
	T List<T>::readTail() const
	{
		if(empty() == false)
			return _tail->getValue();
		throw ListEmptyException();
	}

}

#endif
