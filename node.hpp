#ifndef _node_
#define _node_

#define RED 1
#define BLACK 0

namespace ft
{
	template <class T>
	struct node
	{
		typedef node<T> node_type;

		T _data;
		bool _color;
		bool _nil;
		node* _left;
		node* _right;
		node* _parent;
		node()
		{
			_left = 0;
			_right = 0;
			_parent = 0;
			_nil = 0;
			_color = RED;
		}
		node(const T& data, const bool& color = RED, node* left = 0, node* right = 0, node* parent = 0) : _data(data), _color(color), _left(left), _right(right), _parent(parent)
		{
			_nil = false;
		}
		node(const node<T>& other) : _data(other._data), _color(other._color), _left(other._left), _right(other._right), _parent(other._parent)
		{
			_nil = other._nil;
		}
		~node()
		{
		}
		node& operator=(const node<T>& other)
		{
			_data = other._data;
			_left = other._left;
			_right = other._right;
			_parent = other._parent;
			_nil = other._nil;
			return *this;
		}
		
		node_type* uncle()
		{
			if (!_parent || !_parent->_parent)
				return 0;
			if (_parent->_parent->_left == _parent)
				return _parent->_parent->_right;
			else
				return _parent->_parent->_left;
		}
		int uncle_color()
		{
			if (!_parent || !_parent->_parent)
				return 42;
			if (_parent->_parent->_left == _parent && _parent->_parent->_right)
				return _parent->_parent->_right->_color;
			else if (_parent->_parent->_right == _parent && _parent->_parent->_left)
				return _parent->_parent->_left->_color;
			else
				return BLACK;
		}
		T& operator*()
		{
			return _data;
		}
		operator node<const T>() const
		{
			return node<const T>(_data, _color, _left, _right, _parent);
		}
	};

	template <class T, class U>
	bool operator==(const node<T>& A, const node<U>& B)
	{
		return A._data == B._data;
	}
	template <class T, class U>
	bool operator!=(const node<T>& A, const node<U>& B)
	{
		return A._data != B._data;
	}
	template <class T, class U>
	bool operator<(const node<T>& A, const node<U>& B)
	{
		return A._data < B._data;
	}
	template <class T, class U>
	bool operator>(const node<T>& A, const node<U>& B)
	{
		return B._data < A._data;
	}
	template <class T, class U>
	bool operator>=(const node<T>& A, const node<U>& B)
	{
		return !(A._data < B._data);
	}
		template <class T, class U>
	bool operator<=(const node<T>& A, const node<U>& B)
	{
		return !(A._data > B._data);
	}
}

#endif