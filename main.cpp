#include <iostream>
#include "vector.hpp"
#include "iterator.hpp"
#include "stack.hpp"
#include "rb_tree.hpp"
#include "map.hpp"
#include <fstream>

int	main(void)
{
	ft::map<int, std::string> ma_map;

	ma_map.insert(ft::pair<int, std::string>(30, "lol"));
	ma_map[64] = "ceci est une phrase";
	ma_map[42] = "ce projet etait long!";
	ma_map[1] = "et on enleve une node?";
	ma_map.print();

	std::cout << "---------------------------------------" << std::endl;
	ma_map.erase(42);
	ma_map.print();

	ft::vector<int> vectour;

	vectour.push_back(42);
	vectour[1] = 50;
	std::cout << "vectour[0] =" << vectour[0] << " and vectour[1] =" << vectour[1] << std::endl;

	ft::stack<int> stick;

	stick.push(42);
	stick.push(50);
	std::cout << "stick top = " << stick.top() << " and remember that stack is a fraud of vector" << std::endl;
	


	std::cout << "\nplease use mli tester https://github.com/mli42/containers_test.git or mazoise https://github.com/Mazoise/42TESTERS-CONTAINERS.git tester for further tests for the correction" << std::endl;
	
	return 0;
}