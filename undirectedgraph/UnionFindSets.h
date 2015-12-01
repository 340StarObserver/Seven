#ifndef _UNIONFINDSETS_H
#define _UNIONFINDSETS_H

namespace Seven
{
	// union find sets
	class UnionFindSets
	{
	private:
		int * _parents;    // nodes' parents
		int _size;         // the number of nodes
		int _representNum; // the number of representational elements
	public:
		// constructors:
		UnionFindSets(int size);         // non-default constructor
		                                 // copy constructor
		UnionFindSets(const UnionFindSets & sets);
		                                 // operator = overwrite
		UnionFindSets & operator = (const UnionFindSets & sets);

		// clear:
		void restore();                  // restore the sets
		~UnionFindSets();                // deconstructor

		// show the sets
		void show()const;                // print the sets

		// attribute
		int size()const;                 // get size
		int representNum()const;         // get the number of representational elements
		// that is, how many sets in this unionfindsets

		// find
		int find(int element);           // find the root of a set which "element" belongs to

		// union
		bool Union(int left, int right); // union two sets with their roots
	};
}

#endif