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
	template <class T, class Key, class Compare>
	class rb_tree
	{
		typedef T value_type;
		//typedef	Key key_type;
		typedef node<T> node_type;
		typedef std::allocator<ft::node<T> > Allocator;

		private:
			Allocator alloc;
			node_type* nodes;
			node_type* nil; // need to add support for nil

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
				collor_node(node); //fait les rotations et la couleur correcte pour la node
				node_type* P = check_collor(root_node()); //donne un pointeur vers la node mal placée
				while (P)
				{
					collor_node(&P);
					P = check_collor(root_node()); 
				}
				nodes = root_node();
				nil->_parent = nodes;
			}

			void insert_util(node_type node, node_type** start_node, node_type* parent = 0)
			{
				if (!*start_node)
				{
					*start_node = alloc.allocate(1);
					alloc.construct(*start_node, node);
					(*start_node)->_parent = parent;
					fix_color(start_node);
					//return ft::pair<ft::iterator<node_type>, bool>(*start_node, true);
				}
				else if (node > **start_node && node != **start_node)
					return insert_util(node, &((*start_node)->_right), *start_node);
				else if (node < **start_node && node != **start_node)
					return insert_util(node, &((*start_node)->_left), *start_node);
				else
					throw std::string("the keys node's are the same");
					//return ft::pair<ft::iterator<node_type>, bool>(*start_node, false);
			}
			node_type* find_node_util(const T& value, node_type* node) const //maybe not const
			{
				if (!node)
					throw std::string("invalid key");
				if (node->_data == value || (node->_data._first && node->_data._first == value._first))
					return node;
				if (Compare()(node->_data, value))
					return find_node_util(value, node->_right);
				else
					return find_node_util(value, node->_left);
			}
			void find_next_util(const Key& key, node_type* node, node_type** result) const
			{
				if (!node)
					return;
				//maybe an issue here with >
				if (node->_data._first > key && (!(*result) || Compare()(node->_data, (*result)->_data))) //node->_data._first < (*result)->_data._first))
					(*result) = node;
				find_next_util(key, node->_left, result);
				find_next_util(key, node->_right, result);
			}
			void find_prev_util(const Key& key, node_type* node, node_type** result) const
			{
				if (!node)
					return;
				if (Compare()(node->_data, node_type(make_pair(key, 0)) /*node->_data._first < key && (!(*result)*/ || node->_data._first > (*result)->_data._first))
					(*result) = node;
				find_prev_util(key, node->_left, result);
				find_prev_util(key, node->_right, result);
			}
			size_t size_util(node_type* node) const
			{
				if (!node)
					return 1;
				return find_next_util(node->_left) + find_next_util(node->_right);
			}
			T& find_util(const Key& key, node_type* node) const
			{
				if (!node)
					throw std::string("invalid key");
				if (node->_data._first == key)
					return node->_data;
				if (Compare()(node->_data, node_type(make_pair(key, 0))) /*node->_data._first < key*/)
					return find_util(key, node->_right);
				else
					return find_util(key, node->_left);
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
					std::cout << "\033[31m" << nodes->_data << "\033[0m"; //<< std::endl;
					std::cout << std::endl;
				}
				else
				{
					std::cout << nodes->_data; //<< std::endl;
					std::cout << std::endl;
				}
				print_nodes_utils(nodes->_right, spaces);
			}
			void equal_utils(const node_type* other_nodes, node_type** start_node, node_type *parent = 0)
			{
				if (!other_nodes)
					return;
				*start_node = alloc.allocate(1);
				alloc.construct(*start_node, node_type(other_nodes->_data, other_nodes->_color, 0, 0, parent));
				//insert_util(node_type(other_nodes->_data), &nodes);
				equal_utils(other_nodes->_right, &(*start_node)->_right, *start_node);
				equal_utils(other_nodes->_left, &(*start_node)->_left, *start_node);
			}
		public:
			
			typedef ft::bidirectional_iterator_tag	iterator_category;
			
			rb_tree()
			{
				nodes = 0;
				nil = alloc.allocate(1);
				alloc.construct(nil, node_type(0));
				nil->_nil = true;
			}
			rb_tree(const rb_tree& other)
			{
				*this = other;
			}
			~rb_tree()
			{
				free_nodes(nodes);
				alloc.destroy(nil);
				alloc.deallocate(nil, 1);
			}
			rb_tree& operator=(const rb_tree& other)
			{
				free_nodes(nodes);
				nodes = 0;
				equal_utils(other.nodes, &nodes);
				return *this;
			}
			void print_nodes()
			{
				print_nodes_utils(root_node());
			}
			void insert(const node_type& node)
			{
				insert_util(node, &nodes);
			}
			void insert(T& val)
			{
				return insert_util(node_type(val), &nodes);
			}
			node_type* find_node(const T& val) //maybe not const
			{
				return find_node_util(val, nodes);
			}
			T& find_key(const Key& key) const
			{
				return find_util(key, nodes);
			}
			node_type* find_next_key(const Key& key) const
			{
				node_type* result = 0;
				find_next_util(key, nodes, &result);
				return result;
			}
			node_type* find_prev_key(const Key& key) const
			{
				node_type* result = 0;
				find_prev_util(key, nodes, &result);
				return result;
			}
			size_t size() const
			{
				return size_util(nodes);
			}
			node_type* root_node(void) const
			{
				node_type* node = nodes;
				while (node && node->_parent)
					node = node->_parent;
				return node;
			}
			node_type* end_node(void)
			{
				return nil;
			}
			void min_node(node_type* node_start, node_type **result) const
			{
				if (!node_start)
					return;
				if (!(*result) || Compare()(node_start->_data, (*result)->_data) /*node_start->_data < (*result)->_data*/)
					(*result) = node_start;
				min_node(node_start->_left, result);
				min_node(node_start->_right, result);
			}
			void max_node(const node_type* node_start, node_type **result) const
			{
				if (!node_start)
					return;
				if (!(*result) || Compare()((*result)->_data, node_start->_data) /*node_start->_data > (*result)->_data*/)
					(*result) = node_start;
				max_node(node_start->_left, result);
				max_node(node_start->_right, result);
			}
	};
}

#endif