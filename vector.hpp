#ifndef _vector_
#define _vector_
#include <memory>
#include <iterator>
#include <iostream>
#include <stdexcept>

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:

			//all the alias
			typedef typename Allocator::reference reference;
			typedef typename Allocator::const_reference const_reference;
			//typedef typename std::vector<T>::iterator iterator;
			//typedef const std::iterator const_iterator;
			typedef size_t size_type; //maybe wrong

			typedef ptrdiff_t difference_type; //macos
			//typedef __gnu_cxx::ptrdiff_t difference_type; //linux

			typedef T value_type;
			typedef Allocator allocator_type;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			//typedef std::reverse_iterator<iterator> reverse_iterator;
			//typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

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
			vector(InputIterator first, InputIterator last, const Allocator& = Allocator())
			{
				Allocator alloc;
				c = alloc.allocate(last - first);
				_capacity = last - first;
				_nbr_elem = _capacity;
				int i = 0;
				for (InputIterator it = first; it != last; ++it, i++)
					alloc.construct(c + i, it);
			}
			vector(const vector<T,Allocator>& x)
			{
				*this = x;
			}
			~vector()
			{
				Allocator alloc;
				for (size_t i = 0; i < _nbr_elem; i++)
				{
					alloc.destroy(c + i);
				}
				alloc.deallocate(c, _capacity);
			}
			vector<T,Allocator>& operator=(const vector<T,Allocator>& x)
			{
				Allocator alloc;
				for (size_t i = 0; i < _nbr_elem; i++)
				{
					alloc.destroy(c + i);
				}
				alloc.deallocate(c, _capacity);
				alloc.allocate(x.nbr_elem());
				for (size_t i = 0; i < _nbr_elem; i++)
				{
					//alloc.construct(c + i, x.); //wip
				}
			}
			//template <class InputIterator>
			//void assign(InputIterator first, InputIterator last)
			//{
				//erase(first, last);
				//insert(first, last, last);
			//}
			//void assign(size_type n, const T& u)
			//{
				//erase(first, last);
			//	insert(first, n, u);
			 //}
			allocator_type get_allocator() const
			{
				return Allocator();
				//wip
			}

			//iterator
			// iterator begin();
			// const_iterator begin() const;
			// iterator end();
			// const_iterator end() const;
			// reverse_iterator rbegin();
			// const_reverse_iterator rbegin() const;
			// reverse_iterator rend();
			// const_reverse_iterator rend() const;

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
				return _capacity; //wip?
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
					throw std::length_error("vector");
				if (n <= capacity())
					return;
				Allocator alloc;
				T* new_c = alloc.allocate(capacity() + n);
				for (size_type i = 0; i < _nbr_elem; i++)
					new_c[i] = c[i];
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
				return c[_nbr_elem];
			}
			const_reference back() const
			{
				return c[_nbr_elem];
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
				alloc.destroy(c + _nbr_elem--);
			}
			// iterator insert(iterator position, const T& x)
			// {
			// 	try
			// 	{
			// 		*position;
			// 	}
			// 	catch (std::exception const& e)
			// 	{
			// 		std::cout << e.what() << std::endl;
			// 		return end();
			// 	}
			// 	if (position == end())
			// 		reserve(capacity() * 2)
			// 	*position = x;
			// 	return position;
			// }
			// void insert(iterator position, size_type n, const T& x)
			// {
			// 	try
			// 	{
			// 		*position;
			// 	}
			// 	catch(const std::exception& e)
			// 	{
			// 		std::cerr << e.what() << std::endl;
			// 		return;
			// 	}
			// 	if (std::distance(position, end()) + n > capacity()) //maybe i can get rid of the if by only using resize
			// 	{
			// 		resize(std::distance(position, end()) + n)
			// 	}
			// 	for (unsigned int i = 0, iterator iter = position; i < n; ++i, iter++)
			// 	{
			// 		*iter = x;
			// 	}
			// }
			// template <class InputIterator>
			// void insert(iterator position, InputIterator first, InputIterator last)
			// {
			// 	try
			// 	{
			// 		*position;
			// 	}
			// 	catch(const std::exception& e)
			// 	{
			// 		std::cerr << e.what() << std::endl;
			// 		return;
			// 	}
			// 	if (std::distance(first, last) + std::distance(position , end()) > capacity()) //maybe i can get rid of the if by only using resize
			// 	{
			// 		resize(std::distance(first, last) + std::distance(position , end()))
			// 	}
			// 	for (iterator iter = first; iter != last; iter++)
			// 	{
			// 		insert(position, *iter);
			// 	}
			// }
			// iterator erase(iterator position)
			// {
			// 	try
			// 	{
			// 		*position;
			// 	}
			// 	catch(const std::exception& e)
			// 	{
			// 		std::cerr << e.what() << std::endl;
			// 		return;
			// 	}
			// 	for (iterator iter = position; iter != end(); iter++)
			// 		iter = iter + 1;
			// 	return position + 1;
			// }
			// iterator erase(iterator first, iterator last)
			// {
			// 	try
			// 	{
			// 		*first;
			// 	}
			// 	catch(const std::exception& e)
			// 	{
			// 		std::cerr << e.what() << std::endl;
			// 		return;
			// 	}
			// 	for (iterator iter = first; iter != last; iter++)
			// 		iter = iter + 1;
			// 	return last;
			// }
			// void swap(vector<T,Allocator>&);
			// void clear();

			//operator
			// template <class T, class Allocator>
			// bool operator==(const vector<T,Allocator>& x,
			// const vector<T,Allocator>& y);
			// template <class T, class Allocator>
			// bool operator< (const vector<T,Allocator>& x,
			// const vector<T,Allocator>& y);
			// template <class T, class Allocator>
			// bool operator!=(const vector<T,Allocator>& x,
			// const vector<T,Allocator>& y);
			// template <class T, class Allocator>
			// bool operator> (const vector<T,Allocator>& x,
			// const vector<T,Allocator>& y);
			// template <class T, class Allocator>
			// bool operator>=(const vector<T,Allocator>& x,
			// const vector<T,Allocator>& y);
			// template <class T, class Allocator>
			// bool operator<=(const vector<T,Allocator>& x,
			// const vector<T,Allocator>& y);

			//spe func
			// template <class T, class Allocator>
			// void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);


			void print_debug(void) const
			{
				std::cout << "---------------------------" << std::endl;
				for (size_type i = 0; i < _nbr_elem; i++)
					std::cout << c[i] << std::endl;
				std::cout << "---------------------------" << std::endl;
			} //only for debug, need to be removed

		private:
			T* c;
			size_type _nbr_elem;
			size_type _capacity;
			
			//memory
			void expand(void)
			{
				T* new_c;
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
					new_c[i] = c[i];
					alloc.destroy(c + i);
				}
				alloc.deallocate(c, old_capacity);
				c = new_c;
			}
	};
}

#endif