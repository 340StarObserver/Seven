#ifndef _HASHSTRATEGY_H
#define _HASHSTRATEGY_H

#include <string>
using std::string;

namespace Seven
{
	// a base virtual class of hash strategy
	/*
	Tip:
	you can inherit this class,
	and implement your own hash algorithm,
	only need to overwrite the virtual function "hash"
	*/
	class HashStrategy
	{
	public:
		// hash a string to a integer between [0,module-1]
		// parament module represent how many buckets a HashTable has
		virtual size_t hash(const string & key, size_t module) = 0;
	};
}

#endif