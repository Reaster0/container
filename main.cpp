#include <iostream>
#include "vector.hpp"
#include "iterator.hpp"
#include "stack.hpp"
#include "rb_tree.hpp"
#include "map.hpp"
#include <map>

int main()
{
	// ft::rb_tree<int, char> lol;
	// lol.insert(ft::node<int, char> (10, 'Q'));
	// std::cout << "---------------------------------\n";
	// 	lol.print_nodes();
	// lol.insert(ft::node<int, char> (20, 'P'));
	// 	std::cout << "---------------------------------\n";
	// 	lol.print_nodes();
	// lol.insert(ft::node<int, char> (5, 'C'));
	// 	std::cout << "---------------------------------\n";
	// 	lol.print_nodes();
	// lol.insert(ft::node<int, char> (7, 'E'));
	// 	std::cout << "---------------------------------\n";
	// lol.print_nodes();
	// lol.insert(ft::node<int, char> (15, 'B'));
	// 	std::cout << "---------------------------------\n";
	// 	lol.print_nodes();
	// lol.insert(ft::node<int, char> (30, 'A'));
	// 	std::cout << "---------------------------------\n";
	// lol.print_nodes();
	// lol.insert(ft::node<int, char> (4, 'L'));
	// 	std::cout << "---------------------------------\n";
	// 	lol.print_nodes();
	// lol.insert(ft::node<int, char> (12, 'R'));
	// 	std::cout << "---------------------------------\n";
	// 	lol.print_nodes();
	// lol.insert(ft::node<int, char> (40, 'T'));
	// 	std::cout << "---------------------------------\n";
	// 	lol.print_nodes();
	// lol.insert(ft::node<int, char> (45, 'O'));
	// 	std::cout << "---------------------------------\n";
	// 	lol.print_nodes();
	// lol.insert(ft::node<int, char> (21, 'Y'));
	// 	std::cout << "---------------------------------\n";
	// 	lol.print_nodes();
	// lol.insert(ft::node<int, char> (11, 'X'));
	// 	std::cout << "---------------------------------\n";
	// 	lol.print_nodes();
	// lol.insert(ft::node<int, char> (9, 'Z'));
	// 	std::cout << "---------------------------------\n";
	// 	lol.print_nodes();
	// lol.insert(ft::node<int, char> (8, 'G'));
	// 	std::cout << "---------------------------------\n";
	// 	lol.print_nodes();

	// std::cout << "------------------" << std::endl;
	// lol.print_nodes();

	ft::map<int, char> testing;
	ft::rb_tree<const int, char> test;
	testing.insert(ft::pair<int, char>(2, 'F'));
	testing.insert(testing.begin(), ft::pair<int, char>(6, 'A'));
	testing.clear();
}