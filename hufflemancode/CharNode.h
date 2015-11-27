#ifndef _CHARNODE_H
#define _CHARNODE_H

namespace Seven
{
	// char node in huffleman tree
	class CharNode
	{
	private:
		char _character;     // the char
		size_t _frequency;   // frequency of this char
		CharNode * _left;    // its left child node
		CharNode * _right;   // its right child node
	public:
		// constructor
		CharNode();                                 // default constructor     (ok)
		CharNode(char character, size_t frequency); // non-default constructor (ok)
		// get
		char getCharacter()const;                   // get character           (ok)
		size_t getFrequency()const;                 // get frequency           (ok)
		CharNode * getLeft()const;                  // get left child node     (ok)
		CharNode * getRight()const;                 // get right child node    (ok)
		// set
		void setCharacter(char character);          // set character           (ok)
		void setFrequency(size_t frequency);        // set frequency           (ok)
		void setLeft(CharNode * left);              // set left child node     (ok)
		void setRight(CharNode * right);            // set right child node    (ok)
		// compare priority                                                    (ok)
		static int compare(CharNode * const & left, CharNode * const & right);
	};
}

#endif