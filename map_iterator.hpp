#ifndef _tree_iterator_
#define _tree_iterator_
#include <cstddef>
#include "iterator_traits.hpp"
#include "utils.hpp"
#include "rb_tree.hpp"
#include "map.hpp"
#include "const_map_iterator.hpp"

namespace ft
{

	template <class T, class Key, class Compare>
	class map_iterator
	{
		private:

			typedef ft::node<T> node_type;

			void find_next_util(const Key& key, node_type* node, node_type** result) const
			{
				if (!node)
					return;
				if (_comp(key, node->_data.first) && (!(*result) || _comp(node->_data.first, (*result)->_data.first)))
					(*result) = node;
				find_next_util(key, node->_left, result);
				find_next_util(key, node->_right, result);
			}
			void find_prev_util(const Key& key, node_type* node, node_type** result) const
			{
				if (!node)
					return;
				if (_comp(node->_data.first, key) && (!(*result) || _comp((*result)->_data.first, node->_data.first)))
					(*result) = node;
				find_prev_util(key, node->_left, result);
				find_prev_util(key, node->_right, result);
			}
			node_type* root_node(node_type* nodes) const
			{
				node_type* node = nodes;
				while (node && node->_parent)
					node = node->_parent;
				return node;
			}
			void max_node(node_type* node_start, node_type **result) const
			{
				if (!node_start)
					return;
				if (!(*result) || _comp((*result)->_data.first, node_start->_data.first)) //node_start->_data > (*result)->_data)
					(*result) = node_start;
				max_node(node_start->_left, result);
				max_node(node_start->_right, result);
			}

		public:

			typedef T	value_type;
			typedef T*	pointer;
			typedef T&	reference;
			typedef Key key_value;
			typedef typename ft::bidirectional_iterator_tag iterator_category;
			
			#ifdef __APPLE__
			typedef ptrdiff_t difference_type; //macos
			#endif
			#ifdef __linux__
			typedef ptrdiff_t difference_type; //linux
			#endif
			
			node_type* _ptr;
			node_type* _nil;
			Compare _comp;
		
			map_iterator() : _ptr(0), _nil(0), _comp(Compare())
			{
			}
			map_iterator(node_type* ptr, node_type* nil) : _ptr(ptr), _nil(nil), _comp(Compare())
			{
			}
			map_iterator(const map_iterator& other) : _ptr(other._ptr), _nil(other._nil), _comp(other._comp)
			{
			}
			~map_iterator()
			{
			}

			map_iterator& operator++()
			{
				if (_ptr->_nil)
			 		_ptr->_left->_color = true; //let's segfault like the stl
				node_type* result = 0;
				find_next_util(_ptr->_data.first, root_node(_ptr), &result);
				_ptr = result;
				if (!_ptr)
					_ptr = _nil;
				return *this;
			}
			map_iterator operator++(int)
			{
				map_iterator tmp = *this;
				operator++();
				return tmp;
			}
			map_iterator& operator--()
			{
				node_type* result = 0;
				if (_ptr->_nil)
				{
					max_node(root_node(_ptr->_parent), &result);
					_ptr = result;
					return *this;
				}
				find_prev_util(_ptr->_data.first, root_node(_ptr), &result);
				if (!result)
					result->_left->_color = true; //let's segfault like the stl
				_ptr = result;
				if (!_ptr)
					_ptr = _nil;
				return *this;
			}
			map_iterator operator--(int)
			{
				map_iterator tmp = *this;
				operator--();
				return tmp;
			}
			reference operator*()
			{
				return _ptr->_data;
			}
			const value_type &operator*() const
			{
				return _ptr->_data;
			}
			pointer operator->()
			{
				return (&this->operator*());
			}
			const value_type *operator->() const
			{
				return (&this->operator*());
			}
			map_iterator& operator=(const map_iterator& other)
			{
				_ptr = other._ptr;
				_nil = other._nil;
				_comp = other._comp;
				return *this;
			}
			operator const_map_iterator<T, Key, Compare>() const
			{
				return const_map_iterator<T, Key, Compare>(_ptr, _nil);
			}
	};

	//iterator operator

	template <class T, class U, class K, class V, class comp, class comp2>
	bool operator==(const ft::map_iterator<T, K, comp>& A, const ft::map_iterator<U, V, comp2>& B)
	{
		return (A._ptr == B._ptr);
	}

	template <class T, class U, class K, class V, class comp, class comp2>
	bool operator!=(const ft::map_iterator<T, K, comp>& A, const ft::map_iterator<U, V, comp2>& B)
	{
		return !(A._ptr == B._ptr);
	}

	template <class T, class U, class K, class V, class comp, class comp2>
	bool operator==(const ft::map_iterator<T, K, comp>& A, const ft::const_map_iterator<U, V, comp2>& B)
	{
		return (A._ptr == B._ptr);
	}

	template <class T, class U, class K, class V, class comp, class comp2>
	bool operator!=(const ft::map_iterator<T, K, comp>& A, const ft::const_map_iterator<U, V, comp2>& B)
	{
		return !(A._ptr == B._ptr);
	}
}
#endif