#include "CharNode.h"

namespace Seven
{
	// default constructor
	CharNode::CharNode()
	{
		_left = nullptr;
		_right = nullptr;
	}

	// non-default constructor
	CharNode::CharNode(char character, size_t frequency)
	{
		_character = character;
		_frequency = frequency;
		_left = nullptr;
		_right = nullptr;
	}

	// get character
	char CharNode::getCharacter()const
	{
		return _character;
	}

	// get frequency
	size_t CharNode::getFrequency()const
	{
		return _frequency;
	}

	// get left child node
	CharNode * CharNode::getLeft()const
	{
		return _left;
	}

	// get right child node
	CharNode * CharNode::getRight()const
	{
		return _right;
	}

	// set character
	void CharNode::setCharacter(char character)
	{
		_character = character;
	}

	// set frequency
	void CharNode::setFrequency(size_t frequency)
	{
		_frequency = frequency;
	}

	// set left child node
	void CharNode::setLeft(CharNode * left)
	{
		_left = left;
	}

	// set right child node
	void CharNode::setRight(CharNode * right)
	{
		_right = right;
	}

	// compare priority
	/*
	the frequency is smaller,the priority is higher
	*/
	int CharNode::compare(CharNode * const & left, CharNode * const & right)
	{
		if (left->getFrequency() < right->getFrequency())
			return 1;
		if (left->getFrequency() > right->getFrequency())
			return -1;
		return 0;
	}

}