#include "HashPool.h"
using Seven::HashPool;

#include "HashTable.h"
using Seven::HashTable;

#include "HashStrategy.h"
using Seven::HashStrategy;

#include <iostream>
using std::cout;

#include <string>
using std::string;

// compare two string keys
int mycompare(const string & left,const string & right){
	if(left<right) return -1;
	if(left>right) return 1;
	return 0;
}

// main for show how it works
int main()
{	
	// 1. create a HashTable
	HashTable<string,int> * table=HashTable<string,int>::newInstance(4,HashStrategy::hashString,mycompare);

	// 2. do some CURD
	table->put("balance",6800);
	table->put("age",22);
	table->put("id",340);
	table->put("birthplace",78);
	table->put("aaa",111);
	table->put("bbb",222);
	table->put("ccc",333);
	table->put("birthplace",7788);
	table->add("redis",6372);
	table->replace("aaa",11111);
	table->remove("birthplace");
	table->remove("bbb");

	// 3. use the Iterator
	HashTable<string,int>::Iterator it=table->iterator();
	while(it.hasNext()){
		it.toNext();
		cout<<it.getKey()<<'\t'<<*it.getValue()<<'\n';
	}
	
	// 4. delete the HashTable
	delete table;

	// 5. clean all the nodes in the recycle pool
	HashPool<string,int>::destroyInstance();
	return 0;
}