#include <vector>
#include "vector.hpp"
#include "iterator.hpp"

int main()
{
	ft::vector<int> v;
	ft::vector<int> v2;
	std::vector<int>::iterator it;
	std::cout << "\\\\\\\\\\\\\\\\\\" << std::endl;
	v.push_back(42);
	v.push_back(42);
	v.push_back(42);
	v.push_back(42);
	v.push_back(42);
	
	ft::vector<int>::iterator it2 = v.begin();
	it2.test();
	std::cout << *it2.test2() << std::endl;
}