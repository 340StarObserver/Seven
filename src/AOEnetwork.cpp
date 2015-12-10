#include "stdafx.h"

#include "AOEnetwork.h"
#include "Topologic.h"

#include <cstring>
using std::memset;

namespace Seven
{
	// get key activities(edges) of a AOE network represented by a directed graph
	/*
	Method:
	1. calculate the topological order of the directed graph
	2. calculate the ealiest event time of each vertice, ee[]
	3. calculate the latest event time of each vertice, le[]
	4. for each edge k=<u,v>
		earliest activity time e[k]=ee[u]
		latest activity time l[k]=le[v] - cost of <u,v>
		if e[k]==l[k]: add this edge to the result list
	*/
	LinkedList<Edge> * AOEnetwork::keyActivities(const DirectedGraph & g)const
	{
		Topologic topologicObj;
		size_t * topologicOrder = topologicObj.order(g);

		int * ee = ealiestEventTime(g, topologicOrder);

		size_t N = g.numberOfVertices();
		int endTime = ee[topologicOrder[N - 1]];
		int * le = latestEventTime(g, topologicOrder, endTime);

		LinkedList<Edge> * keylist = LinkedList<Edge>::create();

		AdjacencyNode ** adjacencylists = g.getAdjacencyLists();
		AdjacencyNode * p = nullptr;

		size_t u, v;
		int e, l;
		Edge edge;
		for (u = 0; u < N; u++)
		{
			e = ee[u];
			p = adjacencylists[u];
			while (p)
			{
				v = p->getIndex();
				l = le[v] - p->getCost();
				if (e == l)
				{
					edge.setBegin(u);
					edge.setEnd(v);
					edge.setWeight(p->getCost());
					keylist->insertHead(edge);
				}
				p = p->getNext();
			}
		}

		delete[]topologicOrder;
		delete[]ee;
		delete[]le;
		return keylist;
	}


	// get ealiest event time of each vertice
	/* 
	Tip:
		parameter "topologicOrder" is the topoligocal order of directed graph
	Method:
		ee[v] = max{ ee[u] + cost of <u,v> }
	*/
	int * AOEnetwork::ealiestEventTime(const DirectedGraph & g, size_t * topologicOrder)const
	{
		size_t N = g.numberOfVertices(), i, u, v;

		int * ee = new int[N];
		memset(ee, 0, N*sizeof(int));

		AdjacencyNode ** adjacencylists = g.getAdjacencyLists();
		AdjacencyNode * p = nullptr;

		for (i = 0; i < N; i++)
		{
			u = topologicOrder[i];
			p = adjacencylists[u];
			while (p)
			{
				v = p->getIndex();
				if (ee[v] < ee[u] + p->getCost())
					ee[v] = ee[u] + p->getCost();
				p = p->getNext();
			}
		}
		return ee;
	}


	// get latest event time of each vertice
	/*
	Tips:
	1. parameter "topologicOrder" is the topoligocal order of directed graph
	2. parameter "endTime" is the earliest event time of the last vertice by topological order
		for example:
			the topological order is 4,1,3,0,2
			the "endTime" is earlist event time of vertice(2)
	Method:
	le[u] = min{ le[v] - cost of <u,v> }
	*/
	int * AOEnetwork::latestEventTime(const DirectedGraph & g, size_t * topologicOrder, int endTime)const
	{
		size_t N = g.numberOfVertices(), i, u, v;

		int * le = new int[N];
		for (i = 0; i < N; i++)
			le[i] = endTime;

		AdjacencyNode ** adjacencylists = g.getAdjacencyLists();
		AdjacencyNode * p = nullptr;

		for (i = 0; i <N - 1; i++)
		{
			u = topologicOrder[N - 2 - i];
			p = adjacencylists[u];
			while (p)
			{
				v = p->getIndex();
				if (le[u]>le[v] - p->getCost())
					le[u] = le[v] - p->getCost();
				p = p->getNext();
			}
		}
		return le;
	}


	// get the min cost of the whole project
	/*
	Method:
	1. calculate the topological order of the directed graph, t[]
	2. calculate the ealiest event time of each vertice, ee[]
	3. return ee[t[N-1]], N is the number of vertices
	*/
	int AOEnetwork::minCost(const DirectedGraph & g)const
	{
		Topologic obj;
		size_t * t = obj.order(g);
		int * ee = ealiestEventTime(g, t);
		int cost = ee[t[g.numberOfVertices() - 1]];
		delete[]t;
		delete[]ee;
		return cost;
	}


}