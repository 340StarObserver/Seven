/*
Author 		: 	Lv Yang
Created 	: 	26 April 2017
Modified 	: 	26 April 2017
Version 	: 	1.0
*/

#ifndef SEVEN_MAP_H
#define SEVEN_MAP_H

namespace Seven
{
	template<class K, class V>
	class Map
	{
	public:
		virtual V get(const K & key)const=0;

		virtual void set(const K & key, const V & value)=0;

		virtual bool exist(const K & key)const=0;

		virtual void remove(const K & key)=0;
	};

	class KeyNotFoundException : public std::exception
	{
	private:
		static const char * msg;
	public:
		KeyNotFoundException() : std::exception(){

		}

		virtual const char * what()const throw(){
			return msg;
		}
	};

	const char * KeyNotFoundException::msg = "Exception key not found";
}

#endif
