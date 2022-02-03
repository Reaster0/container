#include <iostream>
#include "vector.hpp"
#include "iterator.hpp"
#include "stack.hpp"
#include "rb_tree.hpp"
#include "map.hpp"
#include <map>

int main()
{
	ft::map<int> testing;
	testing.insert(1);
	testing.insert(4);
	testing.insert(5);
	testing.print();
}