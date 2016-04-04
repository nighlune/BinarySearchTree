#ifndef BST_H_
#define BST_H_

#include <stdexcept>
#include "btnode.h"

/*
	A class to represent a templated binary search tree.
*/
template <typename T>
class BST
{
	private:
	
		//pointer to the root node in the tree
		BTNode<T>* root;
		
	public:
		
		//default constructor to make an empty tree
		BST();
		
		//function to insert a new node into a binary search tree
		//according to the binary search tree rules
		void insert(const T& value);
		
		//function to determine whether or not the input value
		//exists in the tree. Returns true if the 
		//value is found or false if the value is not found
		bool search(const T& value) const;
		
		//recursive function to print out the values contained
		//in the tree in ascending (sorted) order
		void printInOrder() const;
		
		//function to remove a node from the tree, includes removal
		//of a node with no children, left child, right child, or
		//two children
		void remove(const T& value);
		
		//function to print out a visual representation
		//of the tree (not just print the tree's values 
		//on a single line)
		void print() const;
		
	private:
		
		//recursive helper function for "printInOrder()"
		void printInOrder(BTNode<T>* node) const;

		//recursive helper function for "print()"
		void print(BTNode<T>* node,int depth) const;
};

/*
	Default constructor to make an empty tree
*/
template <typename T>
BST<T>::BST()
{
	root = NULL;
}

template <typename T>
void BST<T>::insert(const T& value)
{
	//create memory for a new node
	BTNode<T>* nodeToInsert = new BTNode<T>(value);

	//initialize left and right to NULL
	nodeToInsert->left = NULL;
	nodeToInsert->right = NULL;

	//create a pointer to the root
	BTNode<T>* current = root;

	//if the tree is empty, new node is the root
	if(root == NULL)
	{
		root = nodeToInsert;
	}

	else
	{
		while(current != NULL)
		{
			//if the value is already in the tree, throw an error
			if(current->data == value)
			{
				throw out_of_range("Value found in tree.");
			}

			//otherwise if the data at current is larger than the value of the new node
			else if(current->data > value)
			{
				//if current's left child is NULL, current's left child is the new node
				if(current->left == NULL)
				{
					current->left = nodeToInsert;

					break;
				}

				//traverse down the tree following the left child
				current = current->left;
			}

			//otherwise if the data at current is less than the value of the new node
			else if(current->data < value)
			{
				//if current's right child is NULL, current's right child is the new node
				if(current->right == NULL)
				{
					current->right = nodeToInsert;

					break;
				}

				//traverse down the tree following the right child
				current = current->right;
			}
		}
	}
}

template <typename T>
bool BST<T>::search(const T& value) const
{
	//create a pointer to the root
	BTNode<T>* current = this->root;
	
	while(current != NULL)
	{
		//if current's data equals the value return true
		if(current->data == value)
		{
			return true;
		}

		//if current's data is greater than the value, move to the left child
		else if(current->data > value)
		{
			current = current->left;
		}

		//if current's data is less than the value, move to the right child
		else if(current->data < value)
		{
			current = current->right;
		}
	}

	//value is not found, return false
	return false;
}

template <typename T>
void BST<T>::printInOrder() const
{
	//print out the value's in the tree in order
	printInOrder(root);
}

template <typename T>
void BST<T>::printInOrder(BTNode<T>* node) const
{
	if(node != NULL)
	{
		//call print on the node's left child
		printInOrder(node->left);

		//print the node itself
		cout << node->data << " ";

		//call print on the node's right child
		printInOrder(node->right);
	}	
}

