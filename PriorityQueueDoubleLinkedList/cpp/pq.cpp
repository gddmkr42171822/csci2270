//
// pq.cpp
//
// Decide how you want to implement this: linked list? heap? array?
// magic pixie dust? The choice is yours.
//
// NOTE: You will need to edit pq_struct.h as appropriate, depending
// on your implementation strategy. You will turn in this file (your
// implementation of everything) and pq_struct.h (your definition of
// the pq structure and any helper functions you might create).

// Your Name:Robert Werthman

#include <iostream>
using namespace std;
#include <string>
#include "pq.h"

pq* init_priority_queue()
{
	pq* new_pq = NULL;
	return new_pq;
}

pq* init_priority_queue1()
{
	//making a new pq struct
	pq* new_pq = new pq;
	//putting all the information into that struct
	new_pq->priority = 0;
	new_pq->text = "";
	//attaching the struct to nothing
	new_pq->next = NULL;
	new_pq->parent = NULL;
	//returning a pointer to that struct
	return new_pq;
}

/**
 * Insert the given text information into the queue with the specified
 * priority.
 *
 * Larger priority values have precedence. So if I add "foo" at
 * priority 5.0 and "bar" at priority 5.1, "bar" will be removed
 * before "foo".
 *
 * Priority values may be negative, zero, or positive.
 **/
void insert(pq* &queue, string &text, float priority) {
	
	//if the list is empty then start the pq and a pq* is not initialized to a init_priority_queue
	if( queue == NULL)
	{
		queue = init_priority_queue1();
		queue->text = text;
		queue->priority = priority;
		return;
	}
	//if a pq* has been initialized with init_priority_queue then this will be the first thing
	//else if ( queue->next == NULL && queue->parent == NULL && queue->priority == 0)
	//{
		//queue->text = text;
		//queue->priority = priority;
	//}
	//otherwise we are inserted into the beginning of a non-zero list
	//or in between nodes
	else
	{
		
		//if the new text has a greater priority than the text already at the beginning 
		//the new text is inserted before the original text
		if (priority > queue->priority && queue->parent == NULL)
		{
			pq* temp4 = init_priority_queue1();
			temp4->text = queue->text;
			temp4->priority = queue->priority;
			temp4->next = queue->next;
			queue->text = text;
			queue->priority = priority;
			queue->next = temp4;
			temp4->parent = queue;
			return;
		}
		else if(priority > queue->priority && queue->parent != NULL)
		{
			
			pq* temp2 = init_priority_queue1();
			temp2->text = queue->text;
			temp2->priority = queue->priority;
			temp2->next = queue->next;
			queue->text = text;
			queue->priority = priority;
			queue->next = temp2;
			temp2->parent = queue;
			
			
			return;
			
		}
		//if at the end of the list
		else if (priority < queue->priority && queue->parent != NULL && queue->next == NULL)
		{
			pq* temp3 = init_priority_queue1();
			temp3->text = text;
			temp3->priority = priority;
			queue->next = temp3;
			temp3->parent = queue;
			return;
			
		}
		else if (priority == queue->priority)
		{
			pq* temp9 = NULL;
			pq* temp8 = queue;
			do
			{
				temp8 = temp8->next;
			}
			while (priority == temp8->priority);
			
			temp9 = init_priority_queue1();
			temp9->text = temp8->text;
			temp9->priority = temp8->priority;
			temp9->next = temp8->next;
			temp9->parent = temp8;

			temp8->text = text;
			temp8->priority = priority;
			temp8->next = temp9;
			
		}
		else if(priority < queue->priority && queue->next != NULL)
		{
			return insert(queue->next, text, priority);
		}
	}
}

/**
 * Remove the highest priority element from the queue and return it.
 **/
string remove(pq* &queue) {
	pq* temp = queue;
	pq* temp1 = temp;
	//if the list is empty
	if ( queue == NULL)
	{
		return "Priority queue is empty";
	}
	//if the list has one item
	else if (queue->parent == NULL && queue->next == NULL)
	{
		string text = queue->text;
		queue = NULL;
		return text;
	}
	//otherwise remove the first element because the list should be sorted
	//in which the element with highest priority is at the beginning
	else
	{
		queue = queue->next;
		temp->next = NULL;
		queue->parent = NULL;
	}
  return temp1->text;
}

/**
 * Return the highest priority element in the queue but do not alter
 * the queue's membership.
 **/
string peek(pq* &queue) {
	if ( queue == NULL)
	{
		return "Nothing in List";
	}
	else
	{
		return queue->text;
	}
}
