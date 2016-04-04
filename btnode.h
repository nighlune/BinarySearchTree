#ifndef BTNODE_H_
#define BTNODE_H_

#include <iostream>

/*
	A class to represent a node in a
	binary search tree.
*/
template <typename T>
class BTNode
{
	public:

		//constructor
		BTNode(const T& d);

		//the node's data value
		T data;
		
		//pointer to the node's left child
		BTNode<T>* left;
		
		//pointer to the node's right child
		BTNode<T>* right;
};

/*
	Simple constructor.  Sets the data
	value of the BTNode to "d" and defaults its
	left and right child pointers to NULL.
*/
template <typename T>
BTNode<T>::BTNode(const T& d)
: left(NULL), right(NULL), data(d) {}
	
#endif