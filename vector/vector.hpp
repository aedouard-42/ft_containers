#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "../utils/reverse_iterator.hpp"
# include "../utils/enable_if.hpp"
# include "../utils/is_integral.hpp"
# include "../utils/lexicographical_compare.hpp"
# include "../utils/iterators_traits.hpp"
# include "../utils/algorithms.hpp"

namespace ft 
{
	template <class T, class Allocator = std::allocator<T> >
	class vector 
	{
		public:
		// types:
		typedef typename Allocator::reference					reference;
		typedef typename Allocator::const_reference 			const_reference;
		typedef std::size_t 									size_type; 
		typedef std::ptrdiff_t									difference_type;
		typedef T												value_type;
		typedef Allocator										allocator_type;
		typedef typename Allocator::pointer						pointer;
		typedef typename Allocator::const_pointer				const_pointer;
		typedef pointer											iterator;
		typedef const_pointer									const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		private:
		Allocator		_allocator;
		pointer			_start;
		pointer			_end;
		size_type		_capacity;

		void	_reallocate(size_t size_add)
		{
			size_t newsize = size() + size_add;
			size_t buffer_realloc;

			if (newsize <= capacity())
				return;
			if (size_add == 1)
				buffer_realloc = 2 * (capacity());
			else
				buffer_realloc = 2 * size();
			if (newsize > buffer_realloc)
				reserve (newsize);
			else
				reserve (buffer_realloc);
		}

		public :

		//constructeurs
		vector()
		:
		_allocator(),
		_start(_allocator.allocate(0)),
		_end(_start),
		_capacity(0)
		{}
		explicit vector( const Allocator& alloc )
		:
		_allocator(alloc),
		_start(_allocator.allocate(0)),
		_end(_start),
		_capacity(0)
		{}
		explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator())
		:
		_allocator(alloc),
		_start(_allocator.allocate(0)),
		_end(_start),
		_capacity(0)
		{
			assign(count, value);
		}

