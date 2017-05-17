/*
 * Author 	: 	Lv Yang
 * Create 	: 	17 May 2017
 * Modify 	: 	17 May 2017
 * Version 	: 	1.0
 */

#ifndef _UFSET_H
#define _UFSET_H

#include <cstring>

namespace Seven
{
	class UFset
	{
	private:
		/*
		 * 1. _relations[_size + 1]
		 *    really in use is _relations[1] ~ _relations[_size]
		 *
		 * 2. at the begin, all elements is 0
		 *    it means there are no relation with each other
		 *
		 * 3. _relations[i] = j
		 *    j == 0 : element i is a representative item of one equivalence class
		 *    j != 0 : element i has relation with j
		 *             we often call j is i's parent
		 *             you can find i's ancestor(a representative item) by a loop
		 */
		std::size_t * _relations;

		std::size_t _size;

		/*
		 * all elements can be divided into how many equivalence class
		 * 1. elements in the same equivalence class have relation with each other
		 *    elements in different equivalence class have no relation
		 *
		 * 2. at the begin, there are _size equivalence class
		 *
		 * 3. after build some relations, this value will decrease
		 */
		std::size_t _groups;

	public:
		UFset(std::size_t size);

		~UFset();

		// clean all relations
		void restore();

		/*
		 * resize _relations[]
		 * !-- only can be resized to a larger one
		 */
		void resize(std::size_t size);

		// get the number of elements
		std::size_t getSize() const;

		// get the number of equivalence class
		std::size_t getGroups() const;

		/*
		 * find the representative element of a equivalence class which it belong to
		 * !-- if parameter invalid, return 0
		 */
		std::size_t find(std::size_t item);

		// build relation between two elements
		void link(std::size_t lhs, std::size_t rhs);
	};


	UFset::UFset(std::size_t size) : _size(size), _groups(size)
	{
		_relations = new std::size_t[_size + 1];
		std::memset(_relations, 0, (_size + 1) * sizeof(std::size_t));
	}


	UFset::~UFset()
	{
		delete []_relations;
	}


	void UFset::restore()
	{
		std::memset(_relations, 0, (_size + 1) * sizeof(std::size_t));
		_groups = _size;
	}


	void UFset::resize(std::size_t size)
	{
		if(size > _size)
		{
			std::size_t * tmp = new std::size_t[size + 1];
			for(std::size_t i = 0; i <= _size; i++)
				tmp[i] = _relations[i];
			for(std::size_t i = _size + 1; i <= size; i++)
				tmp[i] = 0;

			delete []_relations;

			_relations = tmp;
			_groups += (size - _size);
			_size = size;
		}
	}


	std::size_t UFset::getSize() const
	{
		return _size;
	}


	std::size_t UFset::getGroups() const
	{
		return _groups;
	}


	std::size_t UFset::find(std::size_t item)
	{
		if(item > 0 && item <= _size)
		{
			std::size_t p = item;
			while(_relations[p] != 0)
				p = _relations[p];

			std::size_t q;
			while(_relations[item] != 0)
			{
				q = _relations[item];
				_relations[item] = p;
				item = q;
			}

			return p;
		}
		return 0;
	}


	void UFset::link(std::size_t lhs, std::size_t rhs)
	{
		lhs = find(lhs);
		rhs = find(rhs);
		if(lhs != 0 && rhs != 0 && lhs != rhs)
		{
			_relations[lhs] = rhs;
			_groups--;
		}
	}

}

#endif
