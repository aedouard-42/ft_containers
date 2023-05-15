#ifndef CONST_MAP_ITERATOR_HPP
# define CONST_MAP_ITERATOR_HPP

# include "Node.hpp"
# include "../utils/iterators_traits.hpp"
#include "map.hpp"
#include "../utils/pair.hpp"
#include "map_iterator.hpp"

namespace ft

{
	template <class Category,
				class T,
				class Distance = std::ptrdiff_t,
				class Pointer = T*,
				class Reference = T&>
	class const_iterator {
	public:

		typedef	Category	iterator_category;
		typedef	const T		value_type;
		typedef	Distance	difference_type;
		typedef	const T*	pointer;
		typedef	const T&	reference;

	};

	template < class T>
	class const_map_iterator
	{
		public:
		typedef const_iterator<std::bidirectional_iterator_tag , T> 		iterator;
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


		const_map_iterator(void)
		: _p(NULL), _root(NULL), _nil(NULL) 
		{}

		const_map_iterator(node_pointer node, node_pointer root, node_pointer nil)
		: _p(node), _root(root), _nil(nil) 
		{}

		const_map_iterator(const_map_iterator const &src)
		: _p(src._p), _root(src._root), _nil(src._nil)
		{}
        
        const_map_iterator(map_iterator<T> const &src)
		: _p(src._p), _root(src._root), _nil(src._nil)
		{}

		const_map_iterator	&operator=(const_map_iterator const &rhs) 
		{
			if (this != &rhs) 
			{
				this->_p = rhs._p;
				this->_root = rhs._root;
				this->_nil = rhs._nil;
			}
		return (*this);
		}

		~const_map_iterator()
		{}

		//operator map_iterator<const value_type> () const { return _p; }

        node_pointer get_base() const
        {
            return(_p);
        }

		const_map_iterator& operator++()
		{
			if (_p->right != _nil)
			{
				_p = _p->right;
				while(_p->left && _p->left != _nil)
				{
					_p = _p->left;
				}
			}
			else
			{
				node_pointer tmp = _p;
				while(tmp != _nil)
				{
					if  (tmp->parent == _nil)
					{
						_p = _p->right;
						return *this;
					}
					else if (tmp == tmp->parent->left && tmp)
					{
						_p = tmp->parent;
						return *this;
					}
					tmp = tmp->parent;
				}
			}
			return *this;
		}

		const_map_iterator operator++(int)
		{
			const_map_iterator ret = *this;
			++(*this);
			return ret;
		}

		const_map_iterator& operator--()
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

		const_map_iterator operator--(int)
		{
			const_map_iterator ret = *this;
			--(*this);
			return ret;
		}

		reference operator*() const { return *_p->content; }
		pointer operator->() const{ return &(*_p->content); }

		//template <typename U>
		bool operator==(const const_map_iterator<T>& rhs) const { return _p == rhs._p; }
		//template <typename U>
		bool operator!=(const const_map_iterator<T>& rhs) const { return _p != rhs._p; }
	};

    template <typename U, typename T>
    bool operator==(const_map_iterator<T> &lhs ,const_map_iterator<U>& rhs) { return lhs.get_base() == rhs.get_base(); }
    template <typename U, typename T>
    bool operator!=(const_map_iterator<T> &lhs, const_map_iterator<U>& rhs) { return lhs.get_base() != rhs.get_base(); }


}



#endif /* ************************************************************* MAP_ITERATOR_HPP */
