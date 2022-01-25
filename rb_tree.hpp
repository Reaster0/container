#ifndef _rb_three_
#define _rb_three_
#include <memory>
#include <iterator>
#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include "utils.hpp"
#include "node.hpp"

//a node is either red or black, the root and leave (NIL) are black (root and leave are probably the same thing)
//a node is either red or black
//If a node is red, then it’s children are black
//All path from root to leave have the same number of black nodesthe root and leave (NIL) are black (root and leave are probably the same thing)

namespace ft
{
	template <class Key, class T, class Allocator = std::allocator<ft::node<Key, T> > >
	class rb_tree
	{
		typedef T value_type;
		typedef	Key key_type;
		typedef node<Key, T> node_type;

		private:
			Allocator alloc;
			void collor_node(node_type** node)
			{
				if (!(*node)->_parent) //case root
					(*node)->_color = BLACK;
				else if ((*node)->uncle()) //other cases
				{
					if ((*node)->uncle()->_color == RED)
					{
						(*node)->_color = RED;
						(*node)->_parent->_color = BLACK;
						(*node)->_parent->_parent->_color = RED;
						(*node)->uncle()->_color = BLACK;
					}
					else if ((*node)->uncle()->_color == BLACK)
					{
						//triangle case
						if ((*node) == (*node)->_parent->_left && (*node)->_parent == (*node)->_parent->_parent->_right) // case triangle right
						{
							node_type* P = *node;
							P->_right = P->_parent;
							P->_parent->_left = nullptr;
							node_type* tempParentParent = P->_parent->_parent;
							if (tempParentParent)
								tempParentParent->_right = P;
							P->_parent->_parent = P;
							P->_parent = tempParentParent;
							//maybe an issue here with many node
						}
						//triangle case rev
						else if ((*node) == (*node)->_parent->_right && (*node)->_parent == (*node)->_parent->_parent->_left) // case triangle left
						{
							node_type* P = *node;
							P->_left = P->_parent;
							P->_parent->_right = nullptr;
							node_type* tempParentParent = P->_parent->_parent;
							if (tempParentParent)
								tempParentParent->_left = P;
							P->_parent->_parent = P;
							P->_parent = tempParentParent;
							//maybe an issue here with many node
						}
						//line rotation left
						else if ((*node) == (*node)->_parent->_left && (*node)->_parent == (*node)->_parent->_parent->_left)
						{
							node_type* P = (*node)->_parent;
							P->_parent->_left = P->_right;
							P->_right->_parent = P->_parent;
							P->_right = P->_parent;
							node_type* tempParentParent = P->_parent->_parent;
							P->_parent->_parent = P;
							P->_parent = tempParentParent;
							P->_color = BLACK;
							P->_right->_color = RED;
							P->_left->_color = RED;
							//maybe an issue here with many node
						}
						//line rotation right
						else if ((*node) == (*node)->_parent->_right && (*node)->_parent == (*node)->_parent->_parent->_right)
						{
							node_type* P = (*node)->_parent;
							P->_parent->_right = P->_left;
							P->_left->_parent = P->_parent;
							P->_left = P->_parent;
							node_type* tempParentParent = P->_parent->_parent;
							P->_parent->_parent = P;
							P->_parent = tempParentParent;
							P->_color = BLACK;
							P->_right->_color = RED;
							P->_left->_color = RED;
							//maybe an issue here with many node
						}
					}
				}
				else
					(*node)->_color = RED;
			}

			void insert_util(const node_type& node, node_type** start_node, node_type* parent = nullptr)
			{
				if (!*start_node)
				{
					*start_node = alloc.allocate(1);
					alloc.construct(*start_node, node);
					(*start_node)->_parent = parent;
					//if ((*start_node)->_value == 'L')
					collor_node(start_node);
				}
				else if (node > **start_node)
					insert_util(node, &((*start_node)->_right), *start_node);
				else if (node < **start_node)
					insert_util(node, &((*start_node)->_left), *start_node);
				else
					throw std::string("the keys node's are the same");
			}
			T& find_util(const Key& value, node_type* node)
			{
				if (!node)
					throw std::string("invalid key");
				if (node->_key == value)
					return node->_value;
				if (node->_key < value)
					return find_util(value, node->_right);
				else
					return find_util(value, node->_left);
			}
			node_type* find_node_util(const Key& value, node_type* node)
			{
				if (!node)
					throw std::string("invalid key");
				if (node->_key == value)
					return node;
				if (node->_key < value)
					return find_node_util(value, node->_right);
				else
					return find_node_util(value, node->_left);
			}
			void print_nodes_utils(node_type* nodes, int spaces = 0)
			{
				if (!nodes)
					return;
				spaces++;
				print_nodes_utils(nodes->_left, spaces);
				std::cout << std::endl;
				for (int i = 1; i < spaces; i++)
					std::cout << "	";
				if (nodes->_color == RED)
				{
					std::cout << "\033[31m" << nodes->_key << ":" << nodes->_value << "\033[0m"; //<< std::endl;
					if (nodes->uncle())
						std::cout << "\033[31m:" << nodes->uncle()->_key << "\033[0m" << std::endl;
					else
						std::cout << std::endl;
				}
				else
				{
					std::cout << nodes->_key << ":" << nodes->_value; //<< std::endl;
					if (nodes->uncle())
						std::cout << ":" << nodes->uncle()->_key << std::endl;
					else
						std::cout << std::endl;
				}
				print_nodes_utils(nodes->_right, spaces);
			}
			node_type* root_node(void)
			{
				node_type* node = nodes;
				while (node && node->_parent)
					node = node->_parent;
				return node;
			}
		
		public:
			node_type* nodes;
			rb_tree()
			{
				nodes = nullptr;
			}
			~rb_tree()
			{
				// alloc.destroy(nodes);
				// alloc.deallocate(nodes, 1);
			}
			void print_nodes()
			{
				print_nodes_utils(root_node());
			}
			void insert(const node_type& node)
			{
				insert_util(node, &nodes);
			}
			T& find(const Key& value)
			{
				return find_util(value, nodes);
			}
			node_type* find_node(const Key& value)
			{
				return find_node_util(value, nodes);
			}
	};
}

#endif