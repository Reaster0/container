#ifndef _tree_iterator_
#define _tree_iterator_
#include <cstddef>
#include "iterator_traits.hpp"
#include "utils.hpp"
#include "rb_tree.hpp"
#include "map.hpp"

namespace ft
{
	template <class T, class Allocator>
	class rb_tree;

	template <class T>
	class iterator
	{
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
			
			pointer _ptr;
		
			iterator(pointer ptr = 0) : _ptr(ptr)
			{
			}
			iterator(const iterator& other) : _ptr(other._ptr)
			{

			}
			~iterator()
			{
			}

			iterator operator+(size_t nbr) const
			{
				return iterator(_ptr + nbr);
			}

			iterator operator-(size_t nbr) const
			{
				return iterator(_ptr - nbr);
			}
			
			difference_type operator+(const iterator& other) const
			{
				return this->_ptr + other._ptr;
			}
			difference_type operator-(const iterator& other) const
			{
				return this->_ptr - other._ptr;
			}

			iterator& operator++()
			{
				_ptr++;
				return *this;
			}
			iterator operator++(int)
			{
				iterator tmp = *this;
				_ptr++;
				return tmp;
			}
			iterator& operator--()
			{
				_ptr--;
				return *this;
			}
			iterator operator--(int)
			{
				iterator tmp = *this;
				_ptr--;
				return tmp;
			}
			iterator& operator+=(const size_t nbr)
			{
				_ptr += nbr;
				return *this;
			}
			iterator& operator-=(const size_t nbr)
			{
				_ptr -= nbr;
				return *this;
			}
			value_type& operator[](int index)
			{
				return _ptr[index];
			}
			pointer operator->()
			{
				return _ptr;
			}
			value_type& operator*()
			{
				return *_ptr;
			}

			iterator& operator=(const iterator& other)
			{
				_ptr = other._ptr;
				return *this;
			}

			operator iterator<const T>() const //the version with template<T>
			{
			    return (iterator<const T>(_ptr));
			}

	};

	//iterator operator

	template <class T, class U>
	bool operator==(const ft::iterator<T>& A, const ft::iterator<U>& B)
	{
		return (A._ptr == B._ptr);
	}

	template <class T, class U>
	bool operator!=(const ft::iterator<T>& A, const ft::iterator<U>& B)
	{
		return !(A._ptr == B._ptr);
	}

	template <class T, class U>
	bool operator<(const ft::iterator<T>& A, const ft::iterator<U>& B)
	{
		return (A._ptr < B._ptr);
	}

	template <class T, class U>
	bool operator>(const ft::iterator<T>& A, const ft::iterator<U>& B)
	{
		return (A._ptr > B._ptr);
	}

	template <class T, class U>
	bool operator<=(const ft::iterator<T>& A, const ft::iterator<U>& B)
	{
		return !(A._ptr > B._ptr);
	}

	template <class T, class U>
	bool operator>=(const ft::iterator<T>& A, const ft::iterator<U>& B)
	{
		return !(A._ptr < B._ptr);
	}


	template <class T>
	ft::iterator<T> operator+(const size_t nbr, const iterator<T> iter)
	{
		return ft::iterator<T>(iter) + nbr;
	}
	template <class T>
	ft::iterator<T> operator-(const size_t nbr, const iterator<T> iter)
	{
		return ft::iterator<T>(iter) - nbr;
	}

	//func
	template<class InputIterator>
	typename ft::enable_if<!ft::is_integral<InputIterator>::value, size_t>::type distance(InputIterator first, InputIterator last)
	{

		size_t result = 0;
		while (first != last)
		{
			result++;
			++first;
		}
		return result;
	}
}
#endif