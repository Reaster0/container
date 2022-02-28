#ifndef _map_
#define _map_

#include "rb_tree.hpp"
#include "map_iterator.hpp"
#include "rev_map_iterator.hpp"
#include "const_map_iterator.hpp"
#include "iterator.hpp"

namespace ft
{
	template <class T, class Key, class Compare>
	class map_iterator;

	template<class InputIterator>
	typename ft::enable_if<!ft::is_integral<InputIterator>::value, size_t>::type distance(InputIterator first, InputIterator last);

	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<Key, T> > >
	class map
	{
		public:
			typedef ft::pair<const Key, T> value_type;
			class value_compare: public std::binary_function<value_type, value_type, bool>
			{
				protected:

					Compare comp;
				public:
					value_compare(Compare c = Compare()) : comp(c) {}
					value_compare(const value_compare& other) : comp(other.comp) {}

					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
					value_compare& operator=(const value_compare& other)
					{
						comp = other.comp;
						return *this;
					}
			};
			//typedef value_compare comp;
			typedef map_iterator<value_type, Key, Compare> iterator;
			typedef const_map_iterator<value_type, Key, Compare> const_iterator;
			typedef ft::rev_map_iterator<iterator> reverse_iterator;
			typedef ft::rev_map_iterator<const_iterator> const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type difference_type;
			typedef Allocator allocator_type;
			typedef T& reference;
			typedef const T& const_reference;
			typedef T* pointer;
			typedef const T* const_pointer;
			typedef Compare key_compare;
			key_compare _comp;

		private:

			template<class InputIterator, class InputIterator2>
			bool	lexicographical_compare_(InputIterator first1, InputIterator last1, InputIterator2 first2, InputIterator2 last2) const
			{
				for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
				{
					if (first1->first < first2->first || first1->second < first2->second)
						return (true);
					if (first1->first > first2->first || first1->second > first2->second)
						return (false);
				}
				return ((first1 == last1) && (first2 != last2));
			}

			typedef node<value_type> node_type;
			typedef node<const value_type> const_node_type;
			typedef size_t size_type;
			typedef Key key_type;

			typedef rb_tree<value_type, Key, value_compare> tree_type; //maybe value_compare
			//typedef rb_tree<value_type, Key, Compare, value_compare> tree_type;
			tree_type _tree;
			allocator_type _allocator;

		public://maybe need to incorporate key_compare in rb_tree
			
			map() : _comp(key_compare()), _allocator(allocator_type()) {}
			explicit map (const Compare& comp,
              const allocator_type& alloc = allocator_type()) :  _comp(comp), _allocator(alloc){}
			template<class InputIterator>
			map(InputIterator first, InputIterator last,
			const Compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _comp(comp), _allocator(alloc)
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
			void print() const
			{
				_tree.print_nodes();
			}
			ft::pair<iterator, bool> insert(const value_type& val)
			{
				ft::pair<iterator, bool> result;
				try
				{
					_tree.insert(val);
					result.first = iterator(_tree.find_node(val), _tree.end_node());
					result.second = true;
				}
				catch(const std::string& e)
				{
					//std::cerr << e << '\n'; //maybe unusefull
					result.first = iterator(_tree.find_node(val), _tree.end_node());
					result.second = false;
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
					result = iterator(_tree.find_node(val), _tree.end_node());	
				}
				catch(const std::string& e)
				{
					//std::cerr << e << '\n'; //maybe unusefull
					result = iterator(_tree.find_node(val), _tree.end_node());
				}
				return result;
			}
			template <class InputIterator> //check that is is a bidirectionnal iterator
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
			insert(InputIterator first, InputIterator second)
			{
					for (InputIterator i = first; i != second; ++i)
					{
						try
						{
							_tree.insert(*i);
						}
						catch(const std::string& e)
						{
							//std::cerr << e << '\n';
						}
					}
			}
			const_iterator begin() const
			{
				node_type* result = 0;
				_tree.min_node(_tree.root_node(), &result);
				if (!result)
					return const_iterator(_tree.end_node(), _tree.end_node());
				return const_iterator(result, _tree.end_node());
			}
			iterator begin()
			{
				node_type* result = 0;
				_tree.min_node(_tree.root_node(), &result);
				if (!result)
					return iterator(_tree.end_node(), _tree.end_node());
				return iterator(result, _tree.end_node());
			}
			iterator end()
			{
				return iterator(_tree.end_node(), _tree.end_node());
			}
			const_iterator end() const
			{
				return const_iterator(_tree.end_node(), _tree.end_node());
			}
			reverse_iterator rbegin()
			{
				return reverse_iterator(iterator(_tree.end_node(), _tree.end_node()));
			}
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(const_iterator(_tree.end_node(), _tree.end_node())); 
			}
			reverse_iterator rend()
			{
				node_type* result = 0;
				_tree.min_node(_tree.root_node(), &result);
				if (!result)
					return reverse_iterator(iterator(_tree.end_node(), _tree.end_node()));
				return reverse_iterator(iterator(result, _tree.end_node()));
			}
			const_reverse_iterator rend() const
			{
				node_type* result = 0;
				_tree.min_node(_tree.root_node(), &result);
				if (!result)
					return const_reverse_iterator(const_iterator(_tree.end_node(), _tree.end_node()));
				return const_reverse_iterator(const_iterator(result, _tree.end_node()));
			}
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
				return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
			}
			ft::pair<iterator, iterator> equal_range(const Key& key)
			{
				return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
			}
			bool empty() const
			{
				return _tree.empty();
			}
			iterator find(const Key& key)
			{
				try
				{
					return iterator(_tree.find_node(_tree.find_key(key)), _tree.end_node());
				}
				catch(const std::string& e)
				{
					return end();
				}
			}
			const_iterator find(const Key& key) const
			{
				try
				{
					return const_iterator(_tree.find_node(_tree.find_key(key)), _tree.end_node());
				}
				catch(const std::string& e)
				{
					return end();
				}
			}
			allocator_type get_allocator() const
			{
				return Allocator();
			}
			size_t max_size() const
			{
				return std::allocator<node_type>().max_size();
			}
			size_t size() const
			{
				return _tree.size();
			}
			T& operator[] (const Key& key)
			{
				return (*insert(pair<Key, T>(key, T())).first).second;
			}

			iterator lower_bound (const Key& key)
			{
				node_type* temp;
				temp = _tree.find_node(pair<Key, T>(key, T())); //
				if (temp != _tree.end_node())
					return iterator(temp, _tree.end_node());
				temp = _tree.find_next_key(key);
				if (temp)
					return iterator(temp, _tree.end_node());
				else
					return iterator(_tree.end_node(), _tree.end_node());
			}
			const_iterator lower_bound (const Key& key) const
			{
				node_type* temp;
				
				temp = _tree.find_node(make_pair(key, 0));
				if (temp != _tree.end_node())
					return const_iterator(temp, _tree.end_node());
				temp = _tree.find_next_key(key);
				if (temp)
					return const_iterator(temp, _tree.end_node());
				else
					return const_iterator(_tree.end_node(), _tree.end_node());
			}
			iterator upper_bound (const Key& k)
			{
				node_type* temp = _tree.find_next_key(k);
				if (temp)		
					return iterator(temp, _tree.end_node());
				else
					return iterator(_tree.end_node(), _tree.end_node());
			}
			const_iterator upper_bound (const Key& k) const
			{
				node_type* temp = _tree.find_next_key(k);
				if (temp)		
					return const_iterator(temp, _tree.end_node());
				else
					return const_iterator(_tree.end_node(), _tree.end_node());
			}
			Compare	key_comp() const
			{
				return (Compare());
			}
			value_compare value_comp() const
			{
				return (value_compare());
			}
			void erase(iterator position)
			{
				_tree.remove(position._ptr);
			}
			size_type erase(const key_type& k)
			{
				try
				{
					_tree.remove(_tree.find_node(_tree.find_key(k)));
					return 1;
				}
				catch (const std::string& e)
				{
					return 0;
				}
			}
    		void erase(iterator first, iterator last)
			{
				int len = ft::distance(first, last);
				pair<Key, T>* key_list = _allocator.allocate(len);
				for (int i = 0; first != last; ++first, ++i)
					_allocator.construct(key_list + i, *first);
				for (int i = 0; i < len; ++i)
				{
					erase(key_list[i].first);
				}
				_allocator.deallocate(key_list, len);
			}
			void swap(map& x)
			{
				_tree.swap(x._tree);
			}

			bool operator==(const map& other) const
			{
				if (this->size() != other.size())
					return false;
				return ft::equal(begin(), end(), other.begin(), other.end());
			}
			bool operator!=(const map& other) const
			{
				return !(*this == other);
			}
			bool operator<(const map& other) const
			{
				return lexicographical_compare_(begin(), end(), other.begin(), other.end());
			}
			bool operator>(const map& other) const
			{
				return (other < *this);
			}
			bool operator<=(const map& other) const
			{
				return (*this == other || *this < other);
			}
			bool operator>=(const map& other) const
			{
				return (*this == other || *this > other);
			}
	};

	template <class Key, class T, class Compare, class Alloc>
  	void swap(ft::map<Key,T,Compare,Alloc>& x, ft::map<Key,T,Compare,Alloc>& y)
	  {
		  x.swap(y);
	  }
}
#endif