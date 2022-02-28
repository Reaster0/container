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

	template <class T>
	class iterator
	{
		public:


			typedef T	value_type;
			typedef T*	pointer;
			typedef T&	reference;
			typedef typename ft::random_access_iterator_tag  iterator_category;
			
			#ifdef __APPLE__
			typedef ptrdiff_t difference_type; //macos
			#endif
			#ifdef __linux__
			typedef ptrdiff_t difference_type; //linux
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

			operator iterator<const T>() const
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

	template <class Iterator>
	class reverse_iterator
	{
		public:
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

			operator reverse_iterator<const Iterator>() const
			{
    			return (reverse_iterator<const Iterator>(_iter));
			}

			iterator_type base() const
			{
				return _iter;
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
