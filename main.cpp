#include <iostream>
#include "vector.hpp"
#include "iterator.hpp"
#include "stack.hpp"
#include "rb_tree.hpp"
#include "map.hpp"
#include <map>
#include <fstream>
#include <vector>
#include <list>
#include <string>

//typedef std::pair<int, int> pair;
typedef ft::pair<const int, std::string> pair;

int main()
{
	ft::map<int, int> testing;
	// testing.insert(pair(7, 7));
	// testing.insert(pair(3,3));
	// testing.insert(pair(18, 18));
	// testing.insert(pair(10, 10));
	// testing.insert(pair(22, 22));
	// testing.insert(pair(26, 26));
	// testing.insert(pair(8, 8));
	// testing.insert(pair(11, 11));

	// testing.insert(pair(10,10));
	// testing.insert(pair(40, 40));
	// testing.insert(pair(50, 50));
	// testing.insert(pair(60, 60));
	// testing.insert(pair(45, 45));
	// testing.insert(pair(20, 20));
	// testing.insert(pair(5, 5));
	// testing.insert(pair(3, 3));
	// testing.insert(pair(8, 8));
	// testing.insert(pair(18, 18));
	// testing.insert(pair(22, 22));
	// testing.insert(pair(41, 41));
	// testing.insert(pair(47,47));
	// testing.insert(pair(64, 64));
	//testing.insert(pair(50,50));
	//testing.insert(pair(20,20));
	//testing.insert(pair(80,80));
	// testing.insert(pair(70, 70));
	// testing.insert(pair(100, 100));
	// testing.insert(pair(10, 10));
	// testing.insert(pair(40, 40));
	// testing.insert(pair(900, 900));
	// testing.insert(pair(400, 400));
	// testing.insert(pair(60, 60));
	// testing.insert(pair(75, 75));

	ft::map<int, std::string> test3;
	test3.insert(ft::pair<int, std::string>(4, std::string("lolmdr")));
	//ft::map<int, int>::iterator it = testing.begin();
	++test3.begin();
	test3[42] = "truc";
std::cout << "-------------------------------\n";

	test3.print();
	std::string lol = "truc";
//	testing.print();

	// std::map<int, int> testing2;
	// testing2.insert(pair(100,10));
	// testing2.insert(pair(10, 40));
	// testing2.insert(pair(70, 50));
	// testing2.insert(pair(69, 60));
	//std::cout << *test.end() << std::endl;
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