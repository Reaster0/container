#ifndef _vector_
#define _vector_
#include <memory>
#include <iterator>
#include <iostream>
#include <stdexcept>
#include "iterator.hpp"
#include "utils.hpp"

namespace ft
{
	//template <typename vector>
	template <class T>
	class iterator;

	template <class Iterator>
	class reverse_iterator;

	template<class InputIterator>
	typename ft::enable_if<!ft::is_integral<InputIterator>::value, size_t>::type distance(InputIterator first, InputIterator last);

	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef typename Allocator::reference reference;
			typedef typename Allocator::const_reference const_reference;
			typedef ft::iterator<T>	iterator;
			typedef ft::iterator<const T> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef size_t size_type;

			#ifdef __APPLE__
			typedef ptrdiff_t difference_type; //macos
			#endif
			#ifdef __linux__
			typedef ptrdiff_t difference_type; //linux
			#endif

			typedef T value_type;
			typedef Allocator allocator_type;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;

			//constructor and cie
			explicit vector(const Allocator& = Allocator())
			{
				Allocator alloc;
				c = alloc.allocate(0);
				_capacity = 0;
				_nbr_elem = 0;
			}
			explicit vector(size_type n, const T& value = T(), const Allocator& = Allocator())
			{
				Allocator alloc;
				c = alloc.allocate(n);
				_capacity = n;
				_nbr_elem = n;
				for (size_type i = 0; i < n; ++i)
					alloc.construct(c + i, value);
			}
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const Allocator& = Allocator(), typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = NULL)
			{
				Allocator alloc;
				c = alloc.allocate(ft::distance(first, last));
				_capacity = ft::distance(first, last);
				_nbr_elem = _capacity;
				int i = 0;
				for (InputIterator it = first; it != last; ++it, i++)
					alloc.construct(c + i, *it);
			}
			vector(const vector<T,Allocator>& x)
			{
				Allocator alloc;
				c = alloc.allocate(0);
				_capacity = 0;
				_nbr_elem = 0;
				*this = x;
			}
			~vector()
			{
				Allocator alloc;
				for (size_t i = 0; i < _nbr_elem; i++)
					alloc.destroy(c + i);
				alloc.deallocate(c, _capacity);
			}
			vector<T,Allocator>& operator=(const vector<T,Allocator>& x)
			{
				Allocator alloc;
				for (size_t i = 0; i < _nbr_elem; i++)
					alloc.destroy(c + i);
				alloc.deallocate(c, _capacity);
				c = alloc.allocate(x._capacity);
				for (size_t i = 0; i < x.size(); i++)
					alloc.construct(c + i, x[i]);
				_capacity = x.capacity();
				_nbr_elem = x.size();
				return *this;
			}
			template <class InputIterator>
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type assign(InputIterator first, InputIterator last)
			{
				Allocator alloc;
				for (size_t i = 0; i < _nbr_elem; i++)
					alloc.destroy(c + i);
				alloc.deallocate(c, _capacity);
				c = alloc.allocate(ft::distance(first, last));
				size_t i = 0;
				for (InputIterator it = first; it != last; ++it, ++i)
					alloc.construct(c + i, *it);
				_capacity = ft::distance(first, last);
				_nbr_elem = _capacity;
			}
			void assign(size_type n, const value_type& val)
			{
				Allocator alloc;
				for (size_t i = 0; i < _nbr_elem; i++)
					alloc.destroy(c + i);
				alloc.deallocate(c, _capacity);
				c = alloc.allocate(n);
				_capacity = n;
				_nbr_elem = n;
				for (size_t i = 0; i < n; i++)
					alloc.construct(c + i, val);
			}
			allocator_type get_allocator() const
			{
				return Allocator();
			}

			//iterator
			iterator begin()
			{
				return iterator(c);
			}
			const_iterator begin() const
			{
				return iterator(c);
			}
			iterator end()
			{
				return iterator(c + _nbr_elem);
			}
			const_iterator end() const
			{
				return iterator(c + _nbr_elem);
			}
			reverse_iterator rbegin()
			{
				return reverse_iterator(c + _nbr_elem);
			}
			const_reverse_iterator rbegin() const
			{
				return reverse_iterator(c + _nbr_elem);
			}
			reverse_iterator rend()
			{
				return reverse_iterator(c);
			}
			const_reverse_iterator rend() const
			{
				return reverse_iterator(c);
			}

			// //capacity
			size_type size() const
			{
				return _nbr_elem;
			}
			size_type max_size() const
			{
				return Allocator().max_size();
			}
			void resize(size_type n, value_type val = value_type())
			{
				if (n > _nbr_elem)
				 	for (size_type i = _nbr_elem; i < n; i++)
						 push_back(val);
				else if (n < _nbr_elem)
				 	for (size_type i = _nbr_elem; i > n; i--)
						 pop_back();
				_capacity = n;
			}

			size_type capacity() const
			{
				return _capacity;
			}
			bool empty() const
			{
				if (!_nbr_elem)
					return true;
				return false;
			}
			void reserve(size_type n)
			{
				if (n > max_size())
					throw std::length_error("vector::reserve");
				if (n <= capacity())
					return;
				Allocator alloc;
				T* new_c = alloc.allocate(capacity() + n);
				for (size_type i = 0; i < _nbr_elem; i++)
					alloc.construct(new_c + i, c[i]);
				for (size_t i = 0; i < _nbr_elem; i++)
					alloc.destroy(c + i);
				alloc.deallocate(c, _capacity);
				c = new_c;
				_capacity = n;
			}

			//getter
			reference operator[](size_type n)
			{
				return c[n];
			}
			const_reference operator[](size_type n) const
			{
				return c[n];
			}
			const_reference at(size_type n) const
			{
				if (n >= _nbr_elem)
					throw (std::out_of_range("vector index out of range"));
				return c[n];
			}
			reference at(size_type n)
			{
				if (n >= _nbr_elem)
					throw (std::out_of_range("vector index out of range"));
				return c[n];
			}
			reference front()
			{
				return *c;
			}
			const_reference front() const
			{
				return *c;
			}
			reference back()
			{
				return c[_nbr_elem - 1];
			}
			const_reference back() const
			{
				return c[_nbr_elem - 1];
			}

			//setter
			void push_back(const T& x)
			{
				Allocator alloc;
				if (_nbr_elem == capacity())
					expand();
				alloc.construct(c + _nbr_elem++, x);
			}
			void pop_back()
			{
				Allocator alloc;
				alloc.destroy(c + --_nbr_elem);
			}
			iterator insert(iterator position, const value_type& x)
			{
				Allocator alloc;
				if (!(_capacity - _nbr_elem))
				{
					size_t index = ft::distance(begin(), position);
					reserve(capacity() + 1);
					position = begin() + index;
				}
				for (iterator it = end(); it > position; --it)
				{
					alloc.construct(it._ptr, *(it - 1));
					alloc.destroy((it - 1)._ptr);
				}
				alloc.construct(position._ptr, x);
				_nbr_elem++;
				return position;
			}
			void insert(iterator position, size_type n, const value_type& x)
			{
				Allocator alloc;
				iterator end_temp = end();
				size_t index = ft::distance(begin(), position);
				if ((_capacity - _nbr_elem) < n)
				{
					reserve(capacity() + n);
					position = begin() + index;
				}
				for (iterator it = end() + (n - 1); it > position; --it)
				{
					if (it < end())
						alloc.destroy(it._ptr);
					alloc.construct(it._ptr, *(it - n));
					if (it - n == begin())
						break;
				}
				for (size_t i = 0; i < n; ++i)
				{
					if (position + i < end())
						alloc.destroy((position + i)._ptr);
					alloc.construct((position + i)._ptr, x);
				}
				_nbr_elem += n;
			}
			template <class InputIterator>
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type insert(iterator position, InputIterator first, InputIterator last)
			{
				Allocator alloc;
				size_t len = ft::distance(first, last);
				if ((_capacity - _nbr_elem) < len)
				{
					size_t index = ft::distance(begin(), position);
					reserve(capacity() + len);
					position = begin() + index;
				}
				for (iterator it = end() + (len - 1); it - (len - 1) > position; --it)
				{
					if (it < end())
						alloc.destroy(it._ptr);
					alloc.construct(it._ptr, *(it - len));
					if (it - len == begin())
						break;
				}
				for (size_t i = 0; i < len; ++i)
				{
					if (position + i < end())
						alloc.destroy((position + i)._ptr);
					alloc.construct((position + i)._ptr, *(first++));
				}
				_nbr_elem += len;
			}
			iterator erase(iterator position)
			{
				Allocator alloc;
				if (position == end())
				{
					alloc.destroy((position._ptr));
					_nbr_elem--;
					return end();
				}
				value_type* new_c = alloc.allocate(ft::distance(begin(), end()) - 1);
				size_t index = ft::distance(begin(), position);
				size_t i = 0;
				for (iterator iter = begin(); iter != end(); iter++)
				{
					if (iter != position)
						alloc.construct(new_c + i++, *iter);
					alloc.destroy(iter._ptr);
				}
				alloc.deallocate(c, _capacity);
				c = new_c;
				position = begin() + index;
				_nbr_elem--;
				_capacity = _nbr_elem;
				return position;
			}
			iterator erase(iterator first, iterator last)
			{
				Allocator alloc;
				size_t len = ft::distance(first, last);
				if (first == end())
				{
					for (iterator iter = first; iter != last; iter++)
						alloc.destroy((iter._ptr));
					_nbr_elem -= len;
					return end();
				}
				value_type* new_c = alloc.allocate(ft::distance(begin(), end()) - len);
				size_t index_start = ft::distance(begin(), first);
				size_t i = 0;
				for (iterator iter = begin(); iter != end(); ++iter)
				{
					if (iter < first || iter >= last)
						alloc.construct(new_c + i++, *iter);
					alloc.destroy(iter._ptr);
				}
				alloc.deallocate(c, _capacity);
				c = new_c;
				first = begin() + index_start;
				_nbr_elem -= len;
				_capacity = _nbr_elem;
				return first;
			}
			void swap(vector& x)
			{
				std::swap(this->c, x.c);
				std::swap(this->_capacity, x._capacity);
				std::swap(this->_nbr_elem, x._nbr_elem);
			}
			void clear()
			{
				Allocator alloc;
				for (size_type i = 0; i < _nbr_elem; ++i)
					alloc.destroy(c + i);
				_nbr_elem = 0;
			}

		private:
			T* c;
			size_type _nbr_elem;
			size_type _capacity;
			
			//memory
			void expand(void)
			{
				value_type* new_c;
				Allocator alloc;
				size_type old_capacity = _capacity;
				if (_capacity)
				{				
					new_c = alloc.allocate(capacity() * 2);
					_capacity *= 2;
				}
				else
				{
					new_c = alloc.allocate(1);
					_capacity = 1;
				}
				for (size_type i = 0; i < _nbr_elem; i++)
				{
					alloc.construct(new_c + i, c[i]);
					alloc.destroy(c + i);
				}
				alloc.deallocate(c, old_capacity);
				c = new_c;
			}
	};
	//operator vector
	template <class T, class Allocator>
	bool operator==(const ft::vector<T,Allocator>& x, const ft::vector<T,Allocator>& y)
	{
		if (x.size() != y.size())
			return false;
		return ft::equal(x.begin(), x.end(), y.begin(), y.end());
	}
	template <class T, class Allocator>
	bool operator<(const ft::vector<T,Allocator>& x, const ft::vector<T,Allocator>& y)
	{
		return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}
	template <class T, class Allocator>
	bool operator!=(const ft::vector<T,Allocator>& x, const ft::vector<T,Allocator>& y)
	{
		return !(x == y);
	}
	template <class T, class Allocator>
	bool operator>(const ft::vector<T,Allocator>& x, const ft::vector<T,Allocator>& y)
	{
		return (y < x);
	}
	template <class T, class Allocator>
	bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
	{
		return !(x < y);
	}
	template <class T, class Allocator>
	bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
	{
		return !(x > y);
	}

	//spe func
	template <class T, class Allocator>
	void swap(ft::vector<T,Allocator>& x, ft::vector<T,Allocator>& y)
	{
		x.swap(y);
	}
}

#endif