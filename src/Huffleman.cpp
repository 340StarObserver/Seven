#include "Huffleman.h"
#include <cstring>
using std::memset;

namespace Seven
{
	// count each character in a string
	/*
	char is [-128,128),
	index is [0,256),so index=int(ch)+128
	*/
	size_t * Huffleman::count(const string & str)const
	{
		size_t * res = new size_t[256];
		memset(res, 0, sizeof(size_t) * 256);
		size_t N = str.size();
		for (size_t i = 0; i < N; i++)
			res[int(str[i]) + 128]++;
		return res;
	}


	// constructor
	Huffleman::Huffleman()
	{
		_tree = nullptr;
	}


	// deconstructor
	Huffleman::~Huffleman()
	{
		if (_tree)
			delete _tree;
	}


	// encode
	/*
	1. calcuate frequency of each character
	2. create a Huffleman Tree based on these frequency
	3. create the codeTable by traversing the tree
	4. traverse the message and use the codeTable to form the encoded string
	*/
	string Huffleman::encode(const string & message)
	{
		size_t * frequency = count(message);

		if (_tree)
			delete _tree;
		_tree = new CharTree(frequency, 256);
		delete[]frequency;

		string * codeTable = _tree->buildMap();

		string res = "";
		size_t N = message.size();
		for (size_t i = 0; i < N; i++)
			res.append(codeTable[int(message[i]) + 128]);
		delete[]codeTable;

		return res;
	}


	// decode
	/*
	the input message is made up by '0' or '1'
	and the method is followed:
	1. originlize the result as ""
	2. let "p" point to the root of the Huffleman Tree
	3. for ch in message:
		if ch is '0':
			move p to its left child
		else:
			move p to its right child
		now,if p has no child:
			add p's character to result
			move p to root
	4. return result
	*/
	string Huffleman::decode(const string & message)const
	{
		if (_tree == nullptr)
			return "";

		string result = "";

		CharNode * p = _tree->getRoot();

		size_t N = message.size();
		for (size_t i = 0; i < N; i++){
			if (message[i] == '0')
				p = p->getLeft();
			else
				p = p->getRight();
			if (p->getLeft() == nullptr && p->getRight() == nullptr){
				result += p->getCharacter();
				p = _tree->getRoot();
			}
		}

		return result;
	}

}