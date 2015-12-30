#ifndef _TREETABLE_H
#define _TREETABLE_H

#include "AVLNode.h"

namespace Seven
{
	// tree table which is based on AVL tree
	/*
	< requirements >
	1. type K,V should support default constructor
	2. type K,V should support operator =

	< tips >
	1. parameter "compare" is used to compare two keys
		compare(left,right) < 0 === left < right
		compare(left,right) = 0 === left = right
		compare(left,right) > 0 === left > right
	2. the differences among ( add , replace , set ):
		add:
			if key not exists,add this <key,value>,return true;
			if key exists,do nothing,return false;
		replace:
			if key not exists,do nothing,return false;
			if key exists,update the value,return true;
		set:
			if key not exists,add this <key,value>
			if key exists,update the value
	*/
	template<class K,class V>
	class TreeTable
	{
	private:
		AVLNode<K, V> * _root;  // the root of the AVL tree
		size_t _size;           // the number of nodes
	private:
		// delete a subtree whose root is "p"     (ok)
		void del(AVLNode<K, V> * p);

		// find the node with a given key         (ok)
		AVLNode<K, V> * find(const K & key, int(*compare)(const K & left, const K & right));

		// add or set a <key,value>               (ok)
		bool work(bool mode, const K & key, const V & value, int(*compare)(const K & left, const K & right));

	public:
		// construct an empty table               (ok)
		TreeTable();

		// get the size of the table              (ok)
		size_t size()const;

		// whether the table is empty             (ok)
		bool empty()const;

		// clear the whole table                  (ok)
		void clear();

		// deconstructor                          (ok)
		~TreeTable();


		// get the value by a given key           (ok)
		V * get(const K & key, int(*compare)(const K & left, const K & right));

		// replace the value of a <key,value>     (ok)
		bool replace(const K & key, const V & value, int(*compare)(const K & left, const K & right));

		// set a <key,value>                      (ok)
		void set(const K & key, const V & value, int(*compare)(const K & left, const K & right));

		// add a <key,value>                      (ok)
		bool add(const K & key, const V & value, int(*compare)(const K & left, const K & right));

	};

	//----------------------------------------
	// implements:

	// construct an empty table
	template<class K,class V>
	TreeTable<K, V>::TreeTable()
	{
		_root = nullptr;
		_size = 0;
	}


	// get the size of the table
	template<class K,class V>
	size_t TreeTable<K, V>::size()const
	{
		return _size;
	}


	// whether the table is empty
	template<class K,class V>
	bool TreeTable<K, V>::empty()const
	{
		return _size == 0;
	}


	// clear the whole table
	template<class K,class V>
	void TreeTable<K, V>::clear()
	{
		del(_root);
		_root = nullptr;
		_size = 0;
	}


	// deconstructor
	template<class K,class V>
	TreeTable<K, V>::~TreeTable()
	{
		clear();
	}


	// delete a subtree whose root is "p"
	template<class K,class V>
	void TreeTable<K, V>::del(AVLNode<K, V> * p)
	{
		if (p)
		{
			del(p->getLeft());
			del(p->getRight());
			delete p;
		}
	}


	// find a node with a given key
	/*
	Tips:
	1. parameter "key" is the given key
	2. parameter "compare" is the strategy how to compare two keys
	3. if not found,it will return null
	*/
	template<class K,class V>
	AVLNode<K, V> * TreeTable<K, V>::find(const K & key, int(*compare)(const K & left, const K & right))
	{
		AVLNode<K, V> * p = _root;
		int t;
		while (p)
		{
			t = compare(key, p->getKey());
			if (t == 0)
				return p;
			p = (t < 0 ? p->getLeft() : p->getRight());
		}
		return nullptr;
	}


	// get the value by a give key
	/*
	Tips:
	1. parameter "key" is the given key
	2. parameter "compare" is the strategy how to compare two keys
		compare(left,right) < 0 === left < right
		compare(left,right) = 0 === left = right
		compare(left,right) > 0 === left > right
	3. if found     : it will return the address of value
	4. if not found : it will return null
	*/
	template<class K,class V>
	V * TreeTable<K, V>::get(const K & key, int(*compare)(const K & left, const K & right))
	{
		AVLNode<K, V> * p = find(key, compare);
		return (p == nullptr ? nullptr : p->getValueAddress());
	}


	// replace the value of a <key,value>
	/*
	Tips:
	1. parameter "key" is the given key
	2. parameter "value" is the new value
	3. parameter "compare" is the strategy how to compare two keys
		compare(left,right) < 0 === left < right
		compare(left,right) = 0 === left = right
		compare(left,right) > 0 === left > right
	4. if key not exists,do nothing,return false;
	5. if key exists,update the value,return true;
	*/
	template<class K,class V>
	bool TreeTable<K, V>::replace(const K & key, const V & value, int(*compare)(const K & left, const K & right))
	{
		AVLNode<K, V> * p = find(key, compare);
		if (p){
			p->setValue(value);
			return true;
		}
		return false;
	}