		template< class InputIt >
		vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() )
		:
		_allocator(alloc),
		_start(_allocator.allocate(0)),
		_end(_start),
		_capacity(0)
		{
			assign(first, last);
		}

		vector( const vector& other )
		:
		_allocator(other._allocator),
		_start(_allocator.allocate(0)),
		_end(_start),
		_capacity(0)
		{
			assign(other.begin(), other.end());
		}

		void assign( size_type count, const T& value )
		{
			clear();
			insert(_start, count, value);
		}

		template< class InputIt >
		void assign( InputIt first, InputIt last , typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true)
		{
			clear();
			insert(begin(), first, last);
		}

		allocator_type get_allocator() const
		{
			return _allocator;
		}

		vector& operator=( const vector& other )
		{
			if (this == &other) { return *this; }
			this->assign(other.begin(), other.end());
			return *this;
		}

		~vector()
		{
			for (size_type i = 0; i < size() ; i++) { _allocator.destroy(&_start[i]); }
			_allocator.deallocate(_start, _capacity);
			_start = 0;
		}

		//functions


		/* capacity functions*/

		size_type size() const
		{return (_end - _start);}

		size_type max_size() const
		{return (_allocator.max_size());}

		size_type capacity() const
		{return (_capacity);}

		bool empty() const
		{return (_start == _end);}

		void reserve( size_type new_cap )
		{
			if (new_cap >= max_size())
				throw std::length_error("vector::reserve");
			if (new_cap > capacity())
			{
				pointer new_start;
				size_type old_size = size();

				new_start = _allocator.allocate(new_cap);
				for (size_type i = 0; i < old_size; i++)
				{
					_allocator.construct(new_start + i, _start[i]);
					_allocator.destroy(_start + i);
				}
				_allocator.deallocate(_start, capacity());
				_start = new_start;
				_end = _start + old_size;
				_capacity = new_cap;
			}
		}

		/* MODIFIERS */

		void push_back( const T& value )
		{
			//T vcpy = value; // just in case reserve destroys it
			_reallocate(1);
			_allocator.construct(_end, value);
			_end++;
		}

		void pop_back()
		{
			_allocator.destroy(_end - 1);
			_end--;
		}

		void clear()
		{
			for (size_type i = 0; i < size(); i++)
				_allocator.destroy(_start + i);
			_end = _start;
		}

		iterator insert( iterator pos, const T& value )
		{
			if (pos == _end)
			{
				push_back(value);
				return (_end - 1);
			}
			difference_type n_move = _end - pos;
			_reallocate(1);
			pointer previous = _end - 1;
			pointer current = previous + 1;
			for (difference_type i = 0; i < n_move; i++)
			{
				if (current >= _start + size())
					_allocator.construct(current, *previous);
				else
					*current = *previous;
				--current;
				--previous;
			}
			if (current >= _start + size())
				_allocator.construct(current, value);
			else
				*current = value;
			_end++;
			return (current);
		}

        void insert( iterator pos, size_type count, const T& value )
        {
            if (count == 0)
                return ;
            difference_type n_moves = _end - pos;
            _reallocate(count);
            pointer previous = _end - 1;
            pointer current = previous + count;

            // decalage des anciens elements
            for (difference_type i = 0; i < n_moves; i++)
            {
                if (current >= _start + size())
                    _allocator.construct(current, *previous);
                else
                    *current = *previous;
                --current;
                --previous;
            }
            //construction des nouveaux
            for (size_type i = 0; i < count; i++)
            {
                if (current >= _start + size())
                    _allocator.construct(current, value);
                else
                    *current = value;
                current--;
            }
            _end += count;
        }
		
		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last , typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true)
		{
			if (first == last)
				return ;
			size_type  count = ft::distance( first, last);
			difference_type n_moves = _end - pos;
			
			_reallocate(count);
			pointer previous = _end - 1;
			pointer current = previous + count;
			for (difference_type i = 0; i < n_moves; i++)
			{
				if (current >= _start + size())
					_allocator.construct(current, *previous);
				else
					*current = *previous;
				current--;
				previous--;
			}
			last--;
			for (size_type i = 0; i < count; i++)
			{
				if (current >= _start + size())
					_allocator.construct(current, *(last));
				else
					*current = *(last);
				current--;
				last--;
			}
			_end += count;
		}

		iterator erase( iterator pos )
		{
			return(erase(pos, pos + 1));
		}

		iterator erase( iterator first, iterator last )
		{
			size_t erase_count = last - first;
			pointer ret = first;

			while (last != _end)
			{
				*first = *last;
				first++;
				last++;
			}
			while (first != _end)
			{
				_allocator.destroy(first);
				first++;
			}
			_end -= erase_count;
			return (ret);
		}

		void resize( size_type count, T value = T() )
		{
			if (count < size())
			{
				while (count < size())
				{
					_allocator.destroy(_end - 1);
					_end--;
				}
			}
			else
			{
				size_type size_diff = count - size();

				_reallocate(count - size());
				while (size_diff > 0)
				{
					_allocator.construct(_end, value);
					_end++;
					size_diff--;
				}
			}
		}

		void swap( vector& other )
		{
			ft::swap(_start, other._start);
			ft::swap(_end, other._end);
			ft::swap(_capacity, other._capacity);
		}

		/* ELEMENT ACCES*/

		reference back()
		{return (*(_end - 1));}

		const_reference back() const
		{return (*(_end - 1));}

		reference operator[]( size_type pos )
		{return _start[pos];}

		const_reference operator[]( size_type pos ) const
		{return _start[pos];}

		reference at( size_type pos )
		{
			if (!(pos < size()))
				throw (std::out_of_range("ft::vector::at"));
			return _start[pos];
		}
		const_reference at( size_type pos ) const
		{
			if (!(pos < size()))
				throw (std::out_of_range("ft::vector::at"));
			return _start[pos];
		}

		reference front()
		{return (_start[0]);}
		const_reference front() const
		{return (_start[0]);}

			/* iterators */

		iterator begin()
		{return _start;}

		const_iterator begin() const
		{return _start;}

		iterator end()
		{return _end;}

		const_iterator end() const
		{return _end;}

		reverse_iterator rbegin()
		{return reverse_iterator(end());}

		const_reverse_iterator rbegin() const
		{return const_reverse_iterator(end());}

		reverse_iterator rend()
		{return reverse_iterator(begin());}

		const_reverse_iterator rend() const
		{return const_reverse_iterator(begin());}
	};

	template< class T, class Alloc >
	bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		else
			for (size_t i = 0; i < lhs.size(); i++)
			{
				if (lhs[i] != rhs[i])
					return (false);
			}
		return (true);
	}

	template< class T, class Alloc >bool operator!=( const ft::vector<T,Alloc>& lhs,const ft::vector<T,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class T, class Alloc >
	bool operator<( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
	{
		return(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class T, class Alloc >
	bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
	{
		return !(rhs < lhs);
	}

	template< class T, class Alloc >bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template< class T, class Alloc >bool operator>=( const ft::vector<T,Alloc>& lhs,const ft::vector<T,Alloc>& rhs )
	{
		return !(lhs < rhs);
	}

	template< class T, class Alloc >
	void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs )
	{
		lhs.swap(rhs);
	}
}

#endif /* ************************************************************* VECTOR_HPP */
