#include <vector>
#include "vector.hpp"
#include "iterator.hpp"

int main()
{
	ft::vector<int> v;
	ft::vector<int> v2;
	ft::vector<int>::iterator it;
	//ft::iterator<int> it3;
	v.push_back(11);
	v.push_back(12);
	v.push_back(13);
	v.push_back(14);
	v.push_back(111);
	v2.push_back(21);
	v2.push_back(22);
	v2.push_back(23);
	v2.push_back(24);
	v2.push_back(25);

	it = v.begin();

	v.insert(v.end() - 2, v2.begin(), v2.end() - 1);
	v.erase(v.end(), v.end());
	std::cout << "\\\\\\\\\\\\\\\\\\" << std::endl;
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << std::endl;
}