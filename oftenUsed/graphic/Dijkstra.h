#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include "DirectedGraph.h"
#include "LinkedList.h"
#include "Edge.h"

namespace Seven
{
	// a strategy class to calculate shortest paths from a vertice to all other vertices
	class Dijkstra
	{
	private:
		// choose 'u' that mark[u]=false and dist[u] is the min of dist[]
		size_t choose(bool * mark, int * dist, size_t N)const;
	public:
		// calculate shortest paths from a vertice to all other vertices
		/*
		Tip:
		1. parameter "begin" is the beginning vertice
		2. it will return an array with N elements,N is the number of vertices of the directed graph.
			each element array[i] is the shortest path from "begin" to "i"
		*/
		LinkedList<Edge> ** dijkstra(const DirectedGraph & g, size_t begin)const;
	};
}

#endif