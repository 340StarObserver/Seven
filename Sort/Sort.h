/*
 * Author 	: 	Lv Yang
 * Created 	: 	15 May 2017
 * Modified : 	15 May 2017
 * Version 	: 	1.0
 */

#ifndef _SORT_H
#define _SORT_H

namespace Seven
{
	template<class T>
	class Sort
	{
	public:
		/*
		 * base deconstructor
		 */
		virtual ~Sort(){};

		/*
		 * base sort
		 * 1. type T should satisfy :
		 *     a. default constructor
		 *     b. copy constructor
		 *     c. operator =
		 * 2. func cmp returns :
		 *    = 0 : lhs = rhs
		 *    < 0 : lhs < rhs
		 *    > 0 : lhs > rhs
		 */
		virtual void sort(T * data, std::size_t n, int(*cmp)(const T & lhs, const T & rhs)) const = 0;
	};
}

#endif
