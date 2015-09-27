#include "stdafx.h"

#include "GC.h"

#include <iostream>
using std::cout;

namespace Seven
{
	/* Ref: */
	//construct
	//inform: data must be in heap region, can not be in stack region
	Ref::Ref(void * data, unsigned int count)
	{
		_data = data;
		_count = count;
	}

	//deconstruct
	Ref::~Ref()
	{

	}

	//get the data
	void * Ref::getData()const
	{
		return _data;
	}

	//get the ref count of the data
	unsigned int Ref::getCount()const
	{
		return _count;
	}

	//print address of the data and the ref count
	void Ref::print()const
	{
		cout << "address: " << _data << '\t';
		cout << "ref count: " << _count << '\n';
	}

	//retain the data
	/*
	increase the ref count of the data
	*/
	void Ref::retain()
	{
		_count++;
	}

	//release the data
	/*
	1. decrease the ref count of the data
	2. if now the ref count is zero:
	      then delete data and make the data null
	*/
	void Ref::release()
	{
		if (_count > 0)
			_count--;
		if (_count == 0 && _data)
		{
			delete _data;
			_data = nullptr;
		}
	}

	//let the data autorelease
	/*
	1. first retain the data
	2. then put it into ref pool,let ref pool to deal with it
	*/
	void Ref::autorelease()
	{
		retain();
		RefPool::getInstance()->add(this);
	}

	//--------------------------------------------------

	/* RefPool: */

	//origin the single instance
	RefPool * RefPool::_instance = nullptr;

	//construct
	RefPool::RefPool()
	{

	}

	//deconstruct
	//first immediately clear all the objects in the pool
	RefPool::~RefPool()
	{
		rmAll();
	}

	//get the single instance
	/*
	if current the single instance is null:
	   then new it
	return the single instance
	*/
	RefPool * RefPool::getInstance()
	{
		if (_instance == nullptr)
			_instance = new RefPool();
		return _instance;
	}

	//destroy the singale instance
	/*
	if current the single instance is not null:
	   delete it
	   make it null
	*/
	void RefPool::destroyInstance()
	{
		if (_instance)
		{
			delete _instance;
			_instance = nullptr;
		}
	}

	//add one Ref object to the pool
	void RefPool::add(Ref * ref)
	{
		_pool.push_back(ref);
	}

	//recover object in the pool
	/*
	1. release all the Ref objects in the pool
	2. remove those objects whose count == 0
	*/
	void RefPool::recollect()
	{
		size_t N = _pool.size();
		for (size_t i = 0; i < N; i++)
			_pool[i]->release();
		size_t ans = 0;
		for (size_t i = 0; i + ans < N; i++)
		{
			while (i + ans < N && _pool[i + ans]->getCount() == 0)
			{
				delete _pool[i + ans];
				ans++;
			}
			if (i + ans < N)
				_pool[i] = _pool[i + ans];
		}
		_pool.erase(_pool.begin() + N - ans, _pool.end());
	}

	//immediately clear all the objects
	/*
	1. for each one Ref object in the pool:
	{
	   delete its real data
	   delete the Ref object self
	}
	2. clear the pool
	*/
	void RefPool::rmAll()
	{
		size_t N = _pool.size();
		void * tmp = nullptr;
		for (size_t i = 0; i < N; i++)
		{
			if (_pool[i])
			{
				tmp = _pool[i]->getData();
				if (tmp)
					delete tmp;
				delete _pool[i];
			}
		}
		_pool.clear();
	}

	//whether the pool is empty
	bool RefPool::empty()const
	{
		return _pool.size() == 0;
	}

	//print objects in the pool
	void RefPool::print()const
	{
		cout << "\nrefpool: \n";
		size_t N = _pool.size();
		if (N == 0)
		{
			cout << "empty\n\n";
			return;
		}
		for (size_t i = 0; i < N; i++)
		{
			if (_pool[i])
				_pool[i]->print();
		}
		cout << '\n';
	}

}