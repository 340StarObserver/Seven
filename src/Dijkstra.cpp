#include "Dijkstra.h"

#include <limits>
using std::numeric_limits;

namespace Seven
{
	// choose 'u' that mark[u]=false and dist[u] is the min of dist[]
	size_t Dijkstra::choose(bool * mark, int * dist, size_t N)const
	{
		size_t u = 0;
		int tmp = numeric_limits<int>::max();
		for (size_t i = 0; i < N; i++)
		{
			if (mark[i] == false && dist[i] > 0 && dist[i] < tmp)
			{
				u = i;
				tmp = dist[i];
			}
		}
		return u;
	}


	// calculate shortest paths from a vertice to all other vertices
	/*
	Tip:
	1. parameter "begin" is the beginning vertice
	2. it will return an array with N elements,N is the number of vertices of the directed graph.
	each element array[i] is the shortest path from "begin" to "i"
	*/
	LinkedList<Edge> ** Dijkstra::dijkstra(const DirectedGraph & g, size_t begin)const
	{
		size_t N = g.numberOfVertices(), i, u, w, cur;
		int * dist = new int[N];
		bool * mark = new bool[N];
		size_t * dir = new size_t[N];
		for (i = 0; i < N; i++)
		{
			mark[i] = false;
			dist[i] = g.get(begin, i);
			dir[i] = begin;
		}
		mark[begin] = true;
		dist[begin] = 0;

		int cost;
		for (i = 0; i < N - 2; i++)
		{
			u = choose(mark, dist, N);
			mark[u] = true;
			for (w = 0; w < N; w++)
			{
				cost = g.get(u, w);
				if (mark[w] == false && cost > 0 && (dist[w] <= 0 || dist[u] + cost < dist[w]))
				{
					dist[w] = dist[u] + g.get(u, w);
					dir[w] = u;
				}
			}
		}

		LinkedList<Edge> ** paths = new LinkedList<Edge>*[N];
		Edge edge;
		for (i = 0; i < N; i++)
		{
			paths[i] = LinkedList<Edge>::create();
			cur = i;
			while (cur != begin)
			{
				edge.setBegin(dir[cur]);
				edge.setEnd(cur);
				edge.setWeight(g.get(dir[cur], cur));
				paths[i]->insertHead(edge);
				cur = dir[cur];
			}
		}

		delete[]dist;
		delete[]mark;
		delete[]dir;
		return paths;
	}

}