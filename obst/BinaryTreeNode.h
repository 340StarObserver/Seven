#ifndef _BINARYTREENODE_H
#define _BINARYTREENODE_H

#include <iostream>
using std::cout;

namespace Seven
{
	// node of binary tree
	/*
	< requirements >
	1. type T should support default constructor
	2. type T should support operator =
	*/
	template<class T>
	class BinaryTreeNode
	{
	private:
		T _value;                      // its value
		BinaryTreeNode<T> * _parent;   // its parent node address
		BinaryTreeNode<T> * _left;     // its left child node address
		BinaryTreeNode<T> * _right;    // its right child node address
	public:
		// test:
		void print(void(*showT)(const T & value))const; // test print this node (ok)
		
		// constructors:
		BinaryTreeNode();                               // default constructor  (ok)
		BinaryTreeNode(const T & value);                // transfer constructor (ok)

		// get:
		T * getValue();                                 // get its value address(ok)
		T value()const;                                 // get its value        (ok)
		BinaryTreeNode<T> * getParent()const;           // get its parent       (ok)
		BinaryTreeNode<T> * getLeft()const;             // get its left child   (ok)
		BinaryTreeNode<T> * getRight()const;            // get its right child  (ok)

		// set:
		void setValue(const T & value);                 // set its value        (ok)
		void setParent(BinaryTreeNode<T> * parent);     // set its parent       (ok)
		void setLeft(BinaryTreeNode<T> * left);         // set its left child   (ok)
		void setRight(BinaryTreeNode<T> * right);       // set its right child  (ok)

		// rotate:
		void rotateClockWise();                         // clock rotate         (ok)
		void rotateAntiClockWise();                     // anti clock rotate    (ok)
	};

	//----------------------------------------
	// implements:

	// test print
	template<class T>
	void BinaryTreeNode<T>::print(void(*showT)(const T & value))const
	{
		cout << "this value: \n";
		showT(_value);
		cout << "this address       : " << (const void * const)this << '\n';
		cout << "parent address     : " << (void *)_parent << '\n';
		cout << "left child address : " << (void *)_left << '\n';
		cout << "right child address: " << (void *)_right << "\n\n";
	}

	// default constructor
	template<class T>
	BinaryTreeNode<T>::BinaryTreeNode()
	{
		_parent = nullptr;
		_left = nullptr;
		_right = nullptr;
	}

	// transfer constructor
	template<class T>
	BinaryTreeNode<T>::BinaryTreeNode(const T & value)
	{
		_value = value;
		_parent = nullptr;
		_left = nullptr;
		_right = nullptr;
	}

	// get its value address
	template<class T>
	T * BinaryTreeNode<T>::getValue()
	{
		return &_value;
	}

	// get its value
	template<class T>
	T BinaryTreeNode<T>::value()const
	{
		return _value;
	}

	// get its parent
	template<class T>
	BinaryTreeNode<T> * BinaryTreeNode<T>::getParent()const
	{
		return _parent;
	}

	// get its left child
	template<class T>
	BinaryTreeNode<T> * BinaryTreeNode<T>::getLeft()const
	{
		return _left;
	}

	// get its right child
	template<class T>
	BinaryTreeNode<T> * BinaryTreeNode<T>::getRight()const
	{
		return _right;
	}

	// set its value
	template<class T>
	void BinaryTreeNode<T>::setValue(const T & value)
	{
		_value = value;
	}

	// set its parent
	template<class T>
	void BinaryTreeNode<T>::setParent(BinaryTreeNode<T> * parent)
	{
		_parent = parent;
	}

	// set its left child
	template<class T>
	void BinaryTreeNode<T>::setLeft(BinaryTreeNode<T> * left)
	{
		_left = left;
	}

	// set its right child
	template<class T>
	void BinaryTreeNode<T>::setRight(BinaryTreeNode<T> * right)
	{
		_right = right;
	}

	// clock wise rotate
	/*
	this node needs to have left child node
	1. note this's parent as "p"
	   note this's left as "L"
	   note L's right as "LR"
	2. connect L and P
	3. connect LR to this's left
	4. connect this to L's right
	*/
	template<class T>
	void BinaryTreeNode<T>::rotateClockWise()
	{
		if (_left == nullptr)
			return;
		BinaryTreeNode<T> * p = _parent;
		BinaryTreeNode<T> * L = _left;
		BinaryTreeNode<T> * LR = L->_right;
		L->_parent = p;
		if (p)
		{
			if (p->_left == this)
				p->_left = L;
			else
				p->_right = L;
		}
		_left = LR;
		if (LR)
			LR->_parent = this;
		L->_right = this;
		_parent = L;
	}

	// anti clock wise rotate
	/*
	this node needs to have right child node
	1. note this's parent as "p"
	   note this's right as "R"
	   note R's left as "RL"
	2. connect R and p
	3. connect RL to this' right
	4. connect this to R's left
	*/
	template<class T>
	void BinaryTreeNode<T>::rotateAntiClockWise()
	{
		if (_right == nullptr)
			return;
		BinaryTreeNode<T> * p = _parent;
		BinaryTreeNode<T> * R = _right;
		BinaryTreeNode<T> * RL = R->_left;
		R->_parent = p;
		if (p)
		{
			if (p->_left == this)
				p->_left = R;
			else
				p->_right = R;
		}
		_right = RL;
		if (RL)
			RL->_parent = this;
		R->_left = this;
		_parent = R;
	}

}

#endif