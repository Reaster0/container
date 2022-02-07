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
	testing.print();
std::cout << "-----------------------------------" << std::endl;
	ft::map<int, int> testing2;
	testing2.insert(pair(100,10));
	testing2.insert(pair(10, 40));
	testing2.insert(pair(70, 50));
	testing2.insert(pair(69, 60));
	testing2.print();

std::cout << "-----------------------------------" << std::endl;
	ft::swap<int, int, std::allocator<ft::pair<int, int> >, std::less<int> >(testing, testing2);
	testing.print();
std::cout << "-----------------------------------" << std::endl;
	testing2.print();
	std::cout << testing.lower_bound(70)->_data << std::endl;
}