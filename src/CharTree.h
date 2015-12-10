#ifndef _CHARTREE_H
#define _CHARTREE_H

#include "CharNode.h"

#include <string>
using std::string;

namespace Seven
{
	// tree with huffleman char node
	class CharTree
	{
	private:
		CharNode * _root;  // the root of this huffleman tree
		size_t _size;      // the size of this huffleman tree
	public:
		// constructor
		/*
		count[N] are appearance times of each character        (ok)
		*/
		CharTree(size_t * count, int N);

		// deconstructor                                       (ok)
		~CharTree();
		
		// get root                                            (ok)
		CharNode * getRoot()const;

		// build char-code table                               (ok)
		/*
		the length of the returned array(S) is 256
		the code of char(i) is S[i+128],"i" is [-128,128)
		*/
		string * buildMap()const;
	};
}

#endif