template <typename T>
void BST<T>::remove(const T& value)
{
	//if the tree is empty, throw an error
	if(this->root == NULL)
	{
		throw out_of_range("Tree is empty!");
	}

	//call search on value to remove to make sure it's in the tree
	bool isPresent = search(value);

	//if the value is present
	if(isPresent)
	{
		//pointer to the root
		BTNode<T>* current = this->root;

		//a pointer to follow current to retreive the parent of a child node
		BTNode<T>* previous = this->root;

		//a pointer with the node to delete
		BTNode<T>* nodeToDelete = NULL;

		//a temporary pointer to hold the node's left children
		BTNode<T>* tempNode = NULL;

		//if the root is the value
		if(root->data == value)
		{
			//if the root has two children
			if(root->left != NULL && root->right != NULL)
			{
				//set the node to delete to the root
				nodeToDelete = root;

				//temp holds the root's left children
				tempNode = root->left;

				//set the root to be root's right child (the larger number)
				root = root->right;

				//delete the root
				delete nodeToDelete;

				//set current to the new root's left child
				current = root->left;

				//if root has no left child, the temporary node is root's new left child
				if(root->left == NULL)
				{
					root->left = tempNode;
				}

				//if the new root already has left children
				else
				{
					//find the last left child
					while(current != NULL)
					{
						if(current->left == NULL)
						{
							//set the temp node to be roots left most child
							current->left = tempNode;

							break;
						}

						//next left child
						current = current->left;
					}
				}
			}

			//if the root has a left child
			else if(root->left != NULL && root->right == NULL)
			{
				//set node to delete to root
				nodeToDelete = root;

				//set root to it's left child
				root = root->left;

				//delete root
				delete nodeToDelete;
			}

			//if the root has a right child
			else if(root->left == NULL && root->right != NULL)
			{
				//set node to delete to root
				nodeToDelete = root;

				//set root to it's right child
				root = root->right;

				//delete root
				delete nodeToDelete;
			}

			//if the root has no children
			else if(root->left == NULL && root->right == NULL)
			{
				delete root;
				root = NULL;
			}
		}

		//the value is below the root
		else
		{
			//iterate through the tree until the value is found
			while(current != NULL)
			{
				//the node containing the value is found
				if(current->data == value)
				{
					//removing a node with no children
					if(current->left == NULL && current->right == NULL)
					{
						delete current;

						//if current was left child, previous's left child is NULL
						if(previous->left == current)
						{
							previous->left = NULL;
						}

						//if current was right child, previous's right child is NULL
						else
						{
							previous->right = NULL;
						}
						
						break;
					}

					//removing a node with left child
					else if(current->left != NULL && current->right == NULL)
					{
						//if current is left child
						if(previous->left == current)
						{
							//parent's left child is current's left child
							previous->left = current->left;
						}

						//if current is right child
						if(previous->right == current)
						{
							//parent's right child is current's left child
							previous->right = current->left;							
						}

						//set node to delete to current
						nodeToDelete = current;

						delete nodeToDelete;

						break;
					}

					//removing a node with right child
					else if(current->left == NULL && current->right != NULL)
					{
						//if current is left child
						if(previous->left == current)
						{
							//parent's left child is current's right child
							previous->left = current->right;
						}

						//if current is right child
						if(previous->right == current)
						{
							//parent's right child is current's right child
							previous->right = current->right;							
						}

						nodeToDelete = current;

						delete nodeToDelete;

						break;
					}

					//removing a node with two children
					else if(current->left != NULL && current->right != NULL)
					{
						//if previous's left is current
						if(previous->left == current)
						{
							//set previous's left to current's right
							previous->left = current->right;
						}

						//if previous's right is current
						if(previous->right == current)
						{
							//set previous's right to current's right
							previous->right = current->right;
						}

						//deleting the current node
						nodeToDelete = current;

						//the temp holds current's left to rejoin to the tree in the proper location
						tempNode = current->left;

						//set current to current's right
						current = current->right;

						delete nodeToDelete;

						//move the right children under the left most of the original left child
						if(current->left == NULL)
						{
							current->left = tempNode;
						}

						else
						{
							//find current's left most child
							while(current != NULL)
							{
								current = current->left;
							}

							//set temp to current's left node
							current->left = tempNode;
						}

						break;
					}
				}

				//if the value is less than the node's value (left)
				else if(current->data > value)
				{
					previous = current;
					current = current->left;
				}

				//if the value is more than the node's value (right)
				else if(current->data < value)
				{
					//set previous to current
					previous = current;

					//set current to current's right child
					current = current->right;
				}
			}
		}
	}

	//the value is not found in the tree
	else
	{
		throw out_of_range("Value not found in tree.");
	}
}

/*
	Print out the values in the tree and their
	relationships visually.  Sample output (10 is the root):
	
	                    22
                18
        15
10
                9
        5
                3
                        1
*/
template <typename T>
void BST<T>::print() const
{
	print(root,0);
}

template <typename T>
void BST<T>::print(BTNode<T>* node,int depth) const
{
	if(node == NULL)
	{
		std::cout << std::endl;
		return;
	}
	
	print(node->right,depth+1);
	
	for(int i=0; i < depth; i++)
	{
		std::cout << "\t";
	}
	
	std::cout << node->data << std::endl;
	
	print(node->left,depth+1);
}

#endif