	// set a <key,value>
	/*
	1. parameter "key" is the given key
	2. parameter "value" is the new value
	3. parameter "compare" is the strategy how to compare two keys
		compare(left,right) < 0 === left < right
		compare(left,right) = 0 === left = right
		compare(left,right) > 0 === left > right
	4. if key not exists,add this <key,value>
	5. if key exists,update the value
	*/
	template<class K,class V>
	void TreeTable<K, V>::set(const K & key, const V & value, int(*compare)(const K & left, const K & right))
	{
		work(true, key, value, compare);
	}


	// add a <key,value>
	/*
	1. parameter "key" is the given key
	2. parameter "value" is the new value
	3. parameter "compare" is the strategy how to compare two keys
		compare(left,right) < 0 === left < right
		compare(left,right) = 0 === left = right
		compare(left,right) > 0 === left > right
	4. if key not exists,add this <key,value>,return true;
	5. if key exists,do nothing,return false;
	*/
	template<class K,class V>
	bool TreeTable<K, V>::add(const K & key, const V & value, int(*compare)(const K & left, const K & right))
	{
		return work(false, key, value, compare);
	}


	// add or set a <key,value>
	/*
	Tips:
	1. parameter "mode" is the mode, true is set, false is add
	1. parameter "key" is the given key
	2. parameter "value" is the new value
	3. parameter "compare" is the strategy how to compare two keys

	Method:
	1. if table is empty:
		make the root point to the new node
		increase the size
	2. assume:
		{
			a  : most recent node with |bf|=1 before insert
			pa : the parent of a
			p  : used to find the location to insert from the root
			pp : the parent of p
			y  : the new node
			b  : the child of a at that path
			c  : the child of b at that path
		}
	3. find the location to insert and the most recent node with |bf|=1 before insert
	4. when you do step 3,if find the same key,update the value or do nothing according to mode
	5. create a new node and connect to pp
	6. judge which child of "a" should be "b"
	7. modify the bf of nodes at that path
	8. if now is balanced,return
	9. rotate
	10. modify the node which is the parent of the subtree which has been rotated
	*/
	template<class K,class V>
	bool TreeTable<K, V>::work(bool mode, const K & key, const V & value, int(*compare)(const K & left, const K & right))
	{
		if (_size == 0){
			_root = new AVLNode<K, V>(key, value);
			_size = 1;
			return true;
		}

		AVLNode<K, V> * a = _root, *pa = nullptr, *p = _root, *pp = nullptr, *b, *c;
		int t, d;

		while (p){
			if (p->getBf() != 0){
				a = p;
				pa = pp;
			}
			t = compare(key, p->getKey());
			if (t == 0){
				if (mode)
					p->setValue(value);
				return mode;
			}
			pp = p;
			p = (t < 0 ? p->getLeft() : p->getRight());
		}

		AVLNode<K, V> * y = new AVLNode<K, V>(key, value);
		_size++;
		if (t < 0)
			pp->setLeft(y);
		else
			pp->setRight(y);

		if (compare(key, a->getKey()) > 0){
			b = p = a->getRight();
			d = -1;
		}
		else{
			b = p = a->getLeft();
			d = 1;
		}

		while (p != y){
			if (compare(key, p->getKey()) > 0){
				p->setBf(-1);
				p = p->getRight();
			}
			else{
				p->setBf(1);
				p = p->getLeft();
			}
		}

		if (a->getBf() == 0 || a->getBf() + d == 0){
			a->setBf(a->getBf() + d);
			return true;
		}

		if (d == 1){
			if (b->getBf() == 1){
				a->setLeft(b->getRight());
				b->setRight(a);
				a->setBf(0);
				b->setBf(0);
			}
			else{
				c = b->getRight();
				a->setLeft(c->getRight());
				b->setRight(c->getLeft());
				c->setLeft(b);
				c->setRight(a);
				switch (c->getBf()){
				case -1:{ a->setBf(0); b->setBf(1); break; }
				case 0:{ a->setBf(0); b->setBf(0); break; }
				case 1:{ a->setBf(-1); b->setBf(0); break; }
				}
				c->setBf(0);
				b = c;
			}
		}
		else{
			if (b->getBf() == -1){
				a->setRight(b->getLeft());
				b->setLeft(a);
				a->setBf(0);
				b->setBf(0);
			}
			else{
				c = b->getLeft();
				a->setRight(c->getLeft());
				b->setLeft(c->getRight());
				c->setLeft(a);
				c->setRight(b);
				switch (c->getBf()){
				case -1:{ a->setBf(1); b->setBf(0); break; }
				case 0:{ a->setBf(0); b->setBf(0); break; }
				case 1:{ a->setBf(0); b->setBf(-1); break; }
				}
				c->setBf(0);
				b = c;
			}
		}

		if (pa == nullptr)
			_root = b;
		else if (a == pa->getLeft())
			pa->setLeft(b);
		else
			pa->setRight(b);
		return true;
	}

}

#endif