#include <iostream>
#include "vector.hpp"
#include "iterator.hpp"
#include "stack.hpp"
#include "rb_tree.hpp"

int main()
{
	ft::rb_tree<int, char> lol;
	lol.insert(ft::node<int, char> (10, 'Q'));
	lol.insert(ft::node<int, char> (20, 'P'));
	lol.insert(ft::node<int, char> (5, 'C'));
	lol.insert(ft::node<int, char> (15, 'B'));
	lol.print_nodes(lol.nodes);
	lol.insert(ft::node<int, char> (30, 'A'));

	std::cout << "------------------" << std::endl;
	ft::node<int, char>* P = lol.find_node(20);
	P->_parent->_right = P->_right;
	P->_right->_parent = P->_parent;
	P->_right = P->_parent;
	ft::node<int, char>* temp_P_Left = P->_left;
	P->_left = P->_parent->_left;
	P->_left->_parent = P;
	P->_parent->_left = temp_P_Left;
	temp_P_Left->_parent = P->_parent;
	ft::node<int, char>* tempParentParent = P->_parent->_parent;
	P->_parent->_parent = P;
	P->_parent = tempParentParent;
	lol.nodes = P;



	lol.print_nodes(lol.nodes);

}