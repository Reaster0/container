#ifndef _reverse_iterator_
#define _reverse_iterator_
#include <cstddef>
#include "vector.hpp"

namespace ft
{
	template <class T, class Allocator >
	class vector;

	template <typename vector>
	class reverse_iterator
	{
		public:

			typedef typename vector::value_type	value_type;
			typedef typename vector::difference_type  difference_type;
			typedef typename vector::value_type*   pointer;
			typedef typename vector::reference& reference;
			typedef typename std::random_access_iterator_tag  iterator_category;
			pointer _ptr;
		
			reverse_iterator(pointer ptr = 0) : _ptr(ptr)
			{
			}
			~reverse_iterator()
			{
			}

			reverse_iterator operator+(size_t nbr)
			{
				return reverse_iterator(_ptr - nbr);
			}

			reverse_iterator operator-(size_t nbr)
			{
				return reverse_iterator(_ptr + nbr);
			}

			reverse_iterator& operator++()
			{
				_ptr--;
				return *this;
			}
			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				_ptr--;
				return tmp;
			}
			reverse_iterator& operator--()
			{
				_ptr++;
				return *this;
			}
			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				_ptr++;
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

			reverse_iterator& operator=(const reverse_iterator& other)
			{
				_ptr = other._ptr;
				return *this;
			}

			bool operator==(const reverse_iterator& other) const
			{
				return (_ptr == other._ptr);
			}

			bool operator!=(const reverse_iterator& other) const
			{
				return !(_ptr == other._ptr);
			}

			bool operator<(const reverse_iterator& other) const
			{
				return (_ptr > other._ptr);
			}

			bool operator>(const reverse_iterator& other) const
			{
				return (_ptr < other._ptr);
			}

			bool operator<=(const reverse_iterator& other) const
			{
				return !(_ptr < other._ptr);
			}
			
			bool operator>=(const reverse_iterator& other) const
			{
				return !(_ptr > other._ptr);
			}

			// operator reverse_iterator<const value_type>() const
			// {
    		// 	return (reverse_iterator<const value_type>(_ptr));
			// }

	};
}
#endif