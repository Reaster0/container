#include <iostream>
#include "vector.hpp"
#include "iterator.hpp"
#include "stack.hpp"
#include "rb_tree.hpp"
#include "map.hpp"
#include <map>
#include <fstream>
#include <vector>

//typedef std::pair<int, char> pair;
typedef ft::pair<int, int> pair;

int main()
{
	// ft::map<int, int> testing;
	// testing.insert(pair(1,10));
	// testing.insert(pair(4, 40));
	// testing.insert(pair(5, 50));
	// testing.insert(pair(6, 60));
	// testing.insert(pair(0, 70));

	// std::map<int, int> testing2;
	// testing2.insert(pair(100,10));
	// testing2.insert(pair(10, 40));
	// testing2.insert(pair(70, 50));
	// testing2.insert(pair(69, 60));
	ft::map<int, int> test;
	test.insert(pair(2, 30));
	ft::map<int, int>::iterator it = test.end();
	//std::cout << *test.end() << std::endl;
	it++;
	return 1;
}

    // std::ifstream source("test", std::ios::binary);
    // std::vector<char> data((std::istreambuf_iterator<char>(source)),
    //                    std::istreambuf_iterator<char>());
    // std::cout << data[0] << data[1] << data[2] << std::endl;
    // source.close();
    // std::ifstream sourceb("test", std::ios::binary);
    // ft::vector<char> data2((std::istreambuf_iterator<char>(sourceb)),
    //                    std::istreambuf_iterator<char>());
    // std::cout << data2[0] << data2[1] << data2[2] << std::endl;
    // return(0);