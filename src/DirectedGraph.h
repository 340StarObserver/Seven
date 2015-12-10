#ifndef _DIRECTEDGRAPH_H
#define _DIRECTEDGRAPH_H

#include "AdjacencyNode.h"

namespace Seven
{
	// directed graph
	/*
	Tip:
		assume the number of vertices of a directed graph is N, the index of each vertice is [0,N-1].
		assume the cost from p to q is c(p,q),
			if c(p,q) is a negative value,it represents that there is not an edge <p,q>
	*/
	class DirectedGraph
	{
	private:
		size_t _vertices;                 // the number of vertices in the directed graph
		size_t _edges;                    // the number of edges in the directed graph
		AdjacencyNode ** _adjacencylist;  // the AdjacencyList used to represent edges
	public:
		// default constructor
		/* parameter "vertices" is the number of vertices in the directed graph */
		DirectedGraph(size_t vertices);


		// clear the graph
		/* that is, remove all edges of the graph */
		void clear();


		// deconstructor
		~DirectedGraph();


		// get the adjacency lists for other class can easily traverse edges faster
		AdjacencyNode ** getAdjacencyLists()const;


		// get the number of vertices in the directed graph
		size_t numberOfVertices()const;


		// get the number of edges in the directed graph
		size_t numberOfEdges()const;


		// add an edge <u,v>
		/*
		Tips:
		1. the cost from u to v is parameter "cost",
			if "cost" is a negative value,it represents that there is not an edge <u,v>,
			that is,it won't add this edge

		2. you should make sure that <u,v> is not in the graph before you execute this function.
			that is,if you are not sure,you can execute "contains(u,v)" to check before this function.

		3. if u==v,the edge <u,u> is not necessary to add
		*/
		void add(size_t u, size_t v, int cost);


		// check whether has an edge <u,v>
		bool contains(size_t u, size_t v)const;


		// get the cost of edge <u,v>
		/* when not has <u,v>,it will return -1 */
		int get(size_t u, size_t v)const;


		// update the cost of edge <u,v>
		/*
		Tip: when parameter "cost" is a positive value,update success
		*/
		bool update(size_t u, size_t v, int cost);


		// remove the edge <u,v>
		void remove(size_t u, size_t v);
	};
}

#endif