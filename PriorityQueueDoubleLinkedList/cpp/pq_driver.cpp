//
// pq_driver.cpp
//
// This is an empty unit test file that you can implement (or not) to
// create unit tests for your code.
//
// You'll likely want one for insert, remove, and peek. Try to think
// about how your queue could break, and write tests that help you
// test your deepest priority-queue-related fears.
//
// The test code will appear on RetroGrade late in the game.

#include "UTFramework.h"
#include "pq.h"

using namespace Thilenius;

SUITE_BEGIN("Priority Queue")

TEST_BEGIN("SanityCheck")
{
  IsTrue("Sane?", true, "OK I'm insane");
}TEST_END


TEST_BEGIN("Insert negative numbers and 0")
{
	
	pq* root = NULL;
	string text5 = "hello";
	insert(root, text5, 0);
	string text = "fuck this";
	float priority = 1.1;
	insert(root , text , priority);
	float priority1 = 1.2;
	string text1 = "you know it";
	insert(root, text1, priority1); 
	float priority2 = 1.3;
	string text2 = "sua sponte";
	insert(root, text2, priority2);
	float priority3 = 1.0;
	string text3 = "no way";
	insert(root, text3, priority3);
	float priority4 = 1.13;
	string text4 = "shit";
	insert(root, text4, priority4);
	IsTrue("the priority of the first node is 1.3", root->priority == 1.3f, "faile");
	IsTrue("The priority of the third node is 1.13", root->next->next->priority == 1.13f, "fail");
	IsTrue("The text of the third node is 'shit'", root->next->next->text.compare(text4) == 0, "fail");
	IsTrue("The priority of the fourth node is 1.1", root->next->next->next->priority == 1.1f, "fail");
	IsTrue("The priority of the second to last node is 1.0 ", root->next->next->next->next->priority == 1.0f, "fail");
	IsTrue("the next pointer to the last node is not null", root->next->next->next->next->next != NULL, "fail");
	IsTrue("the last node priority is 0", root->next->next->next->next->next->priority == 0, "fail");
	float priority6 = -2.3f;
	insert(root, text4, priority6);
	IsTrue("the priority of the last node is -2.3", root->next->next->next->next->next->next->priority == -2.3f, "fail");
}TEST_END

TEST_BEGIN("Insert the same value")
{
	pq* root = NULL;
	string text5 = "hello";
	insert(root, text5, 0);
	string text = "fuck this";
	float priority = 1.1;
	insert(root , text , priority);
	float priority1 = 1.2;
	string text1 = "you know it";
	insert(root, text1, priority1); 
	float priority2 = 1.3;
	string text2 = "sua sponte";
	insert(root, text2, priority2);
	float priority3 = 1.0;
	string text3 = "no way";
	insert(root, text3, priority3);
	float priority4 = 1.13;
	string text4 = "shit";
	insert(root, text4, priority4);
	float priority6 = -2.3f;
	insert(root, text4, priority6);
	insert(root, text3, priority2);
	IsTrue("the priority of the first node is 1.3", root->priority == 1.3f, "fail");
	IsTrue("the priority of the second node is 1.3", root->next->priority ==1.3f, "fail");
	IsTrue("the next pointers priority is 1.2", root->next->next->priority == 1.2f, "fail");
	
}TEST_END


TEST_BEGIN("Insert into empy list")
{
	pq* root = NULL;
	string text = "hello";
	insert(root, text, 1.1f);
	IsTrue("root priority is 1.1", root->priority == 1.1f, "fail");
	IsTrue("root text is hello", root->text.compare(text) == 0,"fail");
	IsTrue("root next is null", root->next == NULL, "fail");
	IsTrue("root parent is null", root->parent == NULL, "fail");
	
	
}TEST_END


TEST_BEGIN("Initial node insert")
{
	
	pq* root = init_priority_queue();
	float priority = 1.1;
	string text = "fuck this";
	insert(root , text , priority);
	IsTrue("The priority of the first node is 1.1", root->priority == 1.1f, "fail");
	IsTrue("The text of the first node is fuck this", root->text.compare(text) == 0, "fail");
	IsTrue("The next pointer should be null", root->next == NULL, "fail");
	IsTrue("the parent pointer should be null", root->parent == NULL, "fail");
}TEST_END

TEST_BEGIN("Second node test insert")
{
	pq* root = init_priority_queue();
	string text = "fuck this";
	float priority = 1.1;
	insert(root , text , priority);
	float priority1 = 1.2;
	string text1 = "you know it";
	insert(root, text1, priority1); 
	IsTrue("The priority of the first node is 1.2", root->priority == 1.2f, "fail");
	IsTrue("The text of the first node is 'you know it'", root->text.compare(text1) == 0, "fail");
	IsTrue("The next pointer should not be null", root->next != NULL, "fail");
	IsTrue("The priority of the second node is 1.1", root->next->priority == 1.1f, "fail");
	IsTrue("The next pointer of second node should be null", root->next->next == NULL, "fail");
	IsTrue("the parent pointer of the second node should not be null", root->next->parent != NULL, "fail");
}TEST_END

