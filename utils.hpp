#ifndef _utils_
#define _utils_

namespace ft
{
	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template <typename T>
    struct is_integral {
		static const bool value = false;
	};

    template <>
    struct is_integral<bool> {
		static const bool value = true;
	};
        
    template <>
    struct is_integral<char> {
		static const bool value = true;
	};

    template <>
    struct is_integral<short> {
		static const bool value = true;
	};

    template <>
    struct is_integral<int> {
		static const bool value = true;
	};

    template <>
    struct is_integral<long> {
		static const bool value = true;
	};

    template <>
    struct is_integral<long long> {
		static const bool value = true;
	};

    template <>
    struct is_integral<unsigned char> {
		static const bool value = true;
	};

    template <>
    struct is_integral<unsigned short> {
		static const bool value = true;
	};

    template <>
    struct is_integral<unsigned int> {
		static const bool value = true;
	};

    template <>
    struct is_integral<unsigned long> {
		static const bool value = true;
	};

    template <>
    struct is_integral<unsigned long long> {
		static const bool value = true;
	};

	template <class InputIterator, class InputIterator2>
	typename ft::enable_if<!ft::is_integral<InputIterator>::value || !ft::is_integral<InputIterator2>::value, bool>::type
	lexicographical_compare(InputIterator begin1, InputIterator end1, InputIterator2 begin2, InputIterator2 end2)
	{
		for (InputIterator it = begin1, it2 = begin2; it2 != end2; ++it, ++it2)
		{	if (it == end1 || *it < *it2)
				return true;
			if (*it2 < *it)
				return false;
		}
		return false;
	}
	template <class InputIterator, class InputIterator2>
	typename ft::enable_if<!ft::is_integral<InputIterator>::value || !ft::is_integral<InputIterator2>::value, bool>::type
	equal(InputIterator begin1, InputIterator end1, InputIterator2 begin2, InputIterator2 end2)
	{
		for (InputIterator it = begin1, it2 = begin2; it != end1 && it2 != end2; ++it, ++it2)
			if (*it != *it2)
				return false;
		return true;
	}
}

#endif