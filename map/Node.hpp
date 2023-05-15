#ifndef NODE_HPP
# define NODE_HPP

# include "../utils/pair.hpp"

# define LEFT 0
# define RIGHT 1
# define left  child[LEFT]
# define right child[RIGHT]
# define is_sentinel(node_pointer) (node_pointer->content == 0 ? true : false)
# define node_side(node_pointer) (node_pointer == node_pointer->parent->right ? RIGHT : LEFT)

namespace ft {

	template <class T1, class T2>
	struct Node
	{
		typedef typename 	ft::pair<const T1,T2>* 		pointer;
		typedef				Node*						node_pointer;
		typedef				Node&						node_reference;

		pointer content;
		node_pointer parent;
		int color;
		node_pointer child[2];

		node_pointer in_order_successor()
		{
			node_pointer node = this->right;
			while (node->left && !is_sentinel(node->left))
				node = node->left;
			return node;
		}
	};
}


#endif /* ************************************************************* NODE_HPP */
