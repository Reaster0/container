#include <vector>
#include "vector.hpp"
#include "iterator.hpp"

int main()
{
	ft::vector<int> v;
	v.push_back(42);
	v.push_back(1);
	std::cout << v.capacity() << std::endl;
	v.reserve(3);
	std::cout << v.capacity() << std::endl;
	v.print_debug();
	v.push_back(112);
	v.push_back(111);
	v.print_debug();
	std::cout << v.capacity() << std::endl;
	v.resize(10);
	v.print_debug();
	std::cout << v.capacity() << std::endl;
	std::cout << v.front() << std::endl;
	std::cout << v.back() << std::endl;
	std::cout << v.at(2) << std::endl;
	v[3] = 90;
	std::cout << v[3] << std::endl;
	v.print_debug();
	std::cout << v.empty() << std::endl;
}