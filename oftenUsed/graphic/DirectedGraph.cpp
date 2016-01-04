#include "DirectedGraph.h"

#include <cstring>
using std::memset;

namespace Seven
{
	// default constructor
	/* parameter "vertices" is the number of vertices in the directed graph */
	/*
	the directed graph is represented by N adjacency lists,N is the number of vertices.
	each _adjacencylist[i] is a list that stores edges that begin from i
	for example:
		_adjacencylist[3] = {4,11} -> {5,7} -> {0,1}.That is to say:
		edge	cost
		<3,4>	11
		<3,5>	7
		<3,0>	1
	*/
	DirectedGraph::DirectedGraph(size_t vertices)
	{
		_vertices = vertices;
		_edges = 0;
		_adjacencylist = new AdjacencyNode*[_vertices];
		memset(_adjacencylist, 0, _vertices*sizeof(AdjacencyNode *));
	}


	// clear the graph
	/* that is, remove all edges of the graph */
	/*
	1. clear each adjacency list
	2. make the number of edges to zero
	*/
	void DirectedGraph::clear()
	{
		AdjacencyNode * p = nullptr;
		for (size_t i = 0; i < _vertices; i++)
		{
			while (_adjacencylist[i] != nullptr){
				p = _adjacencylist[i];
				_adjacencylist[i] = p->getNext();
				delete p;
			}
		}
		_edges = 0;
	}


	// deconstructor
	/*
	1. clear all the adjacency lists
	2. delete the memory of the adjacency list array
	*/
	DirectedGraph::~DirectedGraph()
	{
		clear();
		delete[]_adjacencylist;
	}


	// get the adjacency lists for other class can easily traverse edges faster
	AdjacencyNode ** DirectedGraph::getAdjacencyLists()const
	{
		return _adjacencylist;
	}


	// get the number of vertices in the directed graph
	size_t DirectedGraph::numberOfVertices()const
	{
		return _vertices;
	}


	// get the number of edges in the directed graph
	size_t DirectedGraph::numberOfEdges()const
	{
		return _edges;
	}


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
	void DirectedGraph::add(size_t u, size_t v, int cost)
	{
		if (u < _vertices && v < _vertices && u != v && cost>0)
		{
			AdjacencyNode * p = new AdjacencyNode(v, cost);
			p->setNext(_adjacencylist[u]);
			_adjacencylist[u] = p;
			_edges++;
		}
	}


	// check whether has an edge <u,v>
	/*
	traverse the adjacency list[u] to check whether has edge <u,v>
	*/
	bool DirectedGraph::contains(size_t u, size_t v)const
	{
		if (u < _vertices && v < _vertices && u != v)
		{
			AdjacencyNode * p = _adjacencylist[u];
			while (p)
			{
				if (p->getIndex() == v)
					return true;
				p = p->getNext();
			}
		}
		return false;
	}


	// get the cost of edge <u,v>
	/* when not has <u,v>,it will return -1 */
	int DirectedGraph::get(size_t u, size_t v)const
	{
		if (u < _vertices && v < _vertices && u != v)
		{
			AdjacencyNode * p = _adjacencylist[u];
			while (p)
			{
				if (p->getIndex() == v)
					return p->getCost();
				p = p->getNext();
			}
		}
		return -1;
	}


	// update the cost of edge <u,v>
	/*
	Tip: when parameter "cost" is a positive value,update success
	*/
	bool DirectedGraph::update(size_t u, size_t v, int cost)
	{
		if (u < _vertices && v < _vertices && u != v && cost>0)
		{
			AdjacencyNode * p = _adjacencylist[u];
			while (p)
			{
				if (p->getIndex() == v)
				{
					p->setCost(cost);
					return true;
				}
				p = p->getNext();
			}
		}
		return false;
	}


	// remove the edge <u,v>
	void DirectedGraph::remove(size_t u, size_t v)
	{
		if (u >= _vertices || v >= _vertices || u == v)
			return;
		AdjacencyNode * p = _adjacencylist[u];
		if (p)
		{
			if (p->getIndex() == v)
			{
				_adjacencylist[u] = p->getNext();
				delete p;
				_edges--;
				return;
			}
			AdjacencyNode * pre = p;
			p = p->getNext();
			while (p)
			{
				if (p->getIndex() == v)
				{
					pre->setNext(p->getNext());
					delete p;
					_edges--;
					return;
				}
				pre = p;
				p = p->getNext();
			}
		}
	}

}