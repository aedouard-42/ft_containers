#ifndef ALGORITHMS_HPP
# define ALGORITHMS_HPP

# include <iostream>
# include <string>

#include "iterators_traits.hpp"

namespace ft
{
	template<class T>
	void swap(T& a , T& b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}

	template<class InputIt>
	typename iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last)
	{
		typename iterator_traits<InputIt>::difference_type n = 0;
		while (first != last)
		{
			++first;
			++n;
		}
		return n;
	}

}




#endif /* ************************************************************* ALGORITHMS_HPP */
