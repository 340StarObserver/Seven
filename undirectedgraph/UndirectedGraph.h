#ifndef _UNDIRECTEDGRAPH_H
#define _UNDIRECTEDGRAPH_H

#include "Edge.h"
#include "LinkedList.h"

namespace Seven
{
	// undirected graph
	class UndirectedGraph
	{
	private:
		int * _graph;      // the graph
		size_t _vertices;  // the number of vertices
		size_t _edges;     // the number of edges
	public:
		// constructors:
		UndirectedGraph(size_t vertices);         // default constructor  O(1)

		// clears:
		~UndirectedGraph();                       // deconstructor        O(1)
		void clear();                             // clear the graph      O(1)

		// CURD of edges:
		int get(size_t u, size_t v)const;         // get weight of (u,v)  O(1)

		bool set(size_t u, size_t v, int weight); // set weight of (u,v)  O(1)

		bool contains(size_t u, size_t v)const;   // whether exist (u,v)  O(1)

		bool remove(size_t u, size_t v);          // remove (u,v)         O(1)

		// attributes:
		size_t numberOfVertices()const;           // number of vertices   O(1)

		size_t numberOfEdges()const;              // number of edges      O(1)

		size_t degree(size_t u)const;             // degree of a vertice  O(N)

		// connected:
		                           // whether has a path between u and v  O(N*N)
		bool isConnected(size_t u, size_t v)const;
		
		                           // whether is a connected graph        O(N*N*logN)
		bool isConnected()const;

		// calculate the edges consist of a minmum-cost spanning tree     O(N*logN)
		/*
		Tips:
		1. this function can be used only when this graph is a connected-graph,
		   but you don't need to worry about it because if this graph is not connected,
		   it will return nullptr.
		2. this function return a linkedlist which includes the edges that can form a spanning tree.
		*/
		LinkedList<Edge> * minSpanTree()const;
	};
}

#endif