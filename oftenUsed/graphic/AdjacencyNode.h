#ifndef _ADJACENCYNODE_H
#define _ADJACENCYNODE_H

namespace Seven
{
	// node for adjacencylist of a directed graph
	class AdjacencyNode
	{
	private:
		size_t _index;           // the index of a vertice in the directed graph
		int _cost;               // the cost from one vertice to this vertice
		AdjacencyNode * _next;   // the next AdjacencyNode
	public:
		// default constructor
		/*
		"index" is the index of a vertice in the directed graph
		"cost" is the cost from one vertice(k) to this vertice,
		negative "cost" represents that there is not an edge from k to this vertice
		*/
		AdjacencyNode(size_t index = 0, int cost = 0);


		// get the index of the vertice in the directed graph
		size_t getIndex()const;


		// get the cost from one vertice(k) to this vertice
		/*
		if the returned value is negative,there is not an edge from k to this vertice
		*/
		int getCost()const;


		// get the next AdjacencyNode
		AdjacencyNode * getNext()const;


		// set the index of the vertice in the directed graph
		void setIndex(size_t index);


		// set the cost from one vertice(k) to this vertice
		/*
		if you want to realize that there is not an edge from k to this vertice,
		you can set the cost to a negative value
		*/
		void setCost(int cost);


		// set the next AdjacencyNode
		void setNext(AdjacencyNode * next);
	};
}

#endif