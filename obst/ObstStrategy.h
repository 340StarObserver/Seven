#ifndef _OBSTSTRATEGY_H
#define _OBSTSTRATEGY_H

namespace Seven
{
	// a abstract base class of obst strategy
	/*
	about function "strategy":
	{
	   1. paraments   : the possiblity of being searched of the N elements
	   2. return value: indexs of root nodes of the optimal binary search tree
	   3. requirement :
	      the parament cost[] should be sorted by binary node's value,
		  rather than sorted by cost[] itself
	}
	Tip:
	this class can be seen as an interface,
	you should inherit this class,
	and rewrite the function "strategy" with your own algorithm
	*/
	class ObstStrategy
	{
	public:
		virtual int * strategy(float * cost, unsigned int N)const = 0;
	};
}

#endif