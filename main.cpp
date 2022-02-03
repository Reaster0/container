#include <iostream>
#include "vector.hpp"
#include "iterator.hpp"
#include "stack.hpp"
#include "rb_tree.hpp"
#include "map.hpp"
#include <map>

//typedef std::pair<int, char> pair;
typedef ft::pair<int, int> pair;

int main()
{
	ft::map<int, int> testing;
	testing.insert(pair(1,10));
	testing.insert(pair(4, 40));
	testing.insert(pair(5, 50));
	testing.print();
	std::cout << testing.count(5) << std::endl;
}