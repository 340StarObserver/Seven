#ifndef _EDGE_H
#define _EDGE_H

namespace Seven
{
	// class of edge
	class Edge
	{
	private:
		size_t _begin;  // the begin of this edge
		size_t _end;    // the end of this edge
		int _weight;    // the cost of this edge
	public:
		// constructors:
		Edge(size_t begin = 0, size_t end = 0, int weight = 0);

		// get:
		size_t getBegin()const;
		size_t getEnd()const;
		int getWeight()const;

		// set:
		void setBegin(size_t begin);
		void setEnd(size_t end);
		void setWeight(int weight);

		// compare:
		static bool smallerThan(const Edge & left, const Edge & right);
	};
}

#endif