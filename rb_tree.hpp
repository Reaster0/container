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
			node_type* nodes;

			void RightLineRotation(node_type* P)
			{
				P->_parent->_left = P->_right;
				if (P->_right)
					P->_right->_parent = P->_parent;
				P->_right = P->_parent;
				node_type* tempParentParent = P->_parent->_parent;
				if (tempParentParent && tempParentParent->_left == P->_parent)
					tempParentParent->_left = P;
				else if (tempParentParent && tempParentParent->_right == P->_parent)
					tempParentParent->_right = P;
				P->_parent->_parent = P;
				P->_parent = tempParentParent;
				P->_color = BLACK;
				P->_right->_color = RED;
				//if (P->_left)
					//P->_left->_color = RED; //maybe not usefull
			}
			void LeftLineRotation(node_type* P)
			{
				P->_parent->_right = P->_left;
				if (P->_left)
					P->_left->_parent = P->_parent;
				P->_left = P->_parent;
				node_type* tempParentParent = P->_parent->_parent;
				if (tempParentParent && tempParentParent->_left == P->_parent)
					tempParentParent->_left = P;
				else if (tempParentParent && tempParentParent->_right == P->_parent)
					tempParentParent->_right = P;
				P->_parent->_parent = P;
				P->_parent = tempParentParent;
				P->_color = BLACK;
				//if (P->_right)
					//P->_right->_color = RED; //maybe not usefull
				P->_left->_color = RED;
			}
			void LeftTriangleRotation(node_type* P)
			{
				P->_right = P->_parent;
				P->_parent->_left = 0;
				node_type* tempParentParent = P->_parent->_parent;
				if (tempParentParent)
					tempParentParent->_right = P;
				P->_parent->_parent = P;
				P->_parent = tempParentParent;
			}
			void RightTriangleRotation(node_type* P)
			{
				P->_left = P->_parent;
				P->_parent->_right = 0;
				node_type* tempParentParent = P->_parent->_parent;
				if (tempParentParent)
					tempParentParent->_left = P;
				P->_parent->_parent = P;
				P->_parent = tempParentParent;
			}

			void collor_node(node_type** node)
			{
					//*node = check_pointer;
					if (!(*node)->_parent) //case root
						(*node)->_color = BLACK;
					 	//other cases
						if ((*node)->uncle_color() == RED)
						{
							(*node)->_color = RED;
							(*node)->_parent->_color = BLACK;
							(*node)->_parent->_parent->_color = RED;
							(*node)->uncle()->_color = BLACK;
						}
						else if ((*node)->uncle_color() == BLACK)
						{
							//triangle case
							if ((*node) == (*node)->_parent->_left && (*node)->_parent == (*node)->_parent->_parent->_right && (*node)->_parent->_color == RED) // case triangle right
							{
								node_type* P = *node;
								LeftTriangleRotation(P);
								LeftLineRotation(P);
								//maybe an issue here with many node
							}
							//triangle case rev
							else if ((*node) == (*node)->_parent->_right && (*node)->_parent == (*node)->_parent->_parent->_left && (*node)->_parent->_color == RED) // case triangle left
							{
								node_type* P = *node;
								RightTriangleRotation(P);
								RightLineRotation(P);
								//maybe an issue here with many node
							}
							//line rotation left
							else if ((*node) == (*node)->_parent->_left && (*node)->_parent == (*node)->_parent->_parent->_left && (*node)->_parent->_color == RED)
							{
								node_type* P = *node;
								while (P->_parent->_color == RED)
									P = P->_parent;
								RightLineRotation(P);
								//maybe an issue here with many node
							}
							//line rotation right
							else if ((*node) == (*node)->_parent->_right && (*node)->_parent == (*node)->_parent->_parent->_right && (*node)->_parent->_color == RED)
							{
								node_type* P = *node;
								while (P->_parent->_color == RED)
									P = P->_parent;
								LeftLineRotation(P);
								//maybe an issue here with many node
							}
					}
					else
						(*node)->_color = RED;
					if (root_node()->_color == RED)
						root_node()->_color = BLACK;
			}
			
			node_type* check_collor(node_type* node)
			{
				if (!node)
					return 0;
				if (((node->_parent && ((node->_parent->_color != RED && node->_color != RED) || node->_parent->_color != node->_color))) || !node->_parent)
					return (node_type*)((size_t)check_collor(node->_left) + (size_t)check_collor(node->_right)); //can fail if there is both error but that would be weird
				else
					return node;
			}

			void fix_color(node_type** node)
			{
				int debug = 0;
				if (debug)
				{
					std::cout << "-------------------------------------\n";
					print_nodes();
					std::cout << "-------------------------------------\n";
				}
				collor_node(node); //fait les rotations et la couleur correcte pour la node
				if (debug)
				{
					std::cout << "-------------------------------------\n";
					print_nodes();
					std::cout << "-------------------------------------\n";
				}
				node_type* P = check_collor(root_node()); //donne un pointeur vers la node mal placée
				while (P)
				{
					collor_node(&P);
					P = check_collor(root_node()); 
				}

			}

			void insert_util(const node_type& node, node_type** start_node, node_type* parent = 0)
			{
				if (!*start_node)
				{
					*start_node = alloc.allocate(1);
					alloc.construct(*start_node, node);
					(*start_node)->_parent = parent;
					fix_color(start_node);
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
			void free_nodes(node_type* node)
			{
				if (!node)
					return;
				free_nodes(node->_left);
				free_nodes(node->_right);
				alloc.destroy(node);
				alloc.deallocate(node, 1);
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
		public:
			rb_tree()
			{
				nodes = 0;
			}
			~rb_tree()
			{
				free_nodes(root_node());
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
			node_type* root_node(void)
			{
				node_type* node = nodes;
				while (node && node->_parent)
					node = node->_parent;
				return node;
			}
			node_type* right(node_type* node)
			{
				if (!node || !node->_right)
					return 0;
				return node->_right;
			}
			node_type* left(node_type* node)
			{
				if (!node || !node->_left)
					return 0;
				return node->_left;
			}
	};
}

#endif