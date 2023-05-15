#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template<class T1, class T2> 
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		pair():first(first_type()), second(second_type()){};
		pair( const T1 &x, const T2 &y ):first(x), second(y){};
		template< class U1, class U2 >
		pair( const pair<U1, U2>& p ):first(p.first), second(p.second){};
	
		pair& operator=( const pair& other )
		{
			if (this == &other)
				return *this;
			first = other.first;
			second = other.second;
			return *this;
		};

		friend bool operator==( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
		{
			return(lhs.first == rhs.first && lhs.second == rhs.second);
		};
		friend bool operator!=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
		{
			return (!(lhs == rhs));
		};
		friend bool operator<( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
		{
			if (lhs.first < rhs.first)
				return true;
			else if (lhs.first > rhs.first)
				return false;
			else if (lhs.second < rhs.second)
				return true;
			else
				return false;
		};
		friend bool operator<=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
		{
			return (!(rhs < lhs ));
		};
		friend bool operator>( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
		{
			return (rhs < lhs);
		};
		friend bool operator>=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
		{
			return (!(lhs < rhs));
		};
	};

	template< class T1, class T2 >
	pair<T1,T2> make_pair( T1 t, T2 u )
	{
		return (pair<T1, T2>(t, u));
	};
}


#endif /* ************************************************************* PAIR_HPP */
