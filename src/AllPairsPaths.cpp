#include "stdafx.h"

#include "AllPairsPaths.h"

namespace Seven
{
	// calculate shortest paths from a vertice to all other vertices
	/*
	Tip:
	it will return an array with N*N elements,N is the number of vertices of the directed graph.
	each element of this array is a linkedlist,
	and array[u*N + v] is the path from 'u' to 'v'.

	Method:
	1. use dynamic programing to form the dir table
	2. use the dir table to find routes
	*/
	LinkedList<Edge> ** AllPairsPaths::allpaths(const DirectedGraph & g)const
	{
		size_t N = g.numberOfVertices(), i, j, k;
		int * A = new int[N*N];
		size_t * dir = new size_t[N*N];
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				A[i*N + j] = g.get(i, j);
				dir[i*N + j] = i;
			}
		}

		int Aik, Akj, Aij;
		for (k = 0; k < N; k++)
		{
			for (i = 0; i < N; i++)
			{
				for (j = 0; j < N; j++)
				{
					Aik = A[i*N + k];
					Akj = A[k*N + j];
					Aij = A[i*N + j];
					if (i != j && Aik > 0 && Akj > 0 && (Aij <= 0 || Aik + Akj < Aij))
					{
						A[i*N + j] = Aik + Akj;
						dir[i*N + j] = dir[k*N + j];
					}
				}
			}
		}

		LinkedList<Edge> ** paths = new LinkedList<Edge>*[N*N];
		Edge edge;
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				paths[i*N + j] = LinkedList<Edge>::create();
				k = j;
				while (k != i)
				{
					edge.setBegin(dir[i*N + k]);
					edge.setEnd(k);
					edge.setWeight(g.get(dir[i*N + k], k));
					if (edge.getWeight()>0)
						paths[i*N + j]->insertHead(edge);
					k = dir[i*N + k];
				}
			}
		}

		delete[]A;
		delete[]dir;
		return paths;
	}

}