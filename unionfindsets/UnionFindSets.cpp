#include "stdafx.h"

#include "UnionFindSets.h"

#include <cstring>
using std::memset;

#include <iostream>
using std::cout;

using std::_Copy_impl;

namespace Seven
{
	// non-default constructor
	/*
	the length of _parent[] is size+1,
	because we use the _parent[0] as the virtual root,
	that is,at the beginning,it is the parent of all nodes
	*/
	UnionFindSets::UnionFindSets(int size)
	{
		_size = (size >= 2 ? size : 16);
		_parents = new int[_size];
		memset(_parents, -1, sizeof(int)*_size);
	}


	// copy constructor
	UnionFindSets::UnionFindSets(const UnionFindSets & sets)
	{
		_size = sets._size;
		_parents = new int[_size];
		_Copy_impl(sets._parents, sets._parents + _size, _parents);
	}


	// operator = overwrite
	UnionFindSets & UnionFindSets::operator = (const UnionFindSets & sets)
	{
		if (this != &sets){
			delete[]_parents;
			_size = sets._size;
			_parents = new int[_size];
			_Copy_impl(sets._parents, sets._parents + _size, _parents);
		}
		return *this;
	}


	// restore the sets to original state
	void UnionFindSets::restore()
	{
		memset(_parents, -1, sizeof(int)*_size);
	}


	// deconstructor
	UnionFindSets::~UnionFindSets()
	{
		delete[]_parents;
	}


	// get size
	int UnionFindSets::size()const
	{
		return _size;
	}


	// print the sets
	void UnionFindSets::show()const
	{
		cout << "size: " << _size << '\n';
		for (int i = 0; i < _size; i++)
			cout << "parent[" << i << "]: " << _parents[i] << '\n';
	}


	// find the root of a set which "element" belongs to
	/*
	note "element" as "p"
	when p is not a root:
		note p's parent as "parent"
		note p's grandparent as "grandparent"
		if "grandparent" exists:
			update set p's parent as "grandparent"
		move p to parent
	*/
	int UnionFindSets::find(int element)
	{
		if (element >= 0 && element < _size){
			int parent, grandparent;
			while (_parents[element] >= 0){
				parent = _parents[element];
				grandparent = _parents[parent];
				if (grandparent >= 0)
					_parents[element] = grandparent;
				element = parent;
			}
			return element;
		}
		return _size;
	}


	// union two sets with their roots
	/*
	input : both left and right are roots of sets which they belong to
	        both left and right are [0,size)
	strategy:
		if parent[i] is [0,size):
			i is not a root,and its parent is parent[i]
		if parent[i] is [-size,-1]:
			i is a root,and the size of this set is -parent[i]
		so,when union two sets,we make the smaller set become the child of the bigger set
	*/
	bool UnionFindSets::Union(int left, int right)
	{
		if (left >= 0 && left < _size && right >= 0 && right < _size){
			int tmp = _parents[left] + _parents[right];
			if (_parents[left] < _parents[right]){
				_parents[right] = left;
				_parents[left] = tmp;
			}
			else{
				_parents[left] = right;
				_parents[right] = tmp;
			}
			return true;
		}
		return false;
	}

}