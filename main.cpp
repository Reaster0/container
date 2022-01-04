#include <vector>
#include "vector.hpp"
#include "iterator.hpp"

int main()
{
	ft::vector<int> v;
	ft::vector<int> v2;
	ft::vector<int>::iterator it;
	v.push_back(42);
	v.push_back(42);
	v.push_back(42);
	v.push_back(42);
	//v.push_back(111);

	//v.insert(v.begin() + 1, 1);
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << std::endl;
	std::cout << "\\\\\\\\\\\\\\\\\\" << std::endl;
	for (it = v.begin(); it != v.end(); ++it)
		std::cout << "everything" << std::endl;
}