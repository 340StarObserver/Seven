#ifndef _PAIR_H
#define _PAIR_H

#include <string>
using std::string;

namespace Seven
{
	// pair of (key,value),used for HashTable
	/*
	< requirements >
	1. type T must support default constructor
	2. type T must support operator =
	*/
	template<class T>
	class Pair
	{
	private:
		string _key;                               // the key
		T _value;                                  // the value
	public:
		Pair();                                    // default constructor
		Pair(const string & key, const T & value); // constructor using paraments (key,value)
		// key:
		string getKey()const;                      // get the key
		void setKey(const string & key);           // set the key
		// value:
		T getValue()const;                         // get the value
		T * getValueAddress();                     // get the address of value
		void setValue(const T & value);            // set the value
	};

	//----------------------------------------
	// implements:

	// default constructor
	template<class T>
	Pair<T>::Pair()
	{

	}

	// constructor using paraments (key,value)
	template<class T>
	Pair<T>::Pair(const string & key, const T & value)
	{
		_key = key;
		_value = value;
	}

	// get the key
	template<class T>
	string Pair<T>::getKey()const
	{
		return _key;
	}

	// set the key
	template<class T>
	void Pair<T>::setKey(const string & key)
	{
		_key = key;
	}

	// get the value
	template<class T>
	T Pair<T>::getValue()const
	{
		return _value;
	}

	// get the address of value
	template<class T>
	T * Pair<T>::getValueAddress()
	{
		return &_value;
	}

	// set the value
	template<class T>
	void Pair<T>::setValue(const T & value)
	{
		_value = value;
	}
}

#endif