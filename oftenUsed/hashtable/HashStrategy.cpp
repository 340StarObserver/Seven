#include "HashStrategy.h"

namespace Seven
{
	// transfer a integer key to a integer[0,range-1]
	unsigned int HashStrategy::hashInt(unsigned int key,unsigned int range)
	{
		return key%range;
	}

	// transfer a string key to a integer[0,range-1]
	unsigned int HashStrategy::hashString(const string & key,unsigned int range)
	{
		unsigned int res = 0, N = key.length();
		for (unsigned int i = 0; i < N; i++)
			res = 5 * res + key.at(i);
		return res%range;
	}
}