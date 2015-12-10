#ifndef _AOENETWORK_H
#define _AOENETWORK_H

#include "DirectedGraph.h"
#include "LinkedList.h"
#include "Edge.h"

namespace Seven
{
	// a activity-on-edge network of directed graph
	/*
	in an activity-on-edge network,an activity is represented by an edge.
	and the cost of an edge is the cost of this activity
	*/
	class AOEnetwork
	{
	private:
		// get ealiest event time of each vertice
		/*
		parameter "topologicOrder" is the topoligocal order of directed graph
		*/
		int * ealiestEventTime(const DirectedGraph & g, size_t * topologicOrder)const;

		// get latest event time of each vertice
		/*
		1. parameter "topologicOrder" is the topoligocal order of directed graph
		2. parameter "endTime" is the earliest event time of the last vertice by topological order
			for example:
				the topological order is 4,1,3,0,2
				the "endTime" is earlist event time of vertice(2)
		*/
		int * latestEventTime(const DirectedGraph & g, size_t * topologicOrder, int endTime)const;

	public:
		// get key activities(edges) of a AOE network represented by a directed graph
		LinkedList<Edge> * keyActivities(const DirectedGraph & g)const;

		// get the min cost of the whole project
		int minCost(const DirectedGraph & g)const;
	};
}

#endif