/*
 * Author 	: 	Lv Yang
 * Create 	: 	17 May 2017
 * Modify 	: 	17 May 2017
 * Version 	: 	1.0
 */

#include <iostream>
using std::cout;

#include "UFset.h"
using Seven::UFset;

int main()
{
	UFset ufs(8);

	ufs.link(4, 7);
	ufs.link(1, 3);
	ufs.link(2, 7);
	ufs.link(5, 8);
	ufs.link(0, 6);
	ufs.link(9, 6);
	ufs.link(6, 2);
	ufs.link(5, 4);

	for(std::size_t i = 1; i <= ufs.getSize(); i++)
		cout << "find " << i << " : " << ufs.find(i) << '\n';
	cout << '\n';

	ufs.resize(16);

	ufs.link(8, 12);
	ufs.link(11, 3);
	ufs.link(15, 7);
	ufs.link(14, 15);
	ufs.link(2, 11);

	for(std::size_t i = 1; i <= ufs.getSize(); i++)
		cout << "find " << i << " : " << ufs.find(i) << '\n';
	cout << '\n';

	return 0;
}
