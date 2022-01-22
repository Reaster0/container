#ifndef _rb_three_
#define _rb_three_
#include <memory>
#include <iterator>
#include <iostream>
#include <stdexcept>
#include "utils.hpp"

//a node is either red or black, the root and leave (NIL) are black (root and leave are probably the same thing)
//a node is either red or black
//If a node is red, then it’s children are black
//All path from root to leave have the same number of black nodesthe root and leave (NIL) are black (root and leave are probably the same thing)

#define RED 1
#define BLACK 0

namespace ft
{
	template <class Key, class T>
	struct node
	{
		Key _key;
		T _value;
		bool _color;
		node* _left;
		node* _right;
		node* _parent;
		node(const Key& key, const T& value, const bool& color, node* left = nullptr, node* right = nullptr, node* parent = nullptr) : _key(key), _value(value), _color(color), _left(left), _right(right), _parent(parent)
		{
		}
		~node()
		{
		}
		node& operator=(const node<Key, T>& other)
		{
			_key = other._key;
			_value = other._value;
			_left = other._left;
			_right = other._right;
			_parent = other._parent;
			return *this;
		}
	};

	template <class Key, class T, class Allocator = std::allocator<ft::node<Key, T> > >
	class rb_tree
	{
		typedef T value_type;
		typedef	Key key_type;
		typedef node<Key, T> node_type;

		private:
			Allocator alloc;
			node_type* best_place(const node_type& start_node, const node<Key, T>& new_node) const
			{
				if (start_node._key > new_node._key)
				{
					if (!start_node._left)
						return start_node._left;
					return best_place(start_node._left, new_node);
				}
				else if (start_node._key < new_node._key)
				{
					if (!start_node._right)
						return start_node._right;
					return best_place(start_node._right, new_node);
				}
				return 0;
			}
			void fill_test(node_type* start_node, int limit, int i = 0)
			{
				if (i >= limit)
					return;
				start_node->_left = alloc.allocate(1);
				alloc.construct(start_node->_left, node_type(i, limit, RED));
				start_node->_left->_parent = start_node;
				fill_test(start_node->_left, limit, i + 1);
			}
			void fill_test_right(node_type* start_node, int limit, int i = 0, int from = 0)
			{
				if (i >= limit)
					return;
				if (from && start_node->_left)
					fill_test_right(start_node->_left, limit, i, from - 1);
				else
				{
					start_node->_right = alloc.allocate(1);
					alloc.construct(start_node->_right, node_type(from, i, RED));
					start_node->_right->_parent = start_node;
					fill_test_right(start_node->_right, limit, i + 1);
				}
			}
		
		public:
			node_type* nodes;
			rb_tree()
			{
				nodes = alloc.allocate(1);
				alloc.construct(nodes, node<int, int>(42 , 99, RED));
				fill_test(nodes, 10);
				fill_test_right(nodes, 2, 0, 5);
			}
			~rb_tree()
			{
				// alloc.destroy(nodes);
				// alloc.deallocate(nodes, 1);
			}
			void add_node(const node_type& node)
			{
				node_type* node_placement = best_place(nodes, node);
				node_placement = alloc.allocate(1);
				alloc.construct(node_placement, node);
			}
			void print_nodes(node_type* nodes, int spaces = 0)
			{
				if (!nodes)
					return;
				spaces++;
				print_nodes(nodes->_left, spaces);
				std::cout << std::endl;
				for (int i = 1; i < spaces; i++)
					std::cout << "	";
				std::cout << nodes->_key << ":" << nodes->_value << std::endl;
				print_nodes(nodes->_right, spaces);
			}

	};
}

#endif