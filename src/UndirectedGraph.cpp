#include "stdafx.h"

#include "UndirectedGraph.h"

#include "Queue.h"

#include "UnionFindSets.h"

#include "Sort.h"

#include "PriorityQueue.h"

#include <cstring>
using std::memset;

using std::pair;

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
	1.  we can assume A and B are belong to the same set, only when has a path between A and B
	2.  then put all the edges into a unionfindsets
	3.  finally,if the unionfindsets only has a representational element.
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
		1.  this function can be used only when this graph is a connected-graph,
			but you don't need to worry about it because if this graph is not connected,
			it will return nullptr.
		2.  this function return a linkedlist which includes the edges that can form a spanning tree.
	Method:
		1.  put all edges into an array called "E"
		2.  sort these edges ascending by weight,or called cost
		3.  create a unionfindsets called "UFS"
		4.  create a list called "thList"                                                                   
		4.  create "p" and make it is 0
		5.  while UFS.representNum > 1 and not all edges have been tried(that is p < edgesNum):
			if UFS.find(E[p].begin) != UFS.find(E[p].end):
				// that is,after add E[p],will not has loop
				union E[p].begin and E[p].end in UFS
				add E[p] to result thList
			increase p
		6.  if UFS.representNum==1: return thList
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


	// judge whether vertice "u" is a cut-point
	/*
	Tip:
		this function can be used only when this graph is a connected-graph
	Method:
		1. create a unionfindsets called 'UFS'
		2. push all edges exclude associated with vertice 'u' into UFS
		3. if the number of representation elements of UFS is more than two:
			// why is two,because the 'u' is a separate vertice
			// and 'u' is now not in the graph logically
			'u' is a cut-point
	*/
	bool UndirectedGraph::isCutPoint(size_t u)const
	{
		UnionFindSets UFS(_vertices);
		for (size_t i = 0; i < _vertices; i++){
			for (size_t j = i + 1; j < _vertices; j++){
				if (i != u && j != u && contains(i, j))
					UFS.Union(UFS.find((int)i), UFS.find((int)j));
			}
		}
		return UFS.representNum() > 2;
	}


	// get all the cut points
	// this function will return a list of the vertices which are cut points
	LinkedList<size_t> * UndirectedGraph::cutPoints()const
	{
		LinkedList<size_t> * list = LinkedList<size_t>::create();
		bool * visited = new bool[_vertices];
		bool * isCut = new bool[_vertices];
		size_t * dfn = new size_t[_vertices];
		size_t * low = new size_t[_vertices];
		size_t * parent = new size_t[_vertices];
		size_t count = 0;
		memset(visited, false, _vertices);
		memset(isCut, false, _vertices);
		memset(parent, 0, _vertices*sizeof(size_t));
		dfsCutPoints(0, &count, visited, isCut, dfn, low, parent, list);
		delete[]visited;
		delete[]isCut;
		delete[]dfn;
		delete[]low;
		delete[]parent;
		return list;
	}


	// dfs when calculate cut points
	void UndirectedGraph::dfsCutPoints(size_t root, size_t * count, bool * visited, bool * isCut, size_t * dfn, size_t * low, size_t * parent, LinkedList<size_t> * list)const
	{
		size_t children = 0;
		visited[root] = true;
		dfn[root] = low[root] = ++*count;
		for (size_t v = 0; v < _vertices; v++)
		{
			if (contains(root, v))
			{
				if (!visited[v])
				{
					children++;
					parent[v] = root;
					dfsCutPoints(v, count, visited, isCut, dfn, low, parent, list);
					low[root] = (low[root] < low[v] ? low[root] : low[v]);
					if (((root == 0 && children > 1) || (root != 0 && low[v] >= dfn[root])) && !isCut[root])
					{
						list->insertHead(root);
						isCut[root] = true;
					}
				}
				else if (v != parent[root])
					low[root] = (low[root] < dfn[v] ? low[root] : dfn[v]);
			}
		}
	}


	// judge whether edge(u,v) is a cut-bridge
	/*
	Tip:
		this function can be used only when this graph is a connected-graph
	Method:
		1. create a unionfindsets called 'UFS'
		2. push all edges exclude (u,v) into UFS
		3. if the number of representation elements of UFS is more than one:
			'u' is a cut-point
	*/
	bool UndirectedGraph::isCutBridge(size_t u, size_t v)const
	{
		UnionFindSets UFS(_vertices);
		for (size_t i = 0; i < _vertices; i++){
			for (size_t j = i + 1; j < _vertices; j++){
				if ((i != u || j != v) && (i != v || j != u) && contains(i, j))
					UFS.Union(UFS.find((int)i), UFS.find((int)j));
			}
		}
		return UFS.representNum() > 1;
	}


	// get all the bridges
	// this function will return a list of the edges which are bridges
	LinkedList<Edge> * UndirectedGraph::cutBridges()const
	{
		LinkedList<Edge> * list = LinkedList<Edge>::create();
		bool * visited = new bool[_vertices];
		size_t * dfn = new size_t[_vertices];
		size_t * low = new size_t[_vertices];
		size_t * parent = new size_t[_vertices];
		size_t count = 0;
		memset(visited, false, _vertices);
		memset(parent, 0, _vertices*sizeof(size_t));
		dfsCutBridges(0, &count, visited, dfn, low, parent, list);
		delete[]visited;
		delete[]dfn;
		delete[]low;
		delete[]parent;
		return list;
	}


	// dfs when calculate all bridges
	void UndirectedGraph::dfsCutBridges(size_t root, size_t * count, bool * visited, size_t * dfn, size_t * low, size_t * parent, LinkedList<Edge> * list)const
	{
		size_t children = 0;
		visited[root] = true;
		dfn[root] = low[root] = ++*count;
		for (size_t v = 0; v < _vertices; v++)
		{
			if (contains(root, v))
			{
				if (!visited[v])
				{
					children++;
					parent[v] = root;
					dfsCutBridges(v, count, visited, dfn, low, parent, list);
					low[root] = (low[root] < low[v] ? low[root] : low[v]);
					if (dfn[root] < low[v])
						list->insertHead(Edge(root, v, get(root, v)));
				}
				else if (v != parent[root])
					low[root] = (low[root] < dfn[v] ? low[root] : dfn[v]);
			}
		}
	}


	// compare two states when calculate min-cost path between two vertices
	/*
	the smaller the cost is,the larger the state is
	*/
	int compareState(const pair<size_t, int> & left, const pair<size_t, int> & right)
	{
		if (left.second < right.second)
			return 1;
		if (left.second > right.second)
			return -1;
		return 0;
	}


	// min-cost path between vertice 'u' and 'v'
	/*
	Tip: 'u' is the beginning, 'v' is the end
		it return a linkedlist of each step of this min-cost path
		if there is no path between 'u' and 'v',it will return nullptr
	Method:
		1. new a priority-queue called 'Q'
		2. new a array to mark whether each node has been visited called 'visited'
		3. new a original state(u,0)
			push it to 'Q'
			do mark for 'u'
			assume that state(x,y), x is current position, y is the cost from 'u' to it
		4. while 'Q' is not empty:
			fecth the best element from 'Q' called 'cur'
			visit cur and update the distance[]
			if cur.position is 'v':
				"find path"
			push all the possible states into 'Q',and do mark
		5. if "find path":
			use the distance[] to traceback from 'v' to 'u',
			and put the path into a list
		6. return the list
	*/
	LinkedList<Edge> * UndirectedGraph::optimalPath(size_t u, size_t v)const
	{
		PriorityQueue<pair<size_t, int>> Q(_vertices, true);

		bool * visited = new bool[_vertices];
		memset(visited, false, _vertices);

		int * distance = new int[_vertices];
		memset(distance, -1, _vertices*sizeof(int));

		pair<size_t, int> cur(u, 0), next;
		Q.push(cur, compareState);

		bool find = false;
		int nextCost;
		while (!Q.empty()){
			cur = Q.top();
			Q.pop(compareState);

			visited[cur.first] = true;
			if (distance[cur.first] == -1 || distance[cur.first] > cur.second)
				distance[cur.first] = cur.second;
			if (cur.first == v){
				find = true;
				break;
			}

			for (size_t t = 0; t < _vertices; t++){
				nextCost = get(cur.first, t);
				if (nextCost>0 && !visited[t]){
					next.first = t;
					next.second = cur.second + nextCost;
					Q.push(next, compareState);
				}
			}
		}
		
		delete[]visited;

		LinkedList<Edge> * list = nullptr;
		if (find){
			list = LinkedList<Edge>::create();
			Edge edge;
			size_t current = v;
			while (current != u){
				for (size_t prev = 0; prev < _vertices; prev++){
					int nextCost = get(prev, current);
					if (nextCost > 0 && distance[prev] + nextCost == distance[current]){
						edge.setBegin(prev);
						edge.setEnd(current);
						edge.setWeight(nextCost);
						list->insertHead(edge);
						current = prev;
						break;
					}
				}
			}
		}

		delete[]distance;
		return list;
	}

}