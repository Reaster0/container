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

		public:
			rb_tree()
			{
				nodes = alloc.allocate(1);
				alloc.construct(nodes, node<int, std::string>(42 ,"lol mdr", RED));
			}
			~rb_tree()
			{
				// alloc.destroy(nodes);
				// alloc.deallocate(nodes, 1);
			}
		
		private:
			node<Key, T>* nodes;
			Allocator alloc;
	};

}

#endif