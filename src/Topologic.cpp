#include "Topologic.h"

#include <cstring>
using std::memset;

namespace Seven
{
	// get topological order from a directed graph
	/*
	Tip:
	1. when successfully,it will return an array of N elements,N is the number of the graph.
		the returned array is the vertices by topological order
	2. when failed,that is to say there is a loop or more in the graph,
		it will return nullptr

	Method:
	1. prepare a ref array, ref[u]=x, that is to say there are x edges which end with u
	2. do a loop of N times:
		2-1. select a vertice 'u' that ref[u]=0
		2-2. add 'u' to the result order
		2-3. delete all edges that begin from 'u',only need to update ref[] rather that remove edges actually
	3. if the size of the result order is N: return the result order
		else: return nullptr
		this can be simpfied because when 2-1 failed,the graph already appear a loop
	*/
	size_t * Topologic::order(const DirectedGraph & g)const
	{
		size_t * ref = refByDirectedGraph(g);

		size_t N = g.numberOfVertices(), i, u;
		size_t * res = new size_t[N];

		bool success;
		for (i = 0; i < N; i++)
		{
			success = choose(ref, N, &u);
			if (success){
				res[i] = u;
				delEdges(g, ref, u);
			}
			else{
				delete[]ref;
				delete[]res;
				return nullptr;
			}
		}

		delete[]ref;
		return res;
	}


	// prepare a ref array, ref[u]=x, that is to say there are x edges which end with u
	/* the time cost of this function is O(N + e),e is the number of edges of the graph */
	size_t * Topologic::refByDirectedGraph(const DirectedGraph & g)const
	{
		size_t N = g.numberOfVertices(), i;

		size_t * ref = new size_t[N];
		memset(ref, 0, N*sizeof(size_t));

		AdjacencyNode ** adjacelists = g.getAdjacencyLists();
		AdjacencyNode * p = nullptr;
		for (i = 0; i < N; i++)
		{
			p = adjacelists[i];
			while (p){
				ref[p->getIndex()]++;
				p = p->getNext();
			}
		}
		return ref;
	}


	// select a vertice 'u' that ref[u] is zero
	/* if there is not such a 'u',it will return false */
	bool Topologic::choose(size_t * ref, size_t num, size_t * u)const
	{
		for (size_t i = 0; i < num; i++)
		{
			if (ref[i] == 0){
				*u = i;
				return true;
			}
		}
		return false;
	}


	// delete all edges that begin from 'u',only need to update ref[] rather that remove edges actually
	/*
	decrease ref[u] to make ref[u] become the max value of type size_t,
	so that 'u' won't be choose again
	*/
	void Topologic::delEdges(const DirectedGraph & g, size_t * ref, size_t u)const
	{
		ref[u]--;
		AdjacencyNode * p = g.getAdjacencyLists()[u];
		while (p){
			ref[p->getIndex()]--;
			p = p->getNext();
		}
	}

}