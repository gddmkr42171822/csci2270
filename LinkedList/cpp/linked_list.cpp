/*

  linked_list.cpp

  <document your work here: explain what it does from a high level.>
  * This program has 9 functions that deal with nodes and the data struture: linked lists.  

 */

// AUTHOR: Robert Werthman
          
// WHAT: CSCI 2270 Assignment 1

// COLLABORATORS: <List of EVERYBODY you worked with, including
// instructors, TAs, and other students. Include people you helped.>
// TA: Nathaniel Pohl
// Other Students: Jane Lockshin, other people with names I don't remember
// <List of EVERY WEB SITE you consulted substantially> <Don't worry!
// Collaboration is encouraged. This is not cheating.>
/*
http://www.codeproject.com/Articles/24684/How-to-create-Linked-list-using-C-C
http://www.cprogramming.com/tutorial/lesson15.html
http://en.allexperts.com/q/C-1040/c-programming.htm
http://geekswithblogs.net/MarkPearl/archive/2010/02/20/linked-lists-in-c.aspx
*/
// include the header file that provides function prototypes and the
// node structure. When you turn in your assignment, the grading
// system will use its own copy of this file, so don't edit it, and
// implement all the functions it specifies.
#include "linked_list.h"

// sstream gives you the stringstream object. Google it, and admire
// how much easier this makes life.
#include <sstream>

using namespace std;


// your linked list implementation goes here :)

// create a new node structure that points to NULL and holds the
// provided integer. return a pointer to that new node.
node* init_node(int data) {
	node* new_node = new node;//setting up a node pointer and allocating memory to it for a node
	new_node->data = data;//filling in value slot of node with data
	new_node->next = NULL;//pointing the node to null
	
  return new_node; // change this to return a newly initialized node.
}

// create a space-separated string representing the contents of the
// list, in the same order they are found beginning from the head of
// the list. return that string object.  For example, this might
// return "" (the empty string) if the list is empty, or it might
// return "1 7 3" or "1 7 3 " (note the space at the end, you can have
// that there and it is OK).
std::string report(node* root) {
	stringstream listcontents;//setting up a string to hold list contents
	node* traverse = root;//setting a new node pointer to root
	while (traverse != NULL)//using while loop to iterate through list
	{
		listcontents << traverse->data;//inputting into string, data from the nodes that traverse points to
		listcontents << ' ';//inputing space into string after each piece of data
		traverse = traverse->next;//moving traverse to next node
		}
  return listcontents.str(); // change this to return a proper string, 
               // even if it is a zero-length string object.
}

// insert an integer into the list pointed to by head. the resulting
// list is one element longer, and the newly appended node has the
// given data value. consider using the 'append' function to help.
void append_data(node** head, int data) {
	node* ptr = init_node(data);//making a node pointer that uses init_node function to create a new node with given data
	append(head, ptr);//using the append function to insert that node into where head is pointing
}

// this is the same as append_data, except we're adding a node, rather
// than a value. 
void append(node** head, node* new_node) {
	if (*head == NULL)//if head is pointing to a pointer with no value
	{
		*head = new_node;//adding a new node to that pointer
		}
	else//if head is not pointing to a pointer with no value then..
	{
	node* ptr = *head;//set up a new pointer that is pointing to the value in the pointer head is pointing to
		while (ptr->next != NULL)//using thaT pointer to iterate through nodes until one with a next = NULL
			ptr = ptr->next;//moving the pointer to the next node using the while loop
	ptr->next = new_node;//if pointer comes across NULL then it is set equal to new_node
	}	
}

// similar to append_data. insert a new node that contains the given
// data value, such that the new node occupies the offset
// indicated. Any nodes that were already in the list at that offset
// and beyond are shifted down by one. For example if the list
// contains 23, 74, 93, and we insert 42 at index 1, the resulting
// list should be 23, 42, 74, 93.
void insert_data(node** head, int offset, int data) {
	node* ptr = init_node(data);//making a new node using the init_node function
	insert(head, offset, ptr);//using the insert function to insert new node at offset location
}

// this is the same as insert_data, except we're inserting a node,
// rather than a value.
void insert(node** head, int offset, node* new_node) {
	node* temp = *head;//making a node pointer that is looking at what head is looking at
	if (offset == 0)//checking to make sure node is inserted before first node in list
	{
		new_node->next = temp;//setting the new_node link to the first node's address or in this case *head
		*head = new_node;//setting *head to the new_node's address
	}
	else if (temp == NULL)//if temp isn't looking at anything, so no nodes in list then you can't offset anything
	{
		cout << "ERROR " << endl;
 	}
	else
	{
		for (int j = 0; j < (offset-1); j++){//using for loop to move through nodes according to offset
			temp = temp->next;}//moving temp pointer through nodes
		new_node->next = temp->next;//setting new_node link to node after temp
		temp->next = new_node;//connect the node temp is looking at to new_node
	}
	


}

// remove the node indicated by the given offset. For example if our
// list contains 23, 74, 93, and we remove offset 1, the resulting
// list should then contain 23, 93.
void remove(node** parent, int offset) {
	node* temp = new node;//making new node pointer
	temp = *parent;//setting it equal to *parent which is the address of the first node
	node* old_temp = new node;//making another node pointer
	if (*parent == NULL){//checking if there isn't a first node
		cout << "Not going to work." << endl;}
	else if (offset == 0){//checking if the first node needs to be deleted
		*parent = temp->next;//setting *parent equal to the second node
		delete temp;//deleting the first node
		
	}
	else
		{
		for ( int i = 0; i < (offset); i++){//looping through nodes to offset location
			old_temp = temp;//moving old_temp with temp pointer but leaving it equal to one node before
			temp = temp->next;}//moving temp pointer through nodes
		old_temp->next = temp->next;//setting the node before temp to the node right after temp
		delete temp;}//deleting temp
		
		
			
	
}

// report the number of nodes in the linked list pointed to by head.
int size(node* head) {
	node* temp = head;//setting a node pointer equal to head or beginning of list
	int i = 0;//setting up a counter to keep track of nodes in list
	while (temp != NULL){//going through list
		i += 1;//adding one to counter after each node
		temp = temp->next;//moving temp pointer through list
	}

  return i;//returning the counter
}

// return true if the linked list pointed to by head contains a node
// with the specified value.
bool contains(node* head, int data) {
	node* value = head;//setting up a node pointer equal to head
	while (value != NULL)//looping through nodes with pointer
	{
		if (value->data == data)//if the value in the node is the value we are looking for then function returns true
		{
			return true;
		}
		value = value->next;//moving pointer through nodes
	}
	

	
  return false;//if the data is not in the linked list or there are no nodes then false is returned
}
