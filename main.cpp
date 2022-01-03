#include <vector>
#include "vector.hpp"
#include "iterator.hpp"

int main()
{
	ft::vector<int> v;
	ft::vector<int> v2;

	std::cout << "\\\\\\\\\\\\\\\\\\" << std::endl;
	v.push_back(42);
	v.push_back(42);
	v.push_back(42);
	v.push_back(42);
	v.push_back(42);

	v2 = v;
	v.assign(1, 10);

	ft::vector<int> result(5, 10);
	ft::vector<int> result2(5, 10);
	result[5] = 11;
	std::cout << "------------------\n" 
	<< (result <= result2) << std::endl;

}