TEST_BEGIN("Third node test insert")
{
	string text = "fuck this";
	pq* root = init_priority_queue();
	float priority = 1.1;
	insert(root , text , priority);
	float priority1 = 1.2;
	string text1 = "you know it";
	insert(root, text1, priority1); 
	float priority2 = 1.3;
	string text2 = "sua sponte";
	insert(root, text2, priority2);
	IsTrue("The priority of the first node is 1.3", root->priority == 1.3f, "fail");
	IsTrue("The text of the first node is 'sua sponte'", root->text.compare(text2) == 0, "fail");
	IsTrue("The next pointer should not be null", root->next != NULL, "fail");
	IsTrue("The priority of the second node is 1.2", root->next->priority == 1.2f, "fail");
	IsTrue("The next pointer of second node should not be null", root->next->next != NULL, "fail");
	IsTrue("the third priority should be 1.1", root->next->next->priority == 1.1f, "fail");
	IsTrue("the third node next is null", root->next->next->next == NULL, "fail");
	IsTrue("the third node parent is not null", root->next->next->parent != NULL, "fail");
	
}TEST_END


TEST_BEGIN("fourth node test insert")
{
	string text = "fuck this";
	pq* root = init_priority_queue();
	float priority = 1.1;
	insert(root , text , priority);
	float priority1 = 1.2;
	string text1 = "you know it";
	insert(root, text1, priority1); 
	float priority2 = 1.3;
	string text2 = "sua sponte";
	insert(root, text2, priority2);
	float priority3 = 1.0;
	string text3 = "no way";
	insert(root, text3, priority3);
	IsTrue("The priority of the last node is 1.0", root->next->next->next->priority == 1.0f, "fail");
	IsTrue("The text of the last node is 'no way'", root->next->next->next->text.compare(text3) == 0, "fail");
	IsTrue("The priority of the first node is 1.3", root->priority == 1.3f, "fail");
	IsTrue("The text of the first node remains you know it ", root->text.compare(text2) == 0, "fail");
	IsTrue("the next pointer of last node is null", root->next->next->next->next == NULL, "fail");

}TEST_END


TEST_BEGIN("Insert node between nodes")
{
	string text = "fuck this";
	pq* root = init_priority_queue();
	float priority = 1.1;
	insert(root , text , priority);
	float priority1 = 1.2;
	string text1 = "you know it";
	insert(root, text1, priority1); 
	float priority2 = 1.3;
	string text2 = "sua sponte";
	insert(root, text2, priority2);
	float priority3 = 1.0;
	string text3 = "no way";
	insert(root, text3, priority3);
	float priority4 = 1.13;
	string text4 = "shit";
	insert(root, text4, priority4);
	IsTrue("the priority of the first node is 1.3", root->priority == 1.3f, "faile");
	IsTrue("The priority of the third node is 1.13", root->next->next->priority == 1.13f, "fail");
	IsTrue("The text of the third node is 'shit'", root->next->next->text.compare(text4) == 0, "fail");
	IsTrue("The priority of the fourth node is 1.1", root->next->next->next->priority == 1.1f, "fail");
	IsTrue("The priority of the last node is 1.0 ", root->next->next->next->next->priority == 1.0f, "fail");
	IsTrue("the next pointer of last node is null", root->next->next->next->next->next == NULL, "fail");
	 
}TEST_END

TEST_BEGIN("Remove from empty list and initialized list with no priority and text")
{
	pq* root = init_priority_queue();
	string test1 = "Priority queue is empty";
	string test = remove(root);
	IsTrue("Removing from empty list works", test.compare(test1) == 0, "fail");
	
}TEST_END

TEST_BEGIN("Remove one top priority from list of 4")
{
	string text = "fuck this";
	pq* root = init_priority_queue();
	float priority = 1.1;
	insert(root , text , priority);
	float priority1 = 1.2;
	string text1 = "you know it";
	insert(root, text1, priority1); 
	float priority2 = 1.3;
	string text2 = "sua sponte";
	insert(root, text2, priority2);
	float priority3 = 1.0;
	string text3 = "no way";
	insert(root, text3, priority3);	
	string test = remove(root);
	IsTrue("Top priority value text was returned", test.compare(text2) == 0, "fail");
	IsTrue("Top priority struct was deleted from list", root->priority == priority1, "fail");
	IsTrue("Top priority parent is NULL", root->parent == NULL, "fail");
}TEST_END

TEST_BEGIN("Remove two priorities from list of 4")
{
	string text = "fuck this";
	pq* root = init_priority_queue();
	float priority = 1.1;
	insert(root , text , priority);
	float priority1 = 1.2;
	string text1 = "you know it";
	insert(root, text1, priority1); 
	float priority2 = 1.3;
	string text2 = "sua sponte";
	insert(root, text2, priority2);
	float priority3 = 1.0;
	string text3 = "no way";
	insert(root, text3, priority3);	
	string test = remove(root);
	IsTrue("Top priority value text was returned", test.compare(text2) == 0, "fail");
	IsTrue("Top priority struct was deleted from list", root->priority == priority1, "fail");
	IsTrue("Top priority now points to a different priority", root->next->priority == 1.1f, "fail");
	string test1 = remove(root);
	IsTrue("Second Top priority value text was returned", test1.compare(text1) == 0, "fail");
	IsTrue("Second Top priority struct was deleted from list", root->priority == priority, "fail");
}TEST_END

TEST_BEGIN("Peek after removing one element")
{
	string text = "fuck this";
	pq* root = init_priority_queue();
	float priority = 1.1;
	insert(root , text , priority);
	float priority1 = 1.2;
	string text1 = "you know it";
	insert(root, text1, priority1); 
	float priority2 = 1.3;
	string text2 = "sua sponte";
	insert(root, text2, priority2);
	float priority3 = 1.0;
	string text3 = "no way";
	insert(root, text3, priority3);	
	string test = remove(root);
	string test1 = peek(root);
	IsTrue("Peek is working properly", text1.compare(test1) == 0, "false");
}TEST_END



SUITE_END

int main (int argc, char* argv[])
{	
  UTFrameworkInit;
}
