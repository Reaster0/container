#ifndef _const_tree_iterator_
#define _const_tree_iterator_
#include <cstddef>
#include "iterator_traits.hpp"
#include "map_iterator.hpp"
#include "utils.hpp"
#include "rb_tree.hpp"
#include "map.hpp"

namespace ft
{
	template <class T, class Key, class Compare, class Value_compare >
	class map_iterator;
	template <class T, class Key, class Compare, class Value_compare >
	class const_map_iterator
	{
		private:
			typedef ft::node<T> node_type;

			void find_next_util(const Key& key, const node_type* node, node_type** result) const
			{
				if (!node)
					return;
				if (_comp(T(key), node->_data) && (!(*result) || _comp(node->_data, (*result)->_data)))
					(*result) = const_cast<node_type*>(node);
				find_next_util(key, node->_left, result);
				find_next_util(key, node->_right, result);
			}
			void find_prev_util(const Key& key, const node_type* node, node_type** result) const
			{
				if (!node)
					return;
				if (_comp(node->_data, T(key)) && (!(*result) || _comp((*result)->_data, node->_data)))
					(*result) = const_cast<node_type*>(node);
				find_prev_util(key, node->_left, result);
				find_prev_util(key, node->_right, result);
			}
			const node_type* root_node(const node_type* nodes) const
			{
				const node_type* node = nodes;
				while (node && node->_parent)
					node = node->_parent;
				return node;
			}
			void max_node(const node_type* node_start, node_type **result) const
			{
				if (!node_start)
					return;
				if (!(*result) || _comp((*result)->_data, node_start->_data)) //node_start->_data > (*result)->_data)
					(*result) = const_cast<node_type*>(node_start);
				max_node(node_start->_left, result);
				max_node(node_start->_right, result);
			}

		public:

			typedef T	value_type;
			typedef const T*	pointer;
			typedef const T&	reference;
			typedef Key key_value;
			typedef typename ft::bidirectional_iterator_tag iterator_category;
			
			#ifdef __APPLE__
			typedef ptrdiff_t difference_type; //macos
			#endif
			#ifdef __linux__
			typedef __gnu_cxx::ptrdiff_t difference_type; //linux
			#endif
			
			node_type* _ptr;
			node_type* _nil;
			Value_compare _comp;
		
			const_map_iterator() : _ptr(0), _nil(0), _comp(Compare())
			{
			}
			const_map_iterator(node_type* ptr, node_type* nil) : _ptr(ptr), _nil(nil), _comp(Compare())
			{
			}
			const_map_iterator(const const_map_iterator& other) : _ptr(other._ptr), _nil(other._nil), _comp(other._comp)
			{
			}
			~const_map_iterator()
			{
			}
			const_map_iterator& operator++()
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
			const_map_iterator operator++(int)
			{
				const_map_iterator tmp = *this;
				operator++();
				return tmp;
			}
			const_map_iterator& operator--()
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
			const_map_iterator operator--(int)
			{
				const_map_iterator tmp = *this;
				operator--();
				return tmp;
			}
			const value_type &operator*() const
			{
				return _ptr->_data;
			}
			const value_type *operator->() const
			{
				return &this->operator*();
			}
			const_map_iterator& operator=(const const_map_iterator& other)
			{
				_ptr = other._ptr;
				_nil = other._nil;
				_comp = other._comp;
				return *this;
			}
			operator const_map_iterator<const T, const Key, Compare, Value_compare>() const
			{
			    return (const_map_iterator<const T, const Key, Compare, Value_compare>(_ptr));
			} //maybe osef

	};

	//iterator operator

	template <class T, class U, class K, class V, class comp, class comp2, class comp3, class comp4>
	bool operator==(const ft::const_map_iterator<T, K, comp, comp3>& A, const ft::const_map_iterator<U, V, comp2, comp4>& B)
	{
		return (A._ptr == B._ptr);
	}

	template <class T, class U, class K, class V, class comp, class comp2, class comp3, class comp4>
	bool operator!=(const ft::const_map_iterator<T, K, comp, comp3>& A, const ft::const_map_iterator<U, V, comp2, comp4>& B)
	{
		return !(A._ptr == B._ptr);
	}

	template <class T, class U, class K, class V, class comp, class comp2, class comp3, class comp4>
	bool operator==(const ft::const_map_iterator<T, K, comp, comp3>& A, const ft::map_iterator<U, V, comp2, comp4>& B)
	{
		return (A._ptr == B._ptr);
	}

	template <class T, class U, class K, class V, class comp, class comp2, class comp3, class comp4>
	bool operator!=(const ft::const_map_iterator<T, K, comp, comp3>& A, const ft::map_iterator<U, V, comp2, comp4>& B)
	{
		return !(A._ptr == B._ptr);
	}
}
#endif