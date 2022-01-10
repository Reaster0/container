#ifndef _iterator_
#define _iterator_
#include <cstddef>
#include "vector.hpp"
#include "iterator_traits.hpp"
#include "utils.hpp"

namespace ft
{
	template <class T, class Allocator >
	class vector;

	//template <typename vector>
	template <class T>
	class iterator
	{
		public:

			// typedef typename vector::value_type	value_type;
			// typedef typename vector::difference_type  difference_type;
			// typedef typename vector::value_type*   pointer;
			// typedef typename vector::reference& reference;
			typedef T	value_type;
			typedef ptrdiff_t	difference_type;
			typedef T*	pointer;
			typedef T&	reference;
			typedef typename ft::random_access_iterator_tag  iterator_category;
			pointer _ptr;
		
			iterator(pointer ptr = 0) : _ptr(ptr)
			{
			}
			~iterator()
			{
			}

			iterator operator+(size_t nbr)
			{
				return iterator(_ptr + nbr);
			}

			iterator operator-(size_t nbr)
			{
				return iterator(_ptr - nbr);
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

			bool operator==(const iterator& other) const
			{
				return (_ptr == other._ptr);
			}

			bool operator!=(const iterator& other) const
			{
				return !(_ptr == other._ptr);
			}

			bool operator<(const iterator& other) const
			{
				return (_ptr < other._ptr);
			}

			bool operator>(const iterator& other) const
			{
				return (_ptr > other._ptr);
			}

			bool operator<=(const iterator& other) const
			{
				return !(_ptr > other._ptr);
			}
			
			bool operator>=(const iterator& other) const
			{
				return !(_ptr < other._ptr);
			}

			// operator iterator<const ft::vector<const value_type, std::allocator<value_type> > >() const
			// {
    		// 	return (iterator<ft::vector<const value_type, std::allocator<value_type> > >(_ptr));
			// }

			operator iterator<const T>() const //the version with template<T>
			{
			    return (iterator<const T>(_ptr));
			}

	};

	//func
	template<class InputIterator>
	//size_t
	typename ft::enable_if<!ft::is_integral<InputIterator>::value, size_t>::type distance(InputIterator first, InputIterator last) // need to add a enable_if
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