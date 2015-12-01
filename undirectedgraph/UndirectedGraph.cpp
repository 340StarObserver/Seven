#include "stdafx.h"

#include "UndirectedGraph.h"

#include "Queue.h"

#include "UnionFindSets.h"

#include "Sort.h"

#include <cstring>
using std::memset;

namespace Seven
{
	// constructor
	/*
	at the beginning,the number of edges is zero
	and the weight of each edge is -1,that is this edge not exists
	*/
	UndirectedGraph::UndirectedGraph(size_t vertices)
	{
		_vertices = vertices;
		_edges = 0;
		size_t N = vertices*(vertices - 1) / 2;
		_graph = new int[N];
		memset(_graph, -1, N*sizeof(int));
	}


	// deconstructor
	UndirectedGraph::~UndirectedGraph()
	{
		delete[]_graph;
	}


	// clear the graph
	void UndirectedGraph::clear()
	{
		_edges = 0;
		size_t N = _vertices*(_vertices - 1) / 2;
		memset(_graph, -1, N*sizeof(int));
	}


	// get the weight of edge(u,v)
	/*
	if u<v :
		index = u*vertices + v - (u+1)*(u+2)/2
	if u=v :
		index = -1
	if u>v :
		index = v*vertices + u - (v+1)*(v+2)/2
	*/
	int UndirectedGraph::get(size_t u, size_t v)const
	{
		if (u < _vertices && v < _vertices && u != v){
			size_t index;
			if (u < v)
				index = u*_vertices + v - (u + 1)*(u + 2) / 2;
			else
				index = v*_vertices + u - (v + 1)*(v + 2) / 2;
			return _graph[index];
		}
		return -1;
	}


	// set the weight of edge(u,v)
	/*
	1. how to find the index in graph[] of (u,v) is the same as function get
	2. when set (u,v), update the number of edges
	*/
	bool UndirectedGraph::set(size_t u, size_t v, int weight)
	{
		if (u < _vertices && v < _vertices && u != v){
			size_t index;
			if (u < v)
				index = u*_vertices + v - (u + 1)*(u + 2) / 2;
			else
				index = v*_vertices + u - (v + 1)*(v + 2) / 2;
			if (_graph[index] < 0 && weight>0)
				_edges++;
			else if (_graph[index] > 0 && weight < 0)
				_edges--;
			_graph[index] = weight;
			return true;
		}
		return false;
	}


	// contains edge(u,v)
	bool UndirectedGraph::contains(size_t u, size_t v)const
	{
		return get(u, v) > 0;
	}


	// remove edge(u,v)
	/*
	if (u,v) exists:
		delete (u,v)
		decrease the number of edges
	*/
	bool UndirectedGraph::remove(size_t u, size_t v)
	{
		if (u < _vertices && v < _vertices && u != v){
			size_t index;
			if (u < v)
				index = u*_vertices + v - (u + 1)*(u + 2) / 2;
			else
				index = v*_vertices + u - (v + 1)*(v + 2) / 2;
			if (_graph[index] > 0){
				_edges--;
				_graph[index] = -1;
				return true;
			}
		}
		return false;
	}


	// number of vertices
	size_t UndirectedGraph::numberOfVertices()const
	{
		return _vertices;
	}


	// number of edges
	size_t UndirectedGraph::numberOfEdges()const
	{
		return _edges;
	}


	// degree of a vertice
	size_t UndirectedGraph::degree(size_t u)const
	{
		size_t count = 0;
		for (size_t i = 0; i < _vertices; i++){
			if (get(u, i) > 0)
				count++;
		}
		return count;
	}


	// whether has a path between u and v
	/*
	use BFS to judge whether has a path from u to v
	*/
	bool UndirectedGraph::isConnected(size_t u, size_t v)const
	{
		if (u >= _vertices || v >= _vertices)
			return false;

		Queue<size_t> Q;

		bool * visited = new bool[_vertices];
		memset(visited, false, _vertices);

		Q.push(u);
		visited[u] = true;

		size_t cur, next;
		while (!Q.empty()){
			cur = Q.front();
			Q.pop();

			if (cur == v){
				delete[]visited;
				return true;
			}

			for (next = 0; next < _vertices; next++){
				if (get(cur, next) > 0 && !visited[next]){
					Q.push(next);
					visited[next] = true;
				}
			}
		}

		delete[]visited;
		return false;
	}


	// whether is a connected graph
	/*
	here use a unionfindsets to judge whether this graph is connected
	detail steps:
	1. we can assume A and B are belong to the same set, only when has a path between A and B
	2. then put all the edges into a unionfindsets
	3. finally,if the unionfindsets only has a representational element.
	   that is to say,there is only a set in this unionfindsets;
	   that is to say,for any nodes A and B,there is a path between them;
	   that is to say,this undirected graph is connected
	*/
	bool UndirectedGraph::isConnected()const
	{
		if (_edges < _vertices - 1)
			return false;

		UnionFindSets sets(_vertices);
		for (int u = 0; u < (int)_vertices; u++){
			for (int v = u + 1; v < (int)_vertices; v++){
				if (contains(u, v))
					sets.Union(sets.find(u), sets.find(v));
			}
		}
		return sets.representNum() == 1;
	}


	// calculate the edges consist of a minmum-cost spanning tree
	/*
	Tips:
		1. this function can be used only when this graph is a connected-graph,
		   but you don't need to worry about it because if this graph is not connected,
		   it will return nullptr.
		2. this function return a linkedlist which includes the edges that can form a spanning tree.
	Method:
		1. put all edges into an array called "E"
		2. sort these edges ascending by weight,or called cost
		3. create a unionfindsets called "UFS"
		4. create a list called "thList"                                                                   
		4. create "p" and make it is 0
		5. while UFS.representNum > 1 and not all edges have been tried(that is p < edgesNum):
			if UFS.find(E[p].begin) != UFS.find(E[p].end):
				// that is,after add E[p],will not has loop
				union E[p].begin and E[p].end in UFS
				add E[p] to result thList
			increase p
		6. if UFS.representNum==1: return thList
		   else: return nullptr
	*/
	LinkedList<Edge> * UndirectedGraph::minSpanTree()const
	{
		Edge * E = new Edge[_edges];
		int weight;
		size_t p = 0;
		for (size_t u = 0; u < _vertices; u++){
			for (size_t v = u + 1; v < _vertices; v++){
				weight = get(u, v);
				if (weight > 0){
					E[p].setBegin(u);
					E[p].setEnd(v);
					E[p].setWeight(weight);
					p++;
				}
			}
		}
		Sort<Edge>::fastSort(E, _edges, Edge::smallerThan);

		UnionFindSets UFS(_vertices);

		LinkedList<Edge> * thList = LinkedList<Edge>::create();

		p = 0;
		int r1, r2;
		while (UFS.representNum()>1 && p < _edges){
			r1 = UFS.find(E[p].getBegin());
			r2 = UFS.find(E[p].getEnd());
			if (r1 != r2){
				UFS.Union(r1, r2);
				thList->insertTail(E[p]);
			}
			p++;
		}

		delete[]E;

		if (UFS.representNum() == 1)
			return thList;
		delete thList;
		return nullptr;
	}

}