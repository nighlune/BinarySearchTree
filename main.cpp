#include "bst.h"

#include <iostream>

using namespace std;

int main()
{	
	//create a binary search tree
	BST<int> tree;

	cout << "------<removing 7 (tree is empty)>------" << endl;

	//attempt to remove 7 from an empty tree
	try
	{
		tree.remove(7);
	}

	catch(out_of_range& err)
	{
		cout << err.what() << endl;
	}

	//insert 6, 10, 3, 13, 21, 1, 4, and 9
	tree.insert(6);
	tree.insert(10);
	tree.insert(3);
	tree.insert(13);
	tree.insert(21);
	tree.insert(1);
	tree.insert(4);
	tree.insert(9);
	
	//print out full tree
	tree.print();
		
	cout << "------<removing 6>------" << endl;

	//remove 6 (the root) then print out the re-organized tree
	tree.remove(6);

	tree.print();

	cout << "------<removing 9>------" << endl;

	//remove 9 then print out the re-organized tree
	tree.remove(9);

	tree.print();

	cout << "------<removing 3>------" << endl;
	//remove 3 then print out the re-organized tree
	tree.remove(3);

	tree.print();

	cout << "------<removing 77 (not in the tree)>------" << endl;

	//try to remove 77, a value not in the tree
	try
	{
		tree.remove(77);
	}

	catch(out_of_range& err)
	{
		cout << err.what() << endl;
	}

	cout << endl;

	cout << "------<printInOrder()>------" << endl;

	//print the tree from lowest value to highest value
	tree.printInOrder();

	cin.get();
}
