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
	testing.insert(pair(6, 60));
	std::cout << testing[1] << std::endl;
	//ft::map<int, int>::const_iterator it = testing.find2(6);
	//testing.print();
	//std::pair<std::map<int, int>::iterator, std::map<int, int>::iterator > it = testing.equal_range(3);
	//std::cout << *it << std::endl;
}