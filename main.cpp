#include <vector>
#include "vector.hpp"

int main()
{
	std::vector <int>lol2;
	std::allocator<int> lol;

	int *lol = lol.allocate(5);
}