#include "AdjacencyNode.h"

namespace Seven
{
	// default constructor
	/*
	"index" is the index of a vertice in the directed graph
	"cost" is the cost from one vertice(k) to this vertice,
	negative "cost" represents that there is not an edge from k to this vertice
	*/
	AdjacencyNode::AdjacencyNode(size_t index, int cost)
	{
		_index = index;
		_cost = cost;
		_next = nullptr;
	}


	// get the index of the vertice in the directed graph
	size_t AdjacencyNode::getIndex()const
	{
		return _index;
	}


	// get the cost from one vertice(k) to this vertice
	/*
	if the returned value is negative,there is not an edge from k to this vertice
	*/
	int AdjacencyNode::getCost()const
	{
		return _cost;
	}


	// get the next AdjacencyNode
	AdjacencyNode * AdjacencyNode::getNext()const
	{
		return _next;
	}


	// set the index of the vertice in the directed graph
	void AdjacencyNode::setIndex(size_t index)
	{
		_index = index;
	}


	// set the cost from one vertice(k) to this vertice
	/*
	if you want to realize that there is not an edge from k to this vertice,
	you can set the cost to a negative value
	*/
	void AdjacencyNode::setCost(int cost)
	{
		_cost = cost;
	}


	// set the next AdjacencyNode
	void AdjacencyNode::setNext(AdjacencyNode * next)
	{
		_next = next;
	}
}