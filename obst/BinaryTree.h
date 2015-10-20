#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include "BinaryTreeNode.h"
#include "Stack.h"
#include "Queue.h"
#include "ObstStrategy.h"

namespace Seven
{
	// binary tree
	/*
	< requirements >
	1. type T should support default constructor
	2. type T should support operator =
	*/
	template<class T>
	class BinaryTree
	{
	private:
		BinaryTreeNode<T> * _root;  // the root node of the tree
		size_t _size;               // the size of the tree
	private:
		static BinaryTreeNode<T> * copySubTree(BinaryTreeNode<T> * p); // copy sub tree (ok)
	public:
		// constructors:
		BinaryTree();                                            // default constructor (ok)
		static BinaryTree<T> * create();                         // create an empty tree(ok)
		                                                         // build optimial bst  (ok)
		BinaryTree(T * values, float * probalities, unsigned int num, ObstStrategy * strategyObj, int(*compare)(const T & left, const T & right));
		BinaryTree(const BinaryTree<T> & tree);                  // copy constructor    (ok)
		BinaryTree<T> & operator = (const BinaryTree<T> & tree); // operator = overwrite(ok)

		// visit:
		LinkedList<T> * preVisit()const;                         // prefix order        (ok)
		LinkedList<T> * inVisit()const;                          // infix order         (ok)
		LinkedList<T> * postVisit()const;                        // postfix order       (ok)
		LinkedList<T> * levelVisit()const;                       // level order         (ok)

		// clean:
		void clear();                                            // clear the tree      (ok)
		~BinaryTree();                                           // deconstructor       (ok)

		// attributes:
		bool empty()const;                                       // whether is empty    (ok)
		size_t size()const;                                      // get the size of tree(ok)

		// CURD:
		                                                         // insert element      (ok)
		bool insert(const T & value, int(*compare)(const T & left, const T & right));
		                                                         // search element      (ok)
		bool contains(const T & value, int(*compare)(const T & left, const T & right))const;
		                                                         // remove element      (ok)
		bool remove(const T & value, int(*compare)(const T & left, const T & right));
	};

	//----------------------------------------
	// implements:

	// default constructor
	template<class T>
	BinaryTree<T>::BinaryTree()
	{
		_root = nullptr;
		_size = 0;
	}


	// create an empty tree
	template<class T>
	BinaryTree<T> * BinaryTree<T>::create()
	{
		return new BinaryTree<T>();
	}


	// copy sub binary search tree
	template<class T>
	BinaryTreeNode<T> * BinaryTree<T>::copySubTree(BinaryTreeNode<T> * p)
	{
		if (!p)
			return nullptr;
		BinaryTreeNode<T> * root = new BinaryTreeNode<T>(p->value());
		if (p->getLeft())
		{
			BinaryTreeNode<T> * L = copySubTree(p->getLeft());
			root->setLeft(L);
			L->setParent(root);
		}
		if (p->getRight())
		{
			BinaryTreeNode<T> * R = copySubTree(p->getRight());
			root->setRight(R);
			R->setParent(root);
		}
		return root;
	}


	// copy constructor
	template<class T>
	BinaryTree<T>::BinaryTree(const BinaryTree<T> & tree)
	{
		_root = copySubTree(tree._root);
		_size = tree._size;
	}


	// construct an optimial binary search tree
	/*
	paraments:
	{
	values[]      : the list of values
	probalitites[]: probalility of search of each value in values[]
	num           : the number of values
	strategyObj   : strategy for building optimial binary search tree
	compare       : a function to compare two objects
	}
	steps:
	{
	1. ascending sort the values[],
	and sort the probalities[] based on values[]
	for example:
	values[]     : 3,   4,    5,   1,    2
	probalities[]: 0.1, 0.15, 0.2, 0.25, 0.3
	after sort:
	values[]     : 1,    2,    3,   4,    5
	probalities[]: 0.25, 0.3,  0.1, 0.15, 0.2
	2. use strategyObj to form the prefix order
	3. insert values by the prefix order
	4. delete the prefix order
	}
	*/
	template<class T>
	BinaryTree<T>::BinaryTree(T * values, float * probalities, unsigned int num, ObstStrategy * strategyObj, int(*compare)(const T & left, const T & right))
	{
		bool w = true;
		T t1;
		float t2;
		for (unsigned int k = 0; k < num - 1 && w; k++)
		{
			w = false;
			for (unsigned int i = 0; i < num - k - 1; i++)
			{
				if (compare(values[i], values[i + 1]) > 0)
				{
					w = true;
					t1 = values[i];
					values[i] = values[i + 1];
					values[i + 1] = t1;
					t2 = probalities[i];
					probalities[i] = probalities[i + 1];
					probalities[i + 1] = t2;
				}
			}
		}
		int * order = strategyObj->strategy(probalities, num);
		for (unsigned int i = 0; i < num; i++)
			insert(values[order[i]], compare);
		delete[]order;
	}


	// overwrite of operator =
	template<class T>
	BinaryTree<T> & BinaryTree<T>::operator = (const BinaryTree<T> & tree)
	{
		if (&tree != this)
		{
			clear();
			_root = copySubTree(tree._root);
			_size = tree._size;
		}
		return *this;
	}


	// clear the tree
	/*
	1. use bfs to get all the nodes of this tree
	2. delete all the nodes
	3. let the root is null
	   let the size is zero
	*/
	template<class T>
	void BinaryTree<T>::clear()
	{
		if (_size == 0)
			return;
		BinaryTreeNode<T> ** nodes = new BinaryTreeNode<T>*[_size];
		size_t i = 0;
		Queue<BinaryTreeNode<T> *> Q;
		BinaryTreeNode<T> * p = _root;
		Q.push(p);
		while (!Q.empty())
		{
			p = Q.front();
			Q.pop();
			nodes[i++] = p;
			if (p->getLeft())
				Q.push(p->getLeft());
			if (p->getRight())
				Q.push(p->getRight());
		}
		for (i = 0; i < _size; i++)
			delete nodes[i];
		delete[]nodes;
		_root = nullptr;
		_size = 0;
	}


	// deconstructor
	template<class T>
	BinaryTree<T>::~BinaryTree()
	{
		clear();
	}


	// whether this tree is emtpy
	template<class T>
	bool BinaryTree<T>::empty()const
	{
		return _size == 0;
	}


	// get the size of this tree
	template<class T>
	size_t BinaryTree<T>::size()const
	{
		return _size;
	}


	// prefix order of nodes
	/*
	order by: this -> leftSubTree -> rightSubTree
	step:
	{
	   1. create a list for saving data
	   2. create the work stack called "S"
	   3. push root node into S
	   4. while S is not empty:
	         note the top of the work stack as "p"
			 S exec pop
			 insert p's value into the list
			 push p's right child into S
			 push p's left child into S
	   5. return the list
	}
	*/
	template<class T>
	LinkedList<T> * BinaryTree<T>::preVisit()const
	{
		LinkedList<T> * list = LinkedList<T>::create();
		Stack<BinaryTreeNode<T> *> S;
		BinaryTreeNode<T> * p = _root;
		if (p)
			S.push(p);
		while (!S.empty())
		{
			p = S.top();
			S.pop();
			list->insertTail(p->value());
			if (p->getRight())
				S.push(p->getRight());
			if (p->getLeft())
				S.push(p->getLeft());
		}
		return list;
	}


	// infix order of nodes
	/*
	order by: leftSubTree -> this -> rightSubTree
	step:
	{
	   1. create a list for saving data
	   2. create the work stack called "S"
	   3. note the root node as "p"
	   3. do:
	         while p exists:
			    push p into S
				make p point to its left child
			 if S is not empty:
			    note the top of S to p
				S exec pop
				insert p's value into the list
				make p point to its right child
		  while S is not empty or p exists
	   4. return the list
	}
	*/
	template<class T>
	LinkedList<T> * BinaryTree<T>::inVisit()const
	{
		LinkedList<T> * list = LinkedList<T>::create();
		Stack<BinaryTreeNode<T> *> S;
		BinaryTreeNode<T> * p = _root;
		do
		{
			while (p)
			{
				S.push(p);
				p = p->getLeft();
			}
			if (!S.empty())
			{
				p = S.top();
				S.pop();
				list->insertTail(p->value());
				p = p->getRight();
			}
		} while (!S.empty() || p);
		return list;
	}


	// postfix(suffix) order of nodes
	/*
	order by: leftSubTree -> rightSubTree -> this
	steps:
	{
	   first introduce three states of a node such as "p"
	      state = 0 : haven't visited p's left child,p's right child and p itself
	      state = 1 : haven't visited p's right child and p itself
	      state = 2 : haven't visited p itself
	   Then the real steps:
	   1. create a list for saving data
	   2. create a node stack called "A"
	      create a state stack called "B"
	   3. push the root node into A
	      push 0 into B
	   4. while A is not empty:
	         note A's top as topA
			 note B's top as topB
			 if topB is 0:
			    set topB to 1
				push topA's left child to A
				push 0 to B
			 else if topB is 1:
			    set topB to 2
				push topA's left child to A
				push 0 to B
			 else:
			    insert topA's value into the list
				A exec pop
				B exec pop
	   5. return the list
	}
	*/
	template<class T>
	LinkedList<T> * BinaryTree<T>::postVisit()const
	{
		LinkedList<T> * list = LinkedList<T>::create();
		Stack<BinaryTreeNode<T> *> A;
		Stack<char> B;
		if (_root)
		{
			A.push(_root);
			B.push('0');
		}
		BinaryTreeNode<T> * topA = nullptr;
		char * topB = nullptr;
		while (!A.empty())
		{
			topA = A.top();
			topB = B.peek();
			if (*topB == '0')
			{
				*topB = '1';
				if (topA->getLeft())
				{
					A.push(topA->getLeft());
					B.push('0');
				}
			}
			else if (*topB == '1')
			{
				*topB = '2';
				if (topA->getRight())
				{
					A.push(topA->getRight());
					B.push('0');
				}
			}
			else
			{
				list->insertTail(topA->value());
				A.pop();
				B.pop();
			}
		}
		return list;
	}


	// level order of nodes
	/*
	order by the depth(ascending) of nodes
	steps:
	{
	   1. create a list for saving data
	   2. create a work queue called "Q"
	   3. push root into Q
	   4. while Q is not empty:
	         note Q's front as "p"
			 Q exec pop
			 insert p's value into the list
			 push p's left child into Q
			 push p's right child into Q
	   5. return the list
	}
	*/
	template<class T>
	LinkedList<T> * BinaryTree<T>::levelVisit()const
	{
		LinkedList<T> * list = LinkedList<T>::create();
		Queue<BinaryTreeNode<T> *> Q;
		BinaryTreeNode<T> * p = _root;
		if (p)
			Q.push(p);
		while (!Q.empty())
		{
			p = Q.front();
			Q.pop();
			list->insertTail(p->value());
			if (p->getLeft())
				Q.push(p->getLeft());
			if (p->getRight())
				Q.push(p->getRight());
		}
		return list;
	}


	// search whether this tree has such an element
	/*
	the parament "value" is the element to search
	the parament "compare" is to compare element,and its rules are:
	    compare(left,right)<0 : left<right
	    compare(left,right)=0 : left=right
	    compare(left,right)>0 : left>right
	*/
	template<class T>
	bool BinaryTree<T>::contains(const T & value, int(*compare)(const T & left, const T & right))const
	{
		BinaryTreeNode<T> * p = _root;
		int res;
		while (p)
		{
			res = compare(value, p->value());
			if (res == 0)
				return true;
			p = (res < 0 ? p->getLeft() : p->getRight());
		}
		return false;
	}


	// insert element
	/*
	the parament "value" is the element to insert
	the parament "compare" is to compare element,and its rules are:
	    compare(left,right)<0 : left<right
	    compare(left,right)=0 : left=right
	    compare(left,right)>0 : left>right
	*/
	template<class T>
	bool BinaryTree<T>::insert(const T & value, int(*compare)(const T & left, const T & right))
	{
		BinaryTreeNode<T> * node = new BinaryTreeNode<T>(value);
		if (_size == 0)
		{
			_root = node;
			_size = 1;
			return true;
		}
		BinaryTreeNode<T> * p = _root;
		bool w;
		int res;
		while (1)
		{
			res = compare(value, p->value());
			if (res == 0)
			{
				delete node;
				return false;
			}
			if (res < 0)
			{
				if (p->getLeft())
					p = p->getLeft();
				else
				{
					w = false;
					break;
				}
			}
			else
			{
				if (p->getRight())
					p = p->getRight();
				else
				{
					w = true;
					break;
				}
			}
		}
		node->setParent(p);
		if (w)
			p->setRight(node);
		else
			p->setLeft(node);
		_size++;
		return true;
	}


	// remove element based on the value of node
	/*
	note the node which needs to be removed as "p"
	there are some conditions according to p (when p exists)
	1. p is the root, and p has no child
	2. p is the root, and p has left chld
	3. p is the root, and p has right child
	4. p is not the root
	*/
	template<class T>
	bool BinaryTree<T>::remove(const T & value, int(*compare)(const T & left, const T & right))
	{
		BinaryTreeNode<T> * p = _root;
		int res;
		while (p)
		{
			res = compare(value, p->value());
			if (res == 0)
				break;
			p = (res < 0 ? p->getLeft() : p->getRight());
		}
		if (!p)
			return false;
		if (p == _root)
		{
			BinaryTreeNode<T> * L = p->getLeft();
			BinaryTreeNode<T> * R = p->getRight();
			if (!L && !R)
			{
				delete _root;
				_root = nullptr;
			}
			else if (L)
			{
				L->rmParent();
				_root = L;
			}
			else
			{
				R->rmParent();
				_root = R;
			}
		}
		else
		{
			BinaryTreeNode<T> * t = p->getParent();
			if (t->getLeft() == p)
				t->rmLeft();
			else
				t->rmRight();
		}
		_size--;
		return true;
	}


}

#endif