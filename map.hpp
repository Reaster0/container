#ifndef _map_
#define _map_

#include "rb_tree.hpp"

namespace ft
{
	template<class Key, class T, class Allocator = std::allocator<ft::pair<const Key, T> >, class Compare = std::less<Key> >
	class map
	{
		typedef T mapped_type;
		typedef Key key_type;
		typedef node<const Key, T> node_type;
		typedef Compare key_compare;
		typedef rb_tree<const key_type, mapped_type> tree_type;
		typedef pair<const Key, T> value_type;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference	reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef iterator<node_type> iterator;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef size_t size_type;

		private:
			tree_type _tree;

		public://maybe need to incorporate key_compare in rb_tree
			explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type())
			{
			}
			// map (InputIterator first, InputIterator last,
			// const key_compare& comp = key_compare(),
			// const allocator_type& alloc = allocator_type())
			// {

			// }
			map (const map& x)
			{
				this = x;
			}
			~map()
			{
			}
			ft::pair<iterator, bool> insert(const value_type& val)
			{
				ft::pair<iterator, bool> result;
				try
				{
					_tree.insert(val);
					result._first = iterator(_tree.find_node(val._first));
					result._second = true;	
				}
				catch(const std::string& e)
				{
					std::cerr << e << '\n'; //maybe unusefull
					result._first = iterator(_tree.find_node(val._first));
					result._second = false;
				}
				return result;
			}
			iterator insert(iterator position, const value_type& val)
			{
				iterator result;
				result = position;
				try
				{
					_tree.insert(val);
					result = iterator(_tree.find_node(val._first));	
				}
				catch(const std::string& e)
				{
					std::cerr << e << '\n'; //maybe unusefull
					result = iterator(_tree.find_node(val._first));
				}
				return result;
			}
			template <class InputIterator> //check that is is a bidirectionnal iterator
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type 
			insert(InputIterator first, InputIterator second)
			{
				try
				{
					for (InputIterator i = first; i != second; ++i)
						_tree(insert(*i));
				}
				catch(const std::string& e)
				{
					std::cerr << e << '\n';
				}
			}
			iterator begin()
			{
				return iterator(_tree.root_node());
			}

	};
}

#endif