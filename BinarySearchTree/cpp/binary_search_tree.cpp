//
// binary_search_tree.cpp
//
// Please refer to binary_search_tree.h for documentation.
//
//http://www.algolist.net/Data_structures/Binary_search_tree/Removal
//http://www.cpp-home.com/tutorials/151_1.htm
//http://math.hws.edu/eck/cs225/s03/binary_trees/
//http://en.wikipedia.org/wiki/Binary_search_tree
//http://cboard.cprogramming.com/c-programming/124929-help-delete-binary-search-tree.html
//http://stackoverflow.com/questions/10369159/deleting-node-from-a-binary-search-tree
//http://dev-faqs.blogspot.com/2012/03/remove-node-from-binary-search-tree.html
//http://www.youtube.com/watch?v=fa4i8v7YoeM
// Persons: 
#include <iostream>

#include "binary_search_tree.h"
using namespace std;
bt_node* init_node(int data) {
	bt_node* newbt_node = new bt_node;//creating a bt_node struct pointer that creates a new bt_node struct
	newbt_node -> data = data;//insterting data into the bt_node
	newbt_node -> left = NULL;//setting the left pointer of the struct to null
	newbt_node -> right = NULL;//setting the right pointer of the sruct to null
	
  return newbt_node;//returning the new bt_node
  
}
//inserts new node into binary tree
void insert(bt_node** top_ref, bt_node* new_node) {
	//setting up pointer to first node
	bt_node* parentbt_node = *top_ref;
	//checking if there are no nodes in tree
	if (*top_ref == NULL)
	{
		//insert node
		*top_ref = new_node;
	}
	else
	{
		//comparing data of new node to parent if less then data goes left
		if (new_node->data < parentbt_node->data)
	{		//if left child of parent is null insert new node
			if (parentbt_node->left == NULL)
		{
				parentbt_node->left = new_node;
		}
			else
		{
				//otherwise keep moving left
				insert(&parentbt_node->left, new_node);
		}
			
	}
		//if new node data is greater than or equal to parent move right
		else if (new_node->data >= parentbt_node->data)
	{
			//if right child of parent is null, insert new node there
			if (parentbt_node->right == NULL)
		{
				parentbt_node->right = new_node;
		}
			else 
		{
				//otherwise keep moving right
				insert(&parentbt_node->right, new_node);
		}
	}
}
}
//inserts new node with data into sorted binary tree
void insert_data(bt_node** top_ref, int data) {
	//creates new node with data
	bt_node* new_node = init_node (data);
	//calls insert funcion and inserts new node into tree
	insert(top_ref, new_node);
}
//removes node with given value from tree
void remove(bt_node** top_ref, int data) {
	//checks if no nodes in tree
	if ((*top_ref) == NULL)
	{
		return;
	}
	//compares data to other nodes and moves it either left or right down tree
	else if (data < (*top_ref)->data)
	{
		remove(&(*top_ref)->left, data);
	}
	else if (data > (*top_ref)->data)
	{
		remove(&(*top_ref)->right, data);
	}
	else 
	{
		//if node has no children...
		bt_node* temp;
		if (((*top_ref)->left == NULL) && ((*top_ref)->right == NULL))
		{
			temp = *top_ref;
			(*top_ref) = NULL;
			temp = NULL;
			delete temp;
			
		}
		//if node has right child no left then...
		else if ((*top_ref)->left == NULL)
		{
			temp = (*top_ref)->right;
			delete (*top_ref);
			(*top_ref) = temp;
		
		}
		//if node has left child no right then...
		else if ((*top_ref)->right == NULL)
		{
			temp = (*top_ref)->left;
			delete (*top_ref);
			(*top_ref) = temp;
		}
		else 
		{
			//if node has two children
			temp = (*top_ref)->right;
			bt_node* parent = NULL;
			//finds successor to node to be deleted and copies
			//and swaps values
			while (temp->left != NULL)
			{
				parent = temp;
				temp = temp->left;
			}
			(*top_ref)->data = temp->data;
			//deletes successor from tree
			if (parent != NULL)
			{
				remove(&parent->left, parent->left->data);
			}
			else
			{
				//if when going to find successor, we can't go left
				//then deletes node to right of node to be delete
				remove(&(*top_ref)->right, (*top_ref)->right->data);
			}

			
		}
	}
}

//sees if value looking for is in tree using recursion
bool contains(bt_node* top, int data) {
	bt_node* find = top;
	if (top == NULL)
	{
		return false;
	}
	else if (data == find->data)
	{
		return true;
	}
	else if (data < find->data)
	{
		return contains(find->left, data);
	}
	else
	{
		return contains(find->right, data);
	}
	return false;
}
//returns a pointer to a node with value stipulated
bt_node* get_node(bt_node* top, int data) {
	bt_node* find = top;
	if (top == NULL)
	{
		return NULL;
	}
	else if (data == find->data)
	{
		return find;
	}
	else if (data < find->data)
	{
		return get_node(find->left, data);
	}
	else
	{
		return get_node(find->right, data);
	}

	return NULL;

}
//returns an int with the size of the tree
int size(bt_node* top) {
	bt_node* rain = top;
	if ( top == NULL)
	{
		return 0;
	}
	else
	{
		int count = 1;
		count += size(rain->left);
		count += size(rain->right);
	return count;
	}
}
//inorder sort of tree
void in_order(bt_node* top, int array[], int* i){
	if (top != NULL)
	{
		
		in_order(top->left,array, i);
		array[*i] = top->data;
		(*i)++;
		in_order(top->right,array, i);
}
}
//sorts tree into array using inorder sort
void to_array(bt_node* top, int arr[]) {
	if (top == NULL)
	{
		return;
	}
	else 
	{
		int i = 0;
		in_order(top, arr, &i);
		
	}
	
			
}

