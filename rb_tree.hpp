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
	template <class T, class Key, class Compare, class value_compare>
	class rb_tree
	{
		typedef T value_type;
		//typedef	Key key_type;
		typedef node<T> node_type;
		typedef node<const T> const_node_type;
		typedef std::allocator<ft::node<T> > Allocator;

		private:
			Allocator alloc;
			node_type* nodes;
			node_type* nil;
			value_compare _comp;
			size_t _size;

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
				P->_parent->_left = P->_right;
				if (P->_right)
					P->_right->_parent = P->_parent;
				P->_right = P->_parent;
				node_type* tempParentParent = P->_parent->_parent;
				if (tempParentParent)
					tempParentParent->_right = P;
				P->_parent->_parent = P;
				P->_parent = tempParentParent;
			}
			void RightTriangleRotation(node_type* P)
			{
				P->_parent->_right = P->_left;
				if (P->_left)
					P->_left->_parent = P->_parent;
				P->_left = P->_parent;
				node_type* tempParentParent = P->_parent->_parent;
				if (tempParentParent)
					tempParentParent->_left = P;
				P->_parent->_parent = P;
				P->_parent = tempParentParent;
			}
			void leftRotation(node_type* P)
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
			}
			void rightRotation(node_type* P)
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
					_size++;
					//return ft::pair<ft::iterator<node_type>, bool>(*start_node, true);
				}
				else if (_comp(***start_node, *node) && node != **start_node)
					return insert_util(node, &((*start_node)->_right), *start_node);
				else if (_comp(*node, ***start_node) && node != **start_node)
					return insert_util(node, &((*start_node)->_left), *start_node);
				else
					throw std::string("the keys node's are the same");
					//return ft::pair<ft::iterator<node_type>, bool>(*start_node, false);
			}
			node_type* find_node_util(const T& value, node_type* node) const //maybe not const
			{
				if (!node)
					throw std::string("invalid key");
				if (!_comp(node->_data, value) && !_comp(value, node->_data))
					return node;
				if (_comp(node->_data, value))
					return find_node_util(value, node->_right);
				else
					return find_node_util(value, node->_left);
			}
			void find_next_util(const Key& key, node_type* node, node_type** result) const
			{
				if (!node)
					return;
				if (_comp(T(key), node->_data) && (!(*result) || _comp(node->_data, (*result)->_data)))
					(*result) = node;
				find_next_util(key, node->_left, result);
				find_next_util(key, node->_right, result);
			}
			void find_next_node_util(node_type* node, node_type** result) const
			{
				if (!node)
					return;
				if (_comp((*result)->_data, node->_data)) //_comp(node->_data, (*result)->_data))
					(*result) = node;
				find_next_node_util(node->_left, result);
				find_next_node_util(node->_right, result);
			}
			void find_prev_node_util(node_type* node, node_type** result) const
			{
				if (!node)
					return;
				if (_comp(node->_data, (*result)->_data))
					(*result) = node;
				find_prev_node_util(node->_left, result);
				find_prev_node_util(node->_right, result);
			}
			node_type* rb_tree_min(node_type* node)
			{
				if (!node->_left)
					return node;
				return rb_tree_min(node->_left);
			}
			void find_prev_util(const Key& key, node_type* node, node_type** result) const
			{
				if (!node)
					return;
				if (_comp(node->_data, T(key)) && (!(*result) || _comp((*result)->_data, node->_data)))
					(*result) = node;
				find_prev_util(key, node->_left, result);
				find_prev_util(key, node->_right, result);
			}
			node_type** parent_emplacement(node_type* node)
			{ //get the adress of the emplacement of the node relative to his parent
				if (!node)
					return 0;
				if (!node->_parent)
					return &nodes;
				if (node->_parent->_left == node)
					return &node->_parent->_left;
				else if (node->_parent->_right == node)
					return &node->_parent->_right;
				else
					return 0;
			}
			void delete_node_util(node_type* node)
			{
				alloc.destroy(node);
				alloc.deallocate(node, 1);
				_size--;
			}
			node_type* get_siblings(const node_type *node)
			{
				if (!node || !node->_parent)
					return 0;
				if (node->_parent->_left == node)
					return node->_parent->_right;
				else
					return node->_parent->_left;
			}
			void remove_util4(node_type* x) //if there is an error on remove it's here
			{
				if (x && x->_parent && x->_parent->_left == x)
				{
					node_type *largest = x;
					find_next_node_util(x->_left, &largest);
					*parent_emplacement(x) = largest;
					if (largest != x)
					{
						*parent_emplacement(largest) = 0;
						largest->_parent = x->_parent;
						if (largest != x->_left)
							largest->_left = x->_left;
						else
							largest->_left = 0;
						if (x->_right)
						{
							x->_right->_parent = largest;
							largest->_right = x->_right;
							x->_right->_color = RED; //?
						}
					}
				}
				else if (x && x->_parent && x->_parent->_right == x)
				{
					node_type *largest = x;
					find_next_node_util(x->_right, &largest);
					*parent_emplacement(x) = largest;
					if (largest != x)
					{
						*parent_emplacement(largest) = 0;
						largest->_parent = x->_parent;
						if (largest != x->_right)
							largest->_right = x->_right;
						else
							largest->_right = 0;
						if (x->_left)
						{
							x->_left->_parent = largest;
							largest->_left = x->_left;
							x->_left->_color = RED;
						}
					}
				}
			}
			void remove_util3(node_type* replacement, node_type* x)
			{
				node_type* sibling = get_siblings(x);
				if (x && x->_color == RED) //case 0
				{
					x->_color = BLACK;
					return;
				}
				else if (sibling && sibling->_color == RED) //case 1
				{
					sibling->_color = BLACK;
					x->_parent->_color = RED;
					if(x->_parent->_left == x)
						leftRotation(sibling);
					else
						rightRotation(sibling);
					return remove_util3(replacement, x);
				}
				else if (x && x->_color == BLACK && sibling && sibling->_color == BLACK //case 2
				&& ((sibling->_left && sibling->_right && sibling->_left->_color == BLACK && sibling->_right->_color == BLACK) || (!sibling->_left && !sibling->_right)))
				{
					sibling->_color = RED;
					node_type* tempParent = x->_parent;
					*parent_emplacement(x) = 0;
					delete_node_util(x);
					x = tempParent;
					if (x->_color == RED)
						x->_color = BLACK;
					else
						remove_util3(replacement, x);
				}
				else if (x && x->_color == BLACK && sibling && sibling->_color == BLACK //case 3
				&& ((x->_parent->_left == x && sibling->_left && sibling->_left->_color == RED && sibling->_right && sibling->_right->_color == BLACK)
				|| (x->_parent->_right == x && sibling->_left && sibling->_left->_color == BLACK && sibling->_right && sibling->_right->_color == RED)))
				{
					if (x->_parent->_left == x)
					{
						sibling->_left->_color = BLACK;
						sibling->_color = RED;
						rightRotation(sibling);
						x->_parent->_right = sibling; //not sure of theses, check their values
						sibling->_parent = x->_parent; //
					}
					else
					{
						sibling->_right->_color = BLACK;
						sibling->_color = RED;
						leftRotation(sibling);
						x->_parent->_left = sibling; // not sure of theses, check their values
						sibling->_parent = x->_parent; //
					}
					//return remove_util3(node, replacement, x, 0);
				}
				if (x && x->_color == BLACK && sibling && sibling->_color == BLACK //case 4
				&& ((x->_parent->_left == x && sibling->_right && sibling->_right->_color == RED)
				|| (x->_parent->_right == x && sibling->_left && sibling->_left->_color == RED)))
				{
					sibling->_color = x->_parent->_color;
					x->_parent->_color = BLACK;
					if (x->_parent->_left == x)
					{
						sibling->_right->_color = BLACK;
						leftRotation(sibling);
						remove_util4(x);
					}
					else
					{
						sibling->_left->_color = BLACK;
						rightRotation(sibling);
						remove_util4(x);
					}
					//*parent_emplacement(x) = 0;
					delete_node_util(x);
				}
			}
			void remove_util2(node_type* node, node_type* replacement, node_type* x)
			{
				if (node->_color == RED && (!replacement || replacement->_color == RED))
				{
					if (parent_emplacement(replacement))
						*parent_emplacement(replacement) = x;
					if (x)
						x->_parent = replacement->_parent;
					*parent_emplacement(node) = replacement;
					if (replacement)
					{
						replacement->_parent = node->_parent;
						replacement->_left = node->_left;
						if (replacement->_left)
							replacement->_left->_parent = replacement;
						replacement->_right = node->_right;
						if (replacement->_right)
							replacement->_right->_parent = replacement;
					}
					delete_node_util(node);
				}
				else if (node->_color == BLACK && replacement && replacement->_color == RED)
				{
					if (parent_emplacement(node))
						*parent_emplacement(node) = replacement;
					replacement->_parent = node->_parent;
					replacement->_color = BLACK;
					replacement->_left = node->_left;
					if (replacement->_left)
						replacement->_left->_parent = replacement;
					delete_node_util(node);
					nodes = replacement;
					nodes = root_node();
				}
				else if (node->_color == RED && replacement && replacement->_color == BLACK)
				{
					replacement->_color = RED;
					remove_util3(replacement, x);
				}
				else if (!node->_parent) //case root
				{
					delete_node_util(node);
					nodes = 0;
				}
				else
					remove_util3(replacement, node);
			}
			void remove_util(node_type* node)
			{
				node_type* replacement = 0; //node->_data.first to be fixed
				find_next_util(node->_data.first, node, &replacement);
				if (!node->_left && !node->_right)
					remove_util2(node, replacement, 0);
				else if ((!node->_left && node->_right) || (node->_left && !node->_right))
					remove_util2(node, replacement, replacement);
				else
					remove_util2(node, replacement, replacement->_right);
			}
			
			void rb_transplant(node_type* u, node_type* v)
			{
				if (!u)
					nodes = v;
				else
				{
					*parent_emplacement(u) = v;
					if (v)
						v->_parent = u->_parent;
				}
			}
			void rb_delete_fixup(node_type* x)
			{
				if (x == nodes && x->_color == BLACK && x->_right && x->_right->_color == BLACK)
					x->_right->_color = RED;
				while (x != nodes && x->_color == BLACK)
				{
					if (x == x->_parent->_right)
					{
						node_type* w = x->_parent->_left;
						if (w->_color == RED)
						{
							w->_color = BLACK;
							x->_parent->_color = RED;
							rightRotation(w);//x? //x->_parent
							nodes = root_node();
							if (!x->_parent)
								w = x;
							else
							w = x->_parent->_left;
						}
						if ((!w->_left || w->_left->_color == BLACK) && (!w->_left || w->_right->_color == BLACK))
						{
							w->_color = RED;
							x = x->_parent;
						}
						else
						{
							if (!w->_left || w->_left->_color == BLACK)
							{
								if (w->_right)
									w->_right->_color = BLACK;
								w->_color = RED;
								leftRotation(w->_right); //w
								nodes = root_node();
								w = x->_parent->_left;
							}
							w->_color = x->_parent->_color;
							x->_parent->_color = BLACK;
							if (w->_left)
								w->_left->_color = BLACK;
							rightRotation(x->_parent->_left); //x->_parent
							nodes = root_node();
							if (x->_left && x->_left->_nil) //remove of the three the temp nill leaf
								x->_left = 0;
							else if (x->_right && x->_right->_nil)
								x->_right = 0;
							x = nodes;
						}
					}
					else
					{
						node_type* w = x->_parent->_right;
						if (w->_color == RED)
						{
							w->_color = BLACK;
							x->_parent->_color = RED;
							leftRotation(w); //x? //x->_parent
							nodes = root_node();
							if (!x->_parent)
								w = x;
							else
								w = x->_parent->_right;
						}
						if ((!w->_right || w->_right->_color == BLACK) && (!w->_left || w->_left->_color == BLACK))
						{
							w->_color = RED;
							x = x->_parent;
						}
						else
						{
							if (!w->_right || w->_right->_color == BLACK)
							{
								w->_left->_color = BLACK;
								w->_color = RED;
								rightRotation(w->_left); //w
								nodes = root_node();
								w = x->_parent->_right;
							}
							w->_color = x->_parent->_color;
							x->_parent->_color = BLACK;
							w->_right->_color = BLACK;
							leftRotation(x->_parent->_right); //x->_parent
							nodes = root_node();
							if (x->_left && x->_left->_nil) //remove of the three the temp nill leaf
								x->_left = 0;
							else if (x->_right && x->_right->_nil)
								x->_right = 0;
							x = nodes;
						}
					}
				}
				x->_color = BLACK;
			}
			void rb_delete_util(node_type* z)
			{
				node_type* y = z;
				bool y_color = y->_color;
				node_type* x;
				if (!z->_right)
				{
					x = z->_left;
					if (x)
						rb_transplant(z, x);
					else
					{
						x = alloc.allocate(1);
						alloc.construct(x, node_type(value_type(), BLACK, 0, 0, z->_parent));
						x->_nil = true;
						rb_transplant(z, x);
					}
				}
				else if (!z->_left)
				{
					x = z->_right;
					if (x)
						rb_transplant(z, x);
					else
					{
						x = alloc.allocate(1);
						alloc.construct(x, node_type(value_type(), BLACK, 0, 0, z->_parent));
						x->_nil = true;
						rb_transplant(z, x);
					}
				}
				else
				{
					node_type* y_parent = y->_parent;
					y = rb_tree_min(z->_left);
					y_color = y->_color;
					if (!z->_parent)
						x = y;
					else
						x = y->_left;
					if (!x)
					{
						x = alloc.allocate(1);
						alloc.construct(x, node_type(value_type(), BLACK, 0, 0, y_parent));
						x->_nil = true;
						y->_left = x;
					}
					if (y->_parent == z)
						x->_parent = y;
					if (!z->_parent) //maybe an error
						x->_parent = 0;
					else
					{
						rb_transplant(y, y->_left);
						y->_left = z->_left;
						if (y->_left)
							y->_left->_parent = y;
					}
					rb_transplant(z, y);
					y->_right = z->_right;
					y->_right->_parent = y;
					y->_color = z->_color;
				}
				if (y_color == BLACK)
					rb_delete_fixup(x);
				if (x->_nil)
				{
					if (x->_parent && x->_parent->_left == x) 
						x->_parent->_left = 0;
					else if (x->_parent && x->_parent->_right == x)
						x->_parent->_right = 0;
					alloc.destroy(x);
					alloc.deallocate(x, 1);
				}
				if (!z->_parent && !z->_left && !z->_right)
					nodes = 0;
				delete_node_util(z);
			}
			T& find_util(const Key& key, node_type* node) const
			{
				if (!node)
					throw std::string("invalid key");
				if (node->_data.first == key)
					return node->_data;
				if (_comp(node->_data, T(key)) /*node->_data.first < key*/)
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
			void print_nodes_utils(node_type* nodes, int spaces = 0) const
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
				equal_utils(other_nodes->_right, &(*start_node)->_right, *start_node);
				equal_utils(other_nodes->_left, &(*start_node)->_left, *start_node);
			}
		public:
			rb_tree() : _comp(Compare())
			{
				nodes = 0;
				nil = alloc.allocate(1);
				alloc.construct(nil, node_type());
				nil->_nil = true;
				_size = 0;
			}
			rb_tree(const rb_tree& other) : _comp(other.comp)
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
				_comp = other._comp;
				_size = other._size;
				return *this;
			}
			void print_nodes() const
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
			void remove(node_type* node)
			{
				rb_delete_util(node);
			}
			node_type* find_node(const T& val) const //maybe not const
			{
				try
				{
					return find_node_util(val, nodes);
				}
				catch (std::string &e)
				{
					return end_node();
				}
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
				return _size;
			}
			node_type* root_node(void) const
			{
				node_type* node = nodes;
				while (node && node->_parent)
					node = node->_parent;
				return node;
			}
			node_type* end_node(void) const
			{
				return nil;
			}
			void min_node(node_type* node_start, node_type **result) const
			{
				if (!node_start)
					return;
				if (!(*result) || _comp(node_start->_data, (*result)->_data) /*node_start->_data < (*result)->_data*/)
					(*result) = node_start;
				min_node(node_start->_left, result);
				min_node(node_start->_right, result);
			}
			void max_node(const node_type* node_start, node_type **result) const
			{
				if (!node_start)
					return;
				if (!(*result) || _comp((*result)->_data, node_start->_data) /*node_start->_data > (*result)->_data*/)
					(*result) = node_start;
				max_node(node_start->_left, result);
				max_node(node_start->_right, result);
			}
			bool empty() const
			{
				if (!nodes)
					return true;
				return false;
			}
	};
}

#endif