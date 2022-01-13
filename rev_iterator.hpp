#ifndef _reverse_iterator_
#define _reverse_iterator_
#include <cstddef>
#include "vector.hpp"
#include "iterator_traits.hpp"
#include "iterator"

namespace ft
{
	// template <class T, class Allocator >
	// class vector;

	//template <typename vector>
	template <class Iterator>
	class reverse_iterator
	{
		public:

			// typedef typename vector::value_type	value_type;
			// typedef typename vector::difference_type  difference_type;
			// typedef typename vector::value_type*   pointer;
			// typedef typename vector::reference& reference;
			typedef Iterator	iterator_type;
			typedef typename ft::iterator_traits<Iterator>::value_type	value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type	difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer	pointer;
			typedef typename ft::iterator_traits<Iterator>::reference	reference;
			typedef typename ft::iterator_traits<Iterator>::iterator_category  iterator_category;
			pointer _ptr;
		
			reverse_iterator(iterator_type other) : _ptr(other._ptr)
			{
			}
			// reverse_iterator(pointer ptr = 0) : _ptr(ptr)
			// {
			// }
			reverse_iterator() : _ptr()
			{
			}
			template <class T>
			reverse_iterator(const reverse_iterator<T>& other) : _ptr(other._ptr)
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

			template <class T>
			reverse_iterator& operator=(const reverse_iterator<T>& other)
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

			// operator reverse_iterator<const ft::vector<const value_type, std::allocator<value_type> > >() const
			// {
    		// 	return (reverse_iterator<ft::vector<const value_type, std::allocator<value_type> > >(_ptr));
			// }

			operator reverse_iterator<const Iterator>() const
			{
    			return (reverse_iterator<const Iterator>(_ptr));
			}

	};
}
#endif