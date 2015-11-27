#ifndef _HUFFLEMAN_H
#define _HUFFLEMAN_H

#include <string>
using std::string;

#include "CharTree.h"

namespace Seven
{
	// string encode and decode
	class Huffleman
	{
	private:
		size_t * count(const string & str)const;  // count for each char (ok)
		CharTree * _tree;                         // the huffleman tree  (ok)
	public:
		// constructor      (ok)
		Huffleman();

		// deconstructor    (ok)
		~Huffleman();

		// encode           (ok)
		string encode(const string & message);

		// decode           (ok)
		string decode(const string & message)const;
	};
}

#endif