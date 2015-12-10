#ifndef _GC_H
#define _GC_H

#include <vector>
using std::vector;

namespace Seven
{
	//Tip : Ref and RefPool are mostly used for scene tree

	//the class of ref count,used for rubbish recover
	class Ref
	{
	private:
		void * _data;                         //the real data
		unsigned int _count;                  //ref count of the data
	public:
		Ref(void * data, unsigned int count); //construct                         (ok)
		~Ref();                               //deconstruct                       (ok)
		//get:
		void * getData()const;                //get the data                      (ok)
		unsigned int getCount()const;         //get the ref count of the data     (ok)
		//functions:
		void print()const;                    //print address and the ref count   (ok)
		void retain();                        //retain the data                   (ok)
		void release();                       //release the data                  (ok)
		void autorelease();                   //let the data autorelease          (ok)
	};

	//the class of ref pool,used for manage Ref objects
	class RefPool
	{
	private:
		vector<Ref *> _pool;              //pool of Ref objects
		static RefPool * _instance;       //the single instance
		RefPool();                        //construct                             (ok)
	public:
		static RefPool * getInstance();   //get the single instance               (ok)
		static void destroyInstance();    //destroy the singale instance          (ok)
		~RefPool();                       //destructor                            (ok)
		void add(Ref * ref);              //add one Ref object to the pool        (ok)
		void recollect();                 //recollect rubbish object in the pool  (ok)
		void rmAll();                     //immediately clear all the objects     (ok)
		bool empty()const;                //whether the pool is empty             (ok)
		void print()const;                //print objects in the pool             (ok)
	};
}

#endif