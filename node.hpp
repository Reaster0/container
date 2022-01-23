#ifndef _node_
#define _node_

#define RED 1
#define BLACK 0

namespace ft
{
	template <class Key, class T>
	struct node
	{
		typedef node<Key, T> node_type;

		Key _key;
		T _value;
		bool _color;
		node* _left;
		node* _right;
		node* _parent;
		node(const Key& key, const T& value, const bool& color = BLACK, node* left = nullptr, node* right = nullptr, node* parent = nullptr) : _key(key), _value(value), _color(color), _left(left), _right(right), _parent(parent)
		{
		}
		~node()
		{
		}
		node& operator=(const node<Key, T>& other)
		{
			_key = other._key;
			_value = other._value;
			_left = other._left;
			_right = other._right;
			_parent = other._parent;
			return *this;
		}
		node_type* uncle()//node_type* node)
		{
			if (!_parent || !_parent->_parent)
				return 0;
			if (_parent->_parent->_left == _parent)
				return _parent->_parent->_right;
			else
				return _parent->_parent->_left;
		}
		// operator node<const Key, const T>() const
		// {
		// 	return node<const Key, const T>(_key, _value, _color, _left, _right, _parent);
		// }
	};
	template <class Key, class T, class Key2, class T2>
	bool operator<(const node<Key, T>& A, const node<Key2, T2>& B)
	{
		return A._key < B._key;
	}
	template <class Key, class T, class Key2, class T2>
	bool operator>(const node<Key, T>& A, const node<Key2, T2>& B)
	{
		return B._key < A._key;
	}
}

#endif