#ifndef _DPOBSTSTRATEGY_H
#define _DPOBSTSTRATEGY_H

#include "ObstStrategy.h"

namespace Seven
{
	// a class realizing the interface "ObstStrategy::rootList" by dynamic programing
	class DpObstStrategy : public ObstStrategy
	{
	private:
		// calculate the dp dir table                                     (ok)
		int ** dpDirTable(float * cost, unsigned int N)const;

		// calculate the pre order of nodes based on the dp dir table     (ok)
		int * findPreRootsOrder(int ** dir, unsigned int N)const;
	public:
		// calculate the best root list according to the costs            (ok)
		/*
		about function "strategy":
		{
		1. paraments   : the possiblity of being searched of the N elements
		2. return value: indexs of root nodes of the optimal binary search tree
		3. requirement :
			the parament cost[] should be sorted by binary node's value,
			rather than sorted by cost[] itself
		}
		*/
		virtual int * strategy(float * cost, unsigned int N)const;
	};
}

#endif