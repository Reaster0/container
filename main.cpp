#include <iostream>
#include "vector.hpp"
#include "iterator.hpp"
#include "stack.hpp"
#include "rb_tree.hpp"
//#include "map.hpp"
#include <map>

int main()
{
	// ft::map<int, char> testing;
	// ft::rb_tree<const int, char> test;
	// testing.insert(ft::pair<int, char>(2, 'F'));
	// testing.insert(testing.begin(), ft::pair<int, char>(6, 'A'));
	// testing.clear();

	ft::rb_tree<int> tree;
	tree.insert(10);
	tree.insert(20);
	tree.insert(5);
	tree.insert(7);
	tree.insert(15);
	tree.insert(30);
	tree.insert(4);
	tree.insert(12);
	tree.insert(40);
	tree.insert(45);
	tree.insert(21);
	tree.insert(11);
	tree.insert(9);
	tree.insert(8);
	tree.print_nodes();

	ft::rb_tree<ft::pair<int, char> > tree2;
	tree2.insert(ft::pair<int, char>(10, 'a'));
	tree2.insert(ft::pair<int, char>(12, 'b'));
	tree2.print_nodes();
}