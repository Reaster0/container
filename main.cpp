#include <vector>
#include "vector.hpp"
#include "iterator.hpp"

int main()
{
	ft::vector<int> v;
	v.push_back(42);
	v.push_back(78);
	v.print_debug();
	std::cout << v.capacity() << std::endl;
	v.pop_back();
	v.print_debug();
	std::cout << v.capacity() << std::endl;
	v.push_back(54);
	v.print_debug();
	std::cout << v.capacity() << std::endl;
}