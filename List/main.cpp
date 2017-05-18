/*
 * Author 	: 	Lv Yang
 * Create 	: 	18 May 2017
 * Modify 	: 	18 May 2017
 * Version 	: 	1.0
 */

#include <iostream>
using std::cout;

#include "List.h"
using Seven::List;

int main()
{
	List<int> list;
	
	list.addHead(1);
	list.addTail(2);
	list.addTail(3);
	list.addHead(4);
	list.addTail(5);
	list.addHead(6);
	list.addTail(7);

	try{
		cout << "head : " << list.readHead() << '\n';
	}catch(const std::exception & e){
		cout << e.what() << '\n';
	}

	try{
		cout << "tail : " << list.readTail() << '\n';
	}catch(const std::exception & e){
		cout << e.what() << '\n';
	}

	return 0;
}
