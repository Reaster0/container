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
			iterator_type _iter;
		
			reverse_iterator(iterator_type other) : _iter(other)
			{
			}
			// reverse_iterator(pointer ptr = 0) : _iter(ptr)
			// {
			// }
			reverse_iterator() : _iter()
			{
			}
			template <class T>
			reverse_iterator(const reverse_iterator<T>& other) : _iter(other.base())
			{
			}
			~reverse_iterator()
			{
			}
			reverse_iterator operator+(size_t nbr) const
			{
				return reverse_iterator(base() - nbr);
			}

			reverse_iterator operator-(size_t nbr) const
			{
				return reverse_iterator(base() + nbr);
			}

			difference_type operator-(const reverse_iterator& other) const
			{
				return other.base() - base();
			}
			difference_type operator+(const reverse_iterator& other) const
			{
				return other.base() + base();
			}

			reverse_iterator& operator++()
			{
				_iter--;
				return *this;
			}
			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				_iter--;
				return tmp;
			}
			reverse_iterator& operator--()
			{
				_iter++;
				return *this;
			}
			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				_iter++;
				return tmp;
			}
			reverse_iterator operator-=(size_t nbr)
			{
				_iter = _iter + nbr;
				return *this;
			}
			reverse_iterator operator+=(size_t nbr)
			{
				_iter = _iter - nbr;
				return *this;
			}
			value_type& operator[](int index)
			{
				return _iter[-index - 1];
			}
			pointer operator->() const
			{
				return _iter._ptr - 1;
			}
			value_type& operator*()
			{
				return *(_iter._ptr - 1);
			}

			template <class T>
			reverse_iterator& operator=(const reverse_iterator<T>& other)
			{
				_iter = other._iter;
				return *this;
			}

			// operator reverse_iterator<const ft::vector<const value_type, std::allocator<value_type> > >() const
			// {
    		// 	return (reverse_iterator<ft::vector<const value_type, std::allocator<value_type> > >(_iter));
			// }

			operator reverse_iterator<const Iterator>() const
			{
    			return (reverse_iterator<const Iterator>(_iter));
			}

			iterator_type base() const
			{
				return _iter;
				//return iterator_type(_iter._ptr - 1);
				//return iterator_type(_iter._ptr + 1);
			}
	};

	template <class Iterator, class Iterator2>
	bool operator==(const reverse_iterator<Iterator>& A ,const reverse_iterator<Iterator2>& B)
	{
		return A.base() == B.base();
	}

	template <class Iterator, class Iterator2>
	bool operator!=(const reverse_iterator<Iterator>& A ,const reverse_iterator<Iterator2>& B)
	{
		return !(A.base() == B.base());
	}

	template <class Iterator, class Iterator2>
	bool operator<(const reverse_iterator<Iterator>& A ,const reverse_iterator<Iterator2>& B)
	{
		return A.base() > B.base();
	}

	template <class Iterator, class Iterator2>
	bool operator>(const reverse_iterator<Iterator>& A ,const reverse_iterator<Iterator2>& B)
	{
		return A.base() < B.base();
	}

	template <class Iterator, class Iterator2>
	bool operator<=(const reverse_iterator<Iterator>& A ,const reverse_iterator<Iterator2>& B)
	{
		return !(A.base() < B.base());
	}
	
	template <class Iterator, class Iterator2>
	bool operator>=(const reverse_iterator<Iterator>& A ,const reverse_iterator<Iterator2>& B)
	{
		return !(A.base() > B.base());
	}

	template <class InputIterator>
	typename ft::enable_if<!ft::is_integral<InputIterator>::value, ft::reverse_iterator<InputIterator> >::type
	operator+(const size_t nbr, const reverse_iterator<InputIterator> iter)
	{
		return (iter + nbr);
	}

	template<class InputIterator>
	typename ft::enable_if<!ft::is_integral<InputIterator>::value, ft::reverse_iterator<InputIterator> >::type
	operator-(const size_t nbr, const reverse_iterator<InputIterator> iter)
	{
		return (iter - nbr);
	}
}
#endif