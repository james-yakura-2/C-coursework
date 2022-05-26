/**********************************************************************
Program: Daily 6
Author: James Yakura
Date: 9/23/19
Time spent: 0:50
Purpose: The purpose of this program is to create a method to reverse a linked list in place.
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node Node;

struct node
{
	int data;
	Node* next;
};

//declare your function here.
Node* reverse(Node*);


int main(int argc, char* argv[])
{
	Node* head = NULL;
	int i;
	Node* temp;

	//set up a test list with values 9->8->7->...->0
	for (i = 0; i < 10; i++)
	{
		temp = (Node*)malloc(sizeof(Node));
		if (temp == NULL)
		{
			printf("out of memory?\n");
			exit(1);
		}
		temp->data = i;
		temp->next = head;
		head = temp;
	}

	//call your function to reverse the list (should work for any list given the head node).
	head=reverse(head);

	//print the reversed list.
	temp = head;
	while (temp != NULL)
	{
		printf("%d\n", temp->data);
		temp = temp->next;
	}

	return 0;
}

//Define your function here
Node* reverse(Node* head)
{
	Node* temp = head;
	Node* prev = NULL;
	while (temp != NULL)
	{
		Node* next = temp->next;
		temp->next = prev;
		prev = temp;
		temp = next;
	}
	return prev;
}