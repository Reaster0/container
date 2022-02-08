#ifndef _map_
#define _map_

#include "rb_tree.hpp"
#include "map_iterator.hpp"

namespace ft
{
	template<class Key, class T, class Allocator = std::allocator<ft::pair<Key, T> >, class Compare = std::less<Key> >
	class map
	{
		typedef ft::pair<const Key, T> value_type;
		typedef rb_tree<value_type, Key> tree_type;
		typedef node<value_type> node_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference	reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef size_t size_type;

		private:
			tree_type _tree;

		public://maybe need to incorporate key_compare in rb_tree

			typedef ft::map_iterator<value_type, Key> iterator;
			typedef ft::map_iterator<const value_type, Key> const_iterator;
			//typedef ft::reverse_iterator<iterator> reverse_iterator;
			//typedef ft::reverse_iterator<const iterator> const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type difference_type;

			class value_compare: public std::binary_function<value_type, value_type, bool>
			{
				protected:
  				Compare comp;
  				value_compare (Compare c) : comp(c) {}
				
				public:
				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				}
			};
			
			
			explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type())
			{
			}
			template<class InputIterator>
			map(InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
			{
				insert(first, last);
			}
			map(const map& x)
			{
				*this = x;
			}
			~map()
			{
			}
			map& operator=(const map& other)
			{
				_tree = other._tree;
				return *this;
			}
			void print()
			{
				_tree.print_nodes();
			}
			ft::pair<iterator, bool> insert(const value_type& val)
			{
				ft::pair<iterator, bool> result;
				try
				{
					_tree.insert(val);
					result._first = iterator(_tree.find_node(val));
					result._second = true;
				}
				catch(const std::string& e)
				{
					//std::cerr << e << '\n'; //maybe unusefull
					result._first = iterator(_tree.find_node(val));
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
					result = iterator(_tree.find_node(val));	
				}
				catch(const std::string& e)
				{
					std::cerr << e << '\n'; //maybe unusefull
					result = iterator(_tree.find_node(val));
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
				node_type* result = 0;
				_tree.min_node(_tree.root_node(), &result);
				if (!result)
					return iterator(_tree.end_node(), _tree.end_node());
				return iterator(result);
			}
			const_iterator begin() const
			{
				node_type* result = 0;
				_tree.min_node(_tree.root_node(), &result);
				if (!result)
					return const_iterator(_tree.end_node(), _tree.end_node());
				return const_iterator(result, _tree.end_node());
			}
			iterator end()
			{
				return iterator(_tree.end_node(), _tree.end_node());
			}
			const_iterator end() const
			{
				return const_iterator(_tree.end_node(), _tree.end_node());
			}
			// reverse_iterator rbegin()
			// {
			// 	return reverse_iterator(_tree.end_node());
			// }
			// const_reverse_iterator rbegin() const
			// {
			// 	return reverse_iterator(_tree.end_node()); 
			// }
			// reverse_iterator rend()
			// {
			// 	return reverse_iterator(_tree.root_node());
			// }
			// const_reverse_iterator rend() const
			// {
			// 	return reverse_iterator(_tree.root_node());
			// }
			void clear()
			{
				_tree = tree_type();
			}
			size_type count(const Key& k) const
			{
				try
				{
					_tree.find_key(k);
					return 1;
				}
				catch(const std::string& e)
				{
					return 0;
				}
			}
			ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const
			{
				return ft::pair<const_iterator, const_iterator>
				(const_iterator(_tree.find_next_key(key)), const_iterator(_tree.find_next_key(key)));
			}
			bool empty() const
			{
				if (!_tree.nodes)
					return true;
				return false;
			}
			iterator find(const Key& key)
			{
				try
				{
					return iterator(_tree.find_node(_tree.find_key(key)));
				}
				catch(const std::string& e)
				{
					return iterator(0); //sould return end()
					//return end();
				}
			}
			const_iterator find(const Key& key) const
			{
				try
				{
					return const_iterator(_tree.find_node(_tree.find_key(key)));
				}
				catch(const std::string& e)
				{
					return const_iterator(0); //sould return end()
					//return end();
				}
			}
			allocator_type get_allocator() const
			{
				return Allocator();
			}
			size_t max_size() const
			{
				return Allocator().max_size();
			}
			size_t size() const
			{
				return _tree.size();
			}
			T& operator[] (const Key& key)
			{
				return (*insert(make_pair(key, T()))._first)._data._second;
			}

			iterator lower_bound (const Key& key)
			{
				return iterator(_tree.find_prev_key(key));
			}
			const_iterator lower_bound (const Key& key) const
			{
				return iterator(_tree.find_prev_key(key));
			}
			iterator upper_bound (const Key& k)
			{
				return iterator(_tree.find_next_key(k));
			}
			const_iterator upper_bound (const Key& k) const
			{
				return iterator(_tree.find_next_key(k));
			}
			key_compare	key_comp() const
			{
				return (key_compare());
			}
			value_compare	value_comp() const
			{
				return (value_compare());
			}
			void swap (map& x)
			{
				ft::map<Key, T, Allocator, Compare> temp(*this);
				*this = x;
				x = temp;
			}
	};

	template <class Key, class T, class Compare, class Alloc>
  	void swap(ft::map<Key,T,Compare,Alloc>& x, ft::map<Key,T,Compare,Alloc>& y)
	  {
		  x.swap(y);
	  }
}

#endif