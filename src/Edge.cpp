#include "stdafx.h"

#include "Edge.h"

namespace Seven
{
	// constructor
	Edge::Edge(size_t begin, size_t end, int weight)
	{
		_begin = begin;
		_end = end;
		_weight = weight;
	}

	// get begin of this edge
	size_t Edge::getBegin()const
	{
		return _begin;
	}

	// get end of this edge
	size_t Edge::getEnd()const
	{
		return _end;
	}

	// get weight of this edge
	int Edge::getWeight()const
	{
		return _weight;
	}

	// set begin of this edge
	void Edge::setBegin(size_t begin)
	{
		_begin = begin;
	}

	// set end of this edge
	void Edge::setEnd(size_t end)
	{
		_end = end;
	}

	// set weight of this edge
	void Edge::setWeight(int weight)
	{
		_weight = weight;
	}

	// compare two edges
	/*
	we assume that whose weight is smaller,who is smaller
	*/
	bool Edge::smallerThan(const Edge & left, const Edge & right)
	{
		return left.getWeight() < right.getWeight();
	}

}