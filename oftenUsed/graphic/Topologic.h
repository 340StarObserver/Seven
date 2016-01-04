#ifndef _TOPOLOGIC_H
#define _TOPOLOGIC_H

#include "DirectedGraph.h"

namespace Seven
{
	// a class to produce topological order from different kinds of data structure
	class Topologic
	{
	private:
		// prepare a ref array, ref[u]=x, that is to say there are x edges which end with u
		size_t * refByDirectedGraph(const DirectedGraph & g)const;

		// select a vertice 'u' that ref[u] is zero
		/* if there is not such a 'u',it will return false */
		bool choose(size_t * ref, size_t num, size_t * u)const;

		// delete all edges that begin from 'u',only need to update ref[] rather that remove edges actually
		void delEdges(const DirectedGraph & g, size_t * ref, size_t u)const;

	public:
		// get topological order from a directed graph
		/*
		Tip:
		1. when successfully,it will return an array of N elements,N is the number of the graph.
			the returned array is the vertices by topological order
		2. when failed,that is to say there is a loop or more in the graph,
			it will return nullptr
		*/
		size_t * order(const DirectedGraph & g)const;
	};
}

#endif