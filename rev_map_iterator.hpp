#ifndef _rev_tree_iterator_
#define _rev_tree_iterator_
#include "map_iterator.hpp"

namespace ft
{
	template <class Iterator>
	class rev_map_iterator
	{
		public:

		typedef Iterator	iterator_type;
		typedef typename ft::iterator_traits<Iterator>::value_type	value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type	difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer	pointer;
		typedef typename ft::iterator_traits<Iterator>::reference	reference;
		typedef typename ft::iterator_traits<Iterator>::iterator_category  iterator_category;
		iterator_type _iter;
	
		rev_map_iterator(iterator_type other) : _iter(other)
		{
		}
		rev_map_iterator() : _iter()
		{
		}
		template <class T>
		rev_map_iterator(const rev_map_iterator<T>& other) : _iter(other.base())
		{
		}
		~rev_map_iterator()
		{
		}

		rev_map_iterator& operator++()
		{
			_iter--;
			return *this;
		}
		rev_map_iterator operator++(int)
		{
			rev_map_iterator tmp = *this;
			_iter--;
			return tmp;
		}
		rev_map_iterator& operator--()
		{
			_iter++;
			return *this;
		}
		rev_map_iterator operator--(int)
		{
			rev_map_iterator tmp = *this;
			_iter++;
			return tmp;
		}
		value_type& operator[](int index)
		{
			return _iter[index];
		}
		pointer operator->()
		{
			return _iter.operator->();
		}
		const value_type* operator->() const
		{
			return _iter.operator->();
		}
		reference operator*()
		{
			return _iter.operator*();
		}
		const value_type& operator*() const
		{
			return _iter.operator*();
		}
		template <class T>
		rev_map_iterator& operator=(const rev_map_iterator<T>& other)
		{
			_iter = other._iter;
			return *this;
		}
		operator rev_map_iterator<const Iterator>() const
		{
			return (rev_map_iterator<const Iterator>(_iter));
		}

		iterator_type base() const
		{
			return _iter;
		}
	};

		template <class Iterator, class Iterator2>
		bool operator==(const rev_map_iterator<Iterator>& A ,const rev_map_iterator<Iterator2>& B)
		{
			return A.base() == B.base();
		}

		template <class Iterator, class Iterator2>
		bool operator!=(const rev_map_iterator<Iterator>& A ,const rev_map_iterator<Iterator2>& B)
		{
			return !(A.base() == B.base());
		}

		template <class Iterator, class Iterator2>
		bool operator<(const rev_map_iterator<Iterator>& A ,const rev_map_iterator<Iterator2>& B)
		{
			return A.base() > B.base();
		}

		template <class Iterator, class Iterator2>
		bool operator>(const rev_map_iterator<Iterator>& A ,const rev_map_iterator<Iterator2>& B)
		{
			return A.base() < B.base();
		}	
}

#endif