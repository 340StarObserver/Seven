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
	private:
		// connect node to pos's left tail, used in rmParent,rmLeft,rmRight     (ok)
		static void insertToLeftTail(BinaryTreeNode<T> * pos, BinaryTreeNode<T> * node);

		// connect node to pos's right tail, used in rmParent,rmLeft,rmRight    (ok)
		static void insertToRightTail(BinaryTreeNode<T> * pos, BinaryTreeNode<T> * node);

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

		// delete:
		void rmParent();                                // remove its parent    (ok)
		void rmLeft();                                  // remove its left      (ok)
		void rmRight();                                 // remove its right     (ok)

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

	// connect node to pos's left tail, used in rmParent,rmLeft,rmRight
	template<class T>
	void BinaryTreeNode<T>::insertToLeftTail(BinaryTreeNode<T> * pos, BinaryTreeNode<T> * node)
	{
		if (pos == nullptr || node == nullptr)
			return;
		BinaryTreeNode<T> * p = pos;
		while (p->_left)
			p = p->_left;
		p->_left = node;
		node->_parent = p;
	}

	// connect node to pos's right tail, used in rmParent,rmLeft,rmRight
	template<class T>
	void BinaryTreeNode<T>::insertToRightTail(BinaryTreeNode<T> * pos, BinaryTreeNode<T> * node)
	{
		if (pos == nullptr || node == nullptr)
			return;
		BinaryTreeNode<T> * p = pos;
		while (p->_right)
			p = p->_right;
		p->_right = node;
		node->_parent = p;
	}

	// remove its parent node
	/*
	1. if its parent doesn't exist: over
	2. note its parent as "p"
	   note p's parent as "g"
	3. connect this and g
    4. if p's left child is this:
	      note p's right child as "t"
		  connect t to this's right tail
	   else:
	      note p's left child as "t"
		  connect t to this's left tail
	5. delete p
	*/
	template<class T>
	void BinaryTreeNode<T>::rmParent()
	{
		if (_parent == nullptr)
			return;
		BinaryTreeNode<T> * p = _parent;
		BinaryTreeNode<T> * g = p->_parent;
		_parent = g;
		if (g)
		{
			if (p == g->_left)
				g->_left = this;
			else
				g->_right = this;
		}
		BinaryTreeNode<T> * t = nullptr;
		if (p->_left == this)
		{
			t = p->_right;
			insertToRightTail(this, t);
		}
		else
		{
			t = p->_left;
			insertToLeftTail(this, t);
		}
		delete p;
	}

	// remove its left node
	/*
	1. if its left node doesn't exist: over
	2. note its left node as "L"
	   note L's left node as "LL"
	   note L's right node as "LR"
	3. if both LL and LR not exist:
	   {
	      set this's left to null
		  delete L
		  over
	   }
	4. if LL exists,but LR doesn't exist:
	   {
	      connect this and LL
		  delete L
		  over
	   }
	5. if LL doesn't exist,but LR exists:
	   {
	      connect this and LR
		  delete L
		  over
	   }
	6. if both LL and LR exist:
	   {
	      insert LR to LL's right tail
		  connect this and LL
		  delete L
		  over
	   }
	*/
	template<class T>
	void BinaryTreeNode<T>::rmLeft()
	{
		if (_left == nullptr)
			return;
		BinaryTreeNode<T> * L = _left;
		BinaryTreeNode<T> * LL = L->_left;
		BinaryTreeNode<T> * LR = L->_right;
		if (!LL && !LR)
		{
			_left = nullptr;
			delete L;
			return;
		}
		if (LL && !LR)
		{
			_left = LL;
			LL->_parent = this;
			delete L;
			return;
		}
		if (!LL && LR)
		{
			_left = LR;
			LR->_parent = this;
			delete L;
			return;
		}
		insertToRightTail(LL, LR);
		_left = LL;
		LL->_parent = this;
		delete L;
	}

	// remove its right node
	/*
	1. if its right node doesn't exist: over
	2. note its right node as "R"
	   note R's left node as "RL"
	   note R's right node as "RR"
	3. if both RL and RR not exist:
	   {
	      set this's right to null
		  delete R
		  over
	   }
	4. if RL exists,but RR doesn't exist:
	   {
	      connect this and RL
		  delete R
		  over
	   }
	5. if RL doesn't exist,but RR exists:
	   {
	      connect this and RR
		  delete R
		  over
	   }
	6. if both RL and RR exist:
	   {
	      insert RR to RL's right tail
		  connect this and RL
		  delete R
		  over
	   }
	*/
	template<class T>
	void BinaryTreeNode<T>::rmRight()
	{
		if (_right == nullptr)
			return;
		BinaryTreeNode<T> * R = _right;
		BinaryTreeNode<T> * RL = R->_left;
		BinaryTreeNode<T> * RR = R->_right;
		if (!RL && !RR)
		{
			_right = nullptr;
			delete R;
			return;
		}
		if (RL && !RR)
		{
			_right = RL;
			RL->_parent = this;
			delete R;
			return;
		}
		if (!RL && RR)
		{
			_right = RR;
			RR->_parent = this;
			delete R;
			return;
		}
		insertToRightTail(RL, RR);
		_right = RL;
		RL->_parent = this;
		delete R;
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