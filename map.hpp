#ifndef _map_
#define _map_

#include "rb_tree.hpp"

namespace ft
{
	template<class Key, class T, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		typedef T mapped_type;
		typedef Key key_type;
		typedef node<const Key, T> node_type;
		typedef rb_tree<const key_type, mapped_type, Allocator> tree_type;
		typedef pair<const Key, T> value_type;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference	reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::iterator<value_type> iterator;

		private:
			Allocator alloc;
			tree_type tree;

		public:
			map()
			{

			}
	};
}

#endif