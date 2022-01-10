#ifndef _iterator_traits_
#define _iterator_traits_

namespace ft
{
		class input_iterator_tag {};
		class output_iterator_tag {};
		class forward_iterator_tag: public input_iterator_tag {};
		class bidirectional_iterator_tag: public forward_iterator_tag {};
		class random_access_iterator_tag: public bidirectional_iterator_tag {};

		template <class Iter>
		struct iterator_traits
		{
			typedef typename Iter::iterator_category iterator_category;
			typedef typename Iter::iterator::value_type value_type;
			typedef typename Iter::iterator::difference_type difference_type;
			typedef typename Iter::difference_type distance_type;
			typedef typename Iter::pointer pointer;
			typedef typename Iter::iterator::reference reference;
		};

		template <class T>
		struct iterator_traits<T*>
		{
			typedef typename 	ft::random_access_iterator_tag iterator_category;
			typedef T			value_type;
			typedef	T*			pointer;
			typedef T&			reference;
			typedef ptrdiff_t	difference_type;
		};

		template <class T>
		struct iterator_traits<const T*>
		{
			typedef typename ft::random_access_iterator_tag iterator_category;
			typedef T	value_type;
			typedef const T*	pointer;
			typedef const T&	reference;
		};

		// template<class InputIterator> //maybe don't usefull
 		//  typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
		//   {
		// 	  typename iterator_traits<InputIterator>::difference_type	 diff;
		// 	  //check if the iterator is random to make last - first
		// 	  diff = 0;
		// 	  for (InputIterator i = first; i != last; i++)
		// 	  		diff++;
		// 		return diff;
		//   }
	
}

#endif