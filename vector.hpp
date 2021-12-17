#ifndef _vector_
#define _vector_
#include <memory>

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:

			//all the alias
			typedef typename Allocator::reference reference;
			typedef typename Allocator::const_reference const_reference;
			// typedef implementation defined iterator;
			// typedef implementation defined const_iterator;
			typedef sizeof(T) defined size_type; //maybe wrong
			// typedef implementation defined difference_type;
			typedef T value_type;
			typedef Allocator allocator_type;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer
			typedef std::reverse_iterator<iterator> reverse_iterator;
			typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

			//constructor and cie
			explicit vector(const Allocator& = Allocator());
			explicit vector(size_type n, const T& value = T(),
			const Allocator& = Allocator());
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const Allocator& = Allocator())
			{
				c = Allocator(std::distance(first, last));
				int i = 0;
				while (first != last)
					c[i++] = *(first++);
			}
			vector(const vector<T,Allocator>& x)
			{
				*this = x;
			}
			~vector()
			{
				delete(*this);
			}
			vector<T,Allocator>& operator=(const vector<T,Allocator>& x)
			{
				//wip
			}
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last);
			{
				erase(first, last);
				insert(first, last, last);
			}
			void assign(size_type n, const T& u)
			{
				erase(first, last);
				insert(first, n, u);
			}
			allocator_type get_allocator() const
			{
				//wip
			}

			//iterator
			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;

			//capacity
			size_type size() const;
			size_type max_size() const;
			void resize(size_type sz, T c = T())
			{
				if (sz > size())
				 insert(end(), sz - size(), c);
				else if (sz < size())
					erase(begin() + sz, end());
				else
				;
			}
			size_type capacity() const
			{
				return sizeof(c / sizeof(*c)); //wip?
			}
			bool empty() const;
			void reserve(size_type n)
			{
				if (n > max_size())
					throw length_error; //?
				if (n <= capacity())
					return;
				T* new_c = Allocate(capacity() + n);
				for (size_type i = 0, iterator iter = begin(); iter != end(); ++i, iter++)
					new_c[i] = *(iter++);
				delete[] c;
				c = new_c;
			}

			//getter
			reference operator[](size_type n);
			const_reference operator[](size_type n) const;
			const_reference at(size_type n) const;
			reference at(size_type n);
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const

			//setter
			void push_back(const T& x);
			void pop_back();
			iterator insert(iterator position, const T& x)
			{
				try
				{
					*position;
				}
				catch (std::exception const& e)
				{
					std::cout << e.what() << std::endl;
					return end();
				}
				if (position == end())
					reserve(capacity() + 1)
				*position = x;	
			}
			void insert(iterator position, size_type n, const T& x)
			{
				try
				{
					*position;
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << std::endl;
				}
				if (std::distance(position, end()) + n > capacity()) //maybe i can get rid of the if by only using resize
				{
					resize(std::distance(position, end()) + n)
				}
				for (unsigned int i = 0, iterator iter = position; i < n; ++i, iter++)
				{

				}
			}
			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last);
			iterator erase(iterator position);
			iterator erase(iterator first, iterator last);
			void swap(vector<T,Al
			void clear();

			//operator
			template <class T, class Allocator>
			bool operator==(const vector<T,Allocator>& x,
			const vector<T,Allocator>& y);
			template <class T, class Allocator>
			bool operator< (const vector<T,Allocator>& x,
			const vector<T,Allocator>& y);
			template <class T, class Allocator>
			bool operator!=(const vector<T,Allocator>& x,
			const vector<T,Allocator>& y);
			template <class T, class Allocator>
			bool operator> (const vector<T,Allocator>& x,
			const vector<T,Allocator>& y);
			template <class T, class Allocator>
			bool operator>=(const vector<T,Allocator>& x,
			const vector<T,Allocator>& y);
			template <class T, class Allocator>
			bool operator<=(const vector<T,Allocator>& x,
			const vector<T,Allocator>& y);

			//spe func
			template <class T, class Allocator>
			void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);

		private:
			T* c;
	};
}

#endif