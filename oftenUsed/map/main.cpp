/*
Author 		: 	Lv Yang
Created 	: 	26 April 2017
Modified 	: 	08 May 2017
Version 	: 	1.0
*/

#include <iostream>
using std::cout;

#include <string>
using std::string;

#include "Map.h"
using Seven::Map;
using Seven::KeyNotFoundException;

#include "HashMap.h"
using Seven::HashNode;
using Seven::HashPool;
using Seven::HashMap;

std::size_t myHash(const string & key, std::size_t range){
	return key.length() % range;
}

int myCmp(const string & lvs, const string & rvs){
	if(lvs < rvs)
		return -1;
	if(lvs > rvs)
		return 1;
	return 0;
}

int main()
{
	// test HashMap<K, V>
	{
		HashPool<string, int>::setInitSize(4);
		HashPool<string, int>::getInstance();

		Map<string, int> * map = HashMap<string, int>::create(8, myHash, myCmp);

		map->set("shangjun", -338);
		map->set("Y", 0);
		map->set("wuan", 61);
		map->set("yinsi", 56);
		map->set("yinji", 72);
		map->set("changping", 24);
		map->set("observer", 340);
		map->set("H", 18);
		map->set("zhaowulingjun", 66);
		map->set("suqin", 22);

		map->set("shangjun", 338);
		map->set("H", 1818);

		map->remove("observer");
		map->remove("changping");
		map->remove("wuan");
		map->remove("yinsi");
		map->remove("seven");

		cout << "exist observer : " << map->exist("observer") << '\n';
		cout << "exist shangjun : " << map->exist("shangjun") << '\n'; 

		try{
			cout << "get observer : " << map->get("observer") << '\n';
		}catch(std::exception & e){
			cout << e.what() << '\n';
		}
		try{
			cout << "get shangjun : " << map->get("shangjun") << '\n';
		}catch(std::exception & e){
			cout << e.what() << '\n';
		}
		
		delete map;

		HashPool<string, int>::destroyInstance();
	}

	// test TreeMap<K, V>
	{
		
	}

	return 0;
}
