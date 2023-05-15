#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "Node.hpp"
# include "../utils/iterators_traits.hpp"
#include "map.hpp"
#include "../utils/pair.hpp"

namespace ft

{
	template <class Category,
				class T,
				class Distance = std::ptrdiff_t,
				class Pointer = T*,
				class Reference = T&>
	class iterator {
	public:

		typedef	Category	iterator_category;
		typedef	T			value_type;
		typedef	Distance	difference_type;
		typedef	T*			pointer;
		typedef	T&			reference;

	};

	template < class T>
	class map_iterator
	{
		public:

		typedef iterator<std::bidirectional_iterator_tag , T> 				iterator;
		typedef	ft::iterator_traits<iterator>								iterator_traits;
		typedef	typename 	iterator_traits::difference_type				difference_type;
		typedef typename 	iterator_traits::value_type						value_type;
		typedef typename	iterator_traits::pointer						pointer;
		typedef typename	iterator_traits::reference						reference;
		typedef typename	iterator_traits::iterator_category				iterator_category;
		typedef typename 	value_type::first_type							key_type;
		typedef const 		key_type										const_key_type;
		typedef typename	value_type::second_type							mapped_type;
		typedef				Node<const_key_type, mapped_type>				node;
		typedef				node*											node_pointer;

		node_pointer _p;
		node_pointer _root;
		node_pointer _nil;


		map_iterator(void)
		: _p(NULL), _root(NULL), _nil(NULL) 
		{}

		map_iterator(node_pointer node, node_pointer root, node_pointer nil)
		: _p(node), _root(root), _nil(nil) 
		{}

		map_iterator(map_iterator const &src)
		: _p(src._p), _root(src._root), _nil(src._nil)
		{}

		map_iterator	&operator=(map_iterator const &rhs) 
		{
			if (this != &rhs) 
			{
				this->_p = rhs._p;
				this->_root = rhs._root;
				this->_nil = rhs._nil;
			}
		return (*this);
		}

		node_pointer get_base() const
        {
            return(_p);
        }

		~map_iterator()
		{}

		//operator map_iterator<const value_type> () const { return _p; }

		map_iterator& operator++()
		{
			if(_p == _nil || is_sentinel(_p))
				return *this;
			if (_p->right != _nil)
			{
				_p = _p->right;
				while(_p->left != _nil)
				{
					_p = _p->left;
				}
				return *this;
			}
			node_pointer tmp = _p;
			while(tmp != _nil)
			{
				if  (node_side(tmp) == LEFT)
				{
					_p= tmp->parent;
					return *this;
				}
				tmp = tmp->parent;
			}
			return *this;
		}

		map_iterator operator++(int)
		{
			map_iterator ret = *this;
			++(*this);
			return ret;
		}

		map_iterator& operator--()
		{
			if (is_sentinel(_p))
				_p = _p->parent;
			else if (_p->left != _nil)
			{
				_p = _p->left;
				while (_p->right != _nil)
					_p = _p->right;
			}
			else
			{
				node_pointer tmp = _p;
				while (tmp != _nil)
				{
					if (tmp->parent == _nil)
					{
						_p = _p->left;
						break ;
					}
					else if (node_side(tmp) == RIGHT)
					{
						_p = tmp->parent;
						break ;
					}
					tmp = tmp->parent;
				}
			}
			return *this;
		}

		map_iterator operator--(int)
		{
			map_iterator ret = *this;
			--(*this);
			return ret;
		}

		reference operator*() const { return *_p->content; }
		pointer operator->() const{ return &(*_p->content); }
		//template <typename U>
		bool operator==(const map_iterator<T>& rhs) const { return _p == rhs._p; }
		//template <typename U>
		bool operator!=(const map_iterator<T>& rhs) const { return _p != rhs._p; }
	};

	// template <typename U, typename T>
    // bool operator==(map_iterator<T> &lhs ,map_iterator<U>& rhs) { return lhs.get_base() == rhs.get_base(); }
    // template <typename U, typename T>
    // bool operator!=(map_iterator<T> &lhs, map_iterator<U>& rhs) { return lhs.get_base() != rhs.get_base(); }


}



#endif /* ************************************************************* MAP_ITERATOR_HPP */
