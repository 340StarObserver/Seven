#include "stdafx.h"

#include "CharTree.h"
#include "PriorityQueue.h"
#include "Stack.h"
#include "Queue.h"
using std::pair;

namespace Seven
{
	// get root
	CharNode * CharTree::getRoot()const
	{
		return _root;
	}


	// constructor
	/*
	1. create a priority queue
	2. put nodes whose count > 0 into the queue
	3. while queue's size>=2:
		fetch two nodes whose priority are highest
		create a new node,note is as "p"
		set p's count is the add of the two nodes
		make the two nodes become p's child
		put p into the queue
	*/
	CharTree::CharTree(size_t * count, int N)
	{
		PriorityQueue<CharNode *> Q(512, true);

		_size = 0;
		for (int i = 0; i < N; i++){
			if (count[i]>0){
				Q.push(new CharNode(char(i - 128), count[i]), CharNode::compare);
				_size++;
			}
		}
		_size = (_size << 1) - 1;

		CharNode * p = nullptr, *left = nullptr, *right = nullptr;
		while (Q.size() >= 2){
			left = Q.top();
			Q.pop(CharNode::compare);
			right = Q.top();
			Q.pop(CharNode::compare);

			p = new CharNode();
			p->setFrequency(left->getFrequency() + right->getFrequency());
			p->setLeft(left);
			p->setRight(right);

			Q.push(p, CharNode::compare);
		}

		_root = Q.top();
	}


	// deconstructor
	/*
	1. use a stack to traverse the tree,and push its nodes into an array
	2. then use the array to delete each node
	*/
	CharTree::~CharTree()
	{
		CharNode ** nodes = new CharNode*[_size];

		Stack<CharNode *> S;
		if (_root)
			S.push(_root);

		size_t c = 0;
		CharNode * p = nullptr;
		while (!S.empty()){
			p = S.top();
			S.pop();
			nodes[c++] = p;

			if (p->getRight())
				S.push(p->getRight());
			if (p->getLeft())
				S.push(p->getLeft());
		}

		for (c = 0; c < _size; c++)
			delete nodes[c];
		delete[]nodes;
	}


	// build char-code table
	/*
	the length of the returned array(S) is 256
	the code of char(i) is S[i+128],"i" is [-128,128)
	method:
		use BFS to find all paths which from the root to leaves
		that is, for example:
			cur node is p, cur path is "xxx"
			path of p's left child  is "xxx0"
			path of p's right child is "xxx1"
	*/
	string * CharTree::buildMap()const
	{
		Queue<pair<CharNode *, string>> Q;

		pair<CharNode *, string> cur, next;

		if (_root){
			cur.first = _root;
			cur.second = "";
			Q.push(cur);
		}

		string * table = new string[256];

		while (!Q.empty()){
			cur = Q.front();
			Q.pop();

			if (cur.first->getLeft() == nullptr && cur.first->getRight() == nullptr)
				table[int(cur.first->getCharacter()) + 128] = cur.second;
			else{
				if (cur.first->getLeft()){
					next.first = cur.first->getLeft();
					next.second = cur.second + "0";
					Q.push(next);
				}
				if (cur.first->getRight()){
					next.first = cur.first->getRight();
					next.second = cur.second + "1";
					Q.push(next);
				}
			}
		}
		return table;
	}


}