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

	template <class T, class Key, class Compare = std::less<Key> >
	class map_iterator
	{
		private:

			typedef ft::node<T> node_type;

			void find_next_util(const Key& key, node_type* node, node_type** result) const
			{
				if (!node)
					return;
				if (Compare()(make_pair(key, 0), node->_data) /*node->_data._first > key*/ && (!(*result) || Compare()(node->_data, (*result)->_data) /*node->_data._first < (*result)->_data._first*/))
					(*result) = node;
				find_next_util(key, node->_left, result);
				find_next_util(key, node->_right, result);
			}
			void find_prev_util(const Key& key, node_type* node, node_type** result) const
			{
				if (!node)
					return;
				if (Compare()(node->_data, make_pair(key, 0)) /*node->_data._first < key*/ && (!(*result) || Compare()((*result)->_data, node->_data) /*node->_data._first > (*result)->_data._first*/))
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
				if (!(*result) || node_start->_data > (*result)->_data)
					(*result) = node_start;
				max_node(node_start->_left, result);
				max_node(node_start->_right, result);
			}

		public:

			// typedef typename vector::value_type	value_type;
			// typedef typename vector::difference_type  difference_type;
			// typedef typename vector::value_type*   pointer;
			// typedef typename vector::reference& reference;
			typedef T	value_type;
			typedef T*	pointer;
			typedef T&	reference;
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
				find_next_util(_ptr->_data._first, root_node(_ptr), &result);
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
				find_prev_util(_ptr->_data._first, root_node(_ptr), &result);
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
				return &(_ptr->_data);
			}
			value_type& operator*()
			{
				return _ptr->_data;
			}
			map_iterator& operator=(const map_iterator& other)
			{
				_ptr = other._ptr;
				_nil = other._nil;
				return *this;
			}
			operator map_iterator<const T, Key, Compare>() const
			{
			    return (map_iterator<const T, Key, Compare>(_ptr));
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


	template <class Iterator>
	class rev_map_iterator //maybe unescessary because ghe classic rev_iterator is templated on iterator too
	{
		public:

		typedef Iterator	iterator_type;
		typedef typename ft::iterator_traits<Iterator>::value_type	value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type	difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer	pointer;
		typedef typename ft::iterator_traits<Iterator>::reference	reference;
		typedef typename ft::iterator_traits<Iterator>::iterator_category  iterator_category;
		typedef typename Iterator::key_value Key;
		typedef typename iterator_category::Compare Compare;

		private:

			typedef ft::node<value_type> node_type;

			void find_next_util(const Key& key, node_type* node, node_type** result) const
			{
				if (!node)
					return;
				if (Compare(node_type(make_pair(key, 0)), node->_data) /*node->_data._first > key*/ && (!(*result) || Compare(node->_data, (*result)->_data) /*node->_data._first < (*result)->_data._first*/))
					(*result) = node;
				find_next_util(key, node->_left, result);
				find_next_util(key, node->_right, result);
			}
			void find_prev_util(const Key& key, node_type* node, node_type** result) const
			{
				if (!node)
					return;
				if (Compare(node->_data, node_type(make_pair(key, 0))) /*node->_data._first < key*/ && (!(*result) || Compare()(*(result)->_data, node->_data) /*node->_data._first > (*result)->_data._first*/))
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
			void min_node(node_type* node_start, node_type **result) const
			{
				if (!node_start)
					return;
				if (!(*result) || Compare()(node_start->_data, *(result)->_data) /*node_start->_data < (*result)->_data*/)
					(*result) = node_start;
				min_node(node_start->_left, result);
				min_node(node_start->_right, result);
			}

		public:

			node_type* _ptr;
			node_type* _nil;
		
			rev_map_iterator(node_type* ptr = 0, node_type* nil = 0) : _ptr(ptr), _nil(nil)
			{
			}
			rev_map_iterator(const rev_map_iterator& other) : _ptr(other._ptr), _nil(other._nil)
			{
			}
			~rev_map_iterator()
			{
			}

			rev_map_iterator& operator++()
			{
				node_type* result = 0;
				if (_ptr->_nil)
				{
					min_node(root_node(_ptr->_parent), &result);
					_ptr = result;
					return *this;
				}
				find_prev_util(_ptr->_data._first, root_node(_ptr), &result);
				_ptr = result;
				if (!_ptr)
					_ptr = _nil;
				return *this;
			}
			rev_map_iterator operator++(int)
			{
				rev_map_iterator tmp = *this;
				operator++();
				return tmp;
			}
			rev_map_iterator& operator--()
			{
				if (_ptr->_nil)
					_ptr->_left->_color = true; //let's segfault like the stl
				node_type* result = 0;
				find_next_util(_ptr->_data._first, root_node(_ptr), &result);
				_ptr = result;
				if (!_ptr)
					_ptr = _nil;
				return *this;
			}
			rev_map_iterator operator--(int)
			{
				rev_map_iterator tmp = *this;
				operator--();
				return tmp;
			}
			pointer operator->()
			{
				return &(_ptr->_data);
			}
			value_type& operator*()
			{
				return _ptr->_data;
			}
			rev_map_iterator& operator=(const rev_map_iterator& other)
			{
				_ptr = other._ptr;
				return *this;
			}
			operator rev_map_iterator<const Iterator>() const
			{
			    return (rev_map_iterator<const Iterator>(_ptr));
			}
	};

	//iterator operator

	template <class Iterator, class Iterator2>
	bool operator==(const ft::rev_map_iterator<Iterator>& A, const ft::rev_map_iterator<Iterator2>& B)
	{
		return (A._ptr == B._ptr);
	}

	template <class Iterator, class Iterator2>
	bool operator!=(const ft::rev_map_iterator<Iterator>& A, const ft::rev_map_iterator<Iterator2>& B)
	{
		return !(A._ptr == B._ptr);
	}
}
#endif