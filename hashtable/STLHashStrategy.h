#ifndef _STLHASHSTRATEGY_H
#define _STLHASHSTRATEGY_H

#include "HashStrategy.h"

namespace Seven
{
	// a hash strategy using stl hash algorithm
	class STLHashStrategy : public HashStrategy
	{
	public:
		// hash a string to a integer between [0,module-1]
		// parament module represent how many buckets a HashTable has
		virtual size_t hash(const string & key, size_t module)const;
	};
}

#endif