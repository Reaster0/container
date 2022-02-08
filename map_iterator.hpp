#ifndef _tree_iterator_
#define _tree_iterator_
#include <cstddef>
#include "iterator_traits.hpp"
#include "utils.hpp"
#include "rb_tree.hpp"
#include "map.hpp"

namespace ft
{
	// template <class T, class Key>
	// class rb_tree;

	template <class T, class Key>
	class map_iterator
	{
		private:

			typedef ft::node<T> node_type;

			void find_next_util(const Key& key, node_type* node, node_type** result) const
			{
				if (!node)
					return;
				if (node->_data._first > key && (!(*result) || node->_data._first < (*result)->_data._first))
					(*result) = node;
				find_next_util(key, node->_left, result);
				find_next_util(key, node->_right, result);
			}
			void find_prev_util(const Key& key, node_type* node, node_type** result) const
			{
				if (!node)
					return;
				if (node->_data._first < key && (!(*result) || node->_data._first > (*result)->_data._first))
					(*result) = node;
				find_prev_util(key, node->_left, result);
				find_prev_util(key, node->_right, result);
			}

		public:

			// typedef typename vector::value_type	value_type;
			// typedef typename vector::difference_type  difference_type;
			// typedef typename vector::value_type*   pointer;
			// typedef typename vector::reference& reference;
			typedef T	value_type;
			typedef T*	pointer;
			typedef T&	reference;
			typedef typename ft::bidirectional_iterator_tag iterator_category;
			
			#ifdef __APPLE__
			typedef ptrdiff_t difference_type; //macos
			#endif
			#ifdef __linux__
			typedef __gnu_cxx::ptrdiff_t difference_type; //linux
			#endif
			
			node_type* _ptr;
			node_type* _nil;
		
			map_iterator(node_type* ptr = 0, node_type* nil = 0) : _ptr(ptr), _nil(nil)
			{
			}
			map_iterator(const map_iterator& other) : _ptr(other._ptr), _nil(other._nil)
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
				find_next_util(_ptr->_data._first, _ptr, &result);
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
				if (_ptr->_nil)
					_ptr->_left->_color = true; //let's segfault like the stl
				node_type* result;
				find_prev_util(_ptr->_data._first, _ptr, &result);
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
			pointer operator->()
			{
				return _ptr->_data;
			}
			value_type& operator*()
			{
				return _ptr->_data;
			}
			map_iterator& operator=(const map_iterator& other)
			{
				_ptr = other._ptr;
				return *this;
			}
			operator map_iterator<const T, Key>() const
			{
			    return (map_iterator<const T, Key>(_ptr));
			}

	};

	//iterator operator

	template <class T, class U, class K, class V>
	bool operator==(const ft::map_iterator<T, K>& A, const ft::map_iterator<U, V>& B)
	{
		return (A._ptr == B._ptr);
	}

	template <class T, class U, class K, class V>
	bool operator!=(const ft::map_iterator<T, K>& A, const ft::map_iterator<U, V>& B)
	{
		return !(A._ptr == B._ptr);
	}

	// //func
	// template<class InputIterator>
	// typename ft::enable_if<!ft::is_integral<InputIterator>::value, size_t>::type distance(InputIterator first, InputIterator last)
	// {

	// 	size_t result = 0;
	// 	while (first != last)
	// 	{
	// 		result++;
	// 		++first;
	// 	}
	// 	return result;
	// }
}
#endif