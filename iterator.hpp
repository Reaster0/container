#ifndef _iterator_
#define _iterator_
#include <cstddef>
#include "vector.hpp"

namespace ft
{
	template <class T, class Allocator >
	class vector;

	template <typename vector>
	class iterator
	{
		public:

			typedef typename vector::value_type	value_type;
			typedef typename vector::difference_type  difference_type;
			typedef typename vector::value_type*   pointer;
			typedef typename vector::reference& reference;
			typedef typename std::random_access_iterator_tag  iterator_category;
		
			iterator(pointer ptr = 0) : _ptr(ptr)
			{
			}
			~iterator()
			{
			}

			iterator& operator++()
			{
				_ptr++;
				return *this;
			}
			iterator& operator++(int)
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
			iterator& operator--(int)
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

			bool operator==(const iterator& other) const
			{
				return _ptr == other._ptr;
			}

			bool operator!=(const iterator& other) const
			{
				return !(*this == other);
			}

			void test(void) const
			{
				std::cout << "this is a test" << std::endl;
			}
			pointer test2(void)
			{
				return _ptr;
			}
		private:

			pointer _ptr;
	};
}
#endif