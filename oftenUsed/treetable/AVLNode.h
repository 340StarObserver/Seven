#ifndef _AVLNODE_H
#define _AVLNODE_H

#include <iostream>
using std::cout;

namespace Seven
{
	// node for AVL tree
	/*
	< requirements >
	1. type K,V should support default constructor
	2. type K,V should support operator =
	*/
	template<class K,class V>
	class AVLNode
	{
	private:
		K _key;                  // the key of pair
		V _value;                // the value of pair
		int _bf;                 // height(left tree) minus height(right tree)
		bool _useable;           // whether pair is useable,false represents it has been removed
		AVLNode<K, V> * _left;   // left child
		AVLNode<K, V> * _right;  // right child
	public:
		// test print
		/*
		Tip:
		1. parameter "keyPrinter" is a function which to print key
		2. parameter "valuePrinter" is a function which to print value
		3. this method will print:
			{
				the <key,value>,
				the height of left tree minus the height of right tree
				address of left tree
				address of right tree
			}
		*/
		void test(void(*keyPrinter)(const K & key), void(*valuePrinter)(const V & value))const;


		// constructor
		/*
		key   : the key of this <key,value>
		value : the value of this <key,value>
		*/
		AVLNode(const K & key, const V & value);


		// get the key of pair
		K getKey()const;

		// get the value of pair
		V getValue()const;

		// get the address of value
		V * getValueAddress();

		// get height(left tree) minus height(right tree)
		int getBf()const;

		// get left child
		AVLNode<K, V> * getLeft()const;

		// get right child
		AVLNode<K, V> * getRight()const;

		// get whether this pair is useable
		bool getUseable()const;


		// set the key of pair
		void setKey(const K & key);

		// set the value of pair
		void setValue(const V & value);

		// set height(left tree) minus height(right tree)
		void setBf(int bf);

		// set left child
		void setLeft(AVLNode<K, V> * left);

		// set right child
		void setRight(AVLNode<K, V> * right);

		// set whether this pair is useable
		void setUseable(bool useable);

	};

	//----------------------------------------
	// implements:

	// test print
	template<class K,class V>
	void AVLNode<K, V>::test(void(*keyPrinter)(const K & key), void(*valuePrinter)(const V & value))const
	{
		cout << "key        : ";
		keyPrinter(getKey());
		cout << "value      : ";
		valuePrinter(getValue());
		cout << "bf         : " << getBf() << '\n';
		cout << "useable    : " << (getUseable() ? "true" : "false") << '\n';
		cout << "address    : " << (const void * const)this << '\n';
		cout << "address(L) : " << (void *)getLeft() << '\n';
		cout << "address(R) : " << (void *)getRight() << '\n';
		cout << '\n';
	}


	// constructor
	template<class K,class V>
	AVLNode<K, V>::AVLNode(const K & key, const V & value)
	{
		_key = key;
		_value = value;
		_bf = 0;
		_useable = true;
		_left = _right = nullptr;
	}


	// get the key of pair
	template<class K,class V>
	K AVLNode<K, V>::getKey()const
	{
		return _key;
	}

	// get the value of pair
	template<class K,class V>
	V AVLNode<K, V>::getValue()const
	{
		return _value;
	}

	// get address of value
	template<class K,class V>
	V * AVLNode<K, V>::getValueAddress()
	{
		return &_value;
	}

	// get the height of left tree minus the height of right tree
	template<class K,class V>
	int AVLNode<K, V>::getBf()const
	{
		return _bf;
	}

	// get the left child
	template<class K,class V>
	AVLNode<K, V> * AVLNode<K, V>::getLeft()const
	{
		return _left;
	}

	// get the right child
	template<class K,class V>
	AVLNode<K, V> * AVLNode<K, V>::getRight()const
	{
		return _right;
	}

	// get whether this pair is useable
	template<class K,class V>
	bool AVLNode<K, V>::getUseable()const
	{
		return _useable;
	}


	// set the key of pair
	template<class K, class V>
	void AVLNode<K, V>::setKey(const K & key)
	{
		_key = key;
	}

	// set the value of pair
	template<class K, class V>
	void AVLNode<K, V>::setValue(const V & value)
	{
		_value = value;
	}

	// set the height of left tree minus the height of right tree
	template<class K, class V>
	void AVLNode<K, V>::setBf(int bf)
	{
		_bf = bf;
	}

	// set the left child
	template<class K, class V>
	void AVLNode<K, V>::setLeft(AVLNode<K, V> * left)
	{
		_left = left;
	}

	// set the right child
	template<class K, class V>
	void AVLNode<K, V>::setRight(AVLNode<K, V> * right)
	{
		_right = right;
	}

	// set whether this pair is useable
	template<class K, class V>
	void AVLNode<K, V>::setUseable(bool useable)
	{
		_useable = useable;
	}

}

#endif