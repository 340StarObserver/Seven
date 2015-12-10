#ifndef _ALLPAIRSPATHS_H
#define _ALLPAIRSPATHS_H

#include "DirectedGraph.h"
#include "LinkedList.h"
#include "Edge.h"

namespace Seven
{
	// a strategy class to calculate shortest paths from each vertice to all other vertices
	class AllPairsPaths
	{
	public:
		// calculate shortest paths from a vertice to all other vertices
		/*
		Tip:
		it will return an array with N*N elements,N is the number of vertices of the directed graph.
		each element of this array is a linkedlist,
		and array[u*N + v] is the shortest path from 'u' to 'v'.
		*/
		LinkedList<Edge> ** allpaths(const DirectedGraph & g)const;
	};
}

#endif