#ifndef _stack_
#define _stack_
#include "vector.hpp"

namespace ft
{
	template <class T, class Allocator>
	class vector;

	template <class T, class Container = ft::vector<T, std::allocator<T> > >
	class stack
	{
		protected:
			Container _container;
		public:
			typedef T 	value_type;
			typedef typename Container::reference 	reference;
			typedef typename Container::size_type 	size_type;
			typedef typename Container::const_reference const_reference;
			typedef Container 	container_type;

			explicit stack (const container_type& container = container_type()) : _container(container)
			{
			}
			~stack()
			{
			}
			bool empty() const
			{
				return _container.empty();
			}
			size_type size() const
			{
				return _container.size();
			}
			reference top()
			{
				return _container.back();
			}
			const_reference top() const
			{
				return _container.back();
			}
			void push(const value_type& value)
			{
				_container.push_back(value);
			}
			void pop()
			{
				_container.pop_back();
			}
			template<class T_, class Container_>
			friend bool	operator==(const stack<T_, Container_>&, const stack<T_, Container_>&);

			template<class T_, class Container_>
			friend bool	operator<(const stack<T_, Container_>&, const stack<T_, Container_>&);

			template<class T_, class Container_>
			friend bool	operator>(const stack<T_, Container_>&, const stack<T_, Container_>&);
			
			template<class T_, class Container_>
			friend bool	operator<=(const stack<T_, Container_>&, const stack<T_, Container_>&);

			template<class T_, class Container_>
			friend bool	operator>=(const stack<T_, Container_>&, const stack<T_, Container_>&);
};

	template <class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs._container == rhs._container;
	}

	template <class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs._container < rhs._container;
	}

	template <class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs._container <= rhs._container;
	}

	template <class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs._container > rhs._container;
	}

	template <class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs._container >= rhs._container;
	}
}

#endif