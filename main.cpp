#include <vector>
#include "vector.hpp"

int main()
{
	std::allocator<int> lol;

	int *lol = lol.allocate(5);
}