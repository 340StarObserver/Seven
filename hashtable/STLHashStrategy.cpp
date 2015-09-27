#include "stdafx.h"

#include "STLHashStrategy.h"

namespace Seven
{
	// hash a string to a integer between [0,module-1]
	// parament module represent how many buckets a HashTable has
	size_t STLHashStrategy::hash(const string & key, size_t module)
	{
		size_t res = 0, N = key.length();
		for (size_t i = 0; i < N; i++)
			res = 5 * res + key.at(i);
		return res%module;
	}
}