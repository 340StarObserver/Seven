#ifndef _HASHSTRATEGY_H
#define _HASHSTRATEGY_H

#include <string>
using std::string;

namespace Seven
{
	// transfer various kinds of key to a integer
	class HashStrategy
	{
	public:
		// transfer a integer key to a integer[0,range-1]
		static unsigned int hashInt(unsigned int key,unsigned int range);

		// transfer a string key to a integer[0,range-1]
		static unsigned int hashString(const string & key,unsigned int range);
	};
}

#endif