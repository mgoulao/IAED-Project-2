#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedList.h"

void TLprint(TaskList head)
{
	TaskList p;
	for (p = head; p; p = p->next)
	{
		printf("%s - ", p->task->description);
	}
	printf("\n");
}

GlobalTaskList TLinsert(TaskList head, TaskList tail, Task task)
{
	GlobalTaskList listPointers;
	TaskList link = (TaskList)malloc(sizeof(struct node));

	if (!head)
	{
		head = link;
		tail = link;
		link->task = task;
		link->next = NULL;
	}
	else
	{
		tail->next = link;
		tail = link;
		link->task = task;
		link->next = NULL;
	}

	listPointers.head = head;
	listPointers.tail = tail;
	return listPointers;
}

void TLdeleteAndFree(TaskList head, unsigned long id)
{
	TaskList current, previous;
	int exist = 0;

	for (current = head->next, previous = head; current->next; current = current->next,
		previous = current)
	{
		if (current->task->id == id)
		{
			exist = 1;
			if (taskHasDependencies(current->task))
			{
				printf("%s\n", "task with dependencies");
			}
			else
			{
				previous->next = current->next;
				free(current);
			}
			break;
		}
	}

	if (!exist)
	{
		printf("%s\n", "no such task");
	}
}

void TLdelete(TaskList head)
{
	TaskList current, previous;
	
	if (TLlength(head) > 0)
	{
		for (current = head->next, previous = head; current->next; current = current->next,
			previous = current)
		{

			previous->next = current->next;

			break;
		}
	}
}

int TLisEmpty(TaskList head)
{
	return head == NULL;
}

int TLlength(TaskList head)
{
	int length = 0;
	struct node *current;

	for (current = head; current != NULL; current = current->next)
	{
		length++;
	}

	return length;
}

TaskList TLsearch(TaskList head, unsigned long id)
{

	TaskList current = head;

	if (head == NULL)
	{
		return NULL;
	}

	while (current->task->id != id)
	{

		if (current->next == NULL)
		{
			return NULL;
		}
		else
		{
			current = current->next;
		}
	}

	return current;
}
/*
TaskList TLdelete(int key) {

   struct node* current = head;
   struct node* previous = NULL;

   if (head == NULL) {
	return NULL;
   }

   while (current->key != key) {

	if (current->next == NULL) {
	   return NULL;
	} else {
	   previous = current;
	   current = current->next;
	}
   }

   if (current == head) {
	head = head->next;
   } else {
	previous->next = current->next;
   }

   return current;
}

void TLsort() {

   int i, j, k, tempKey, tempData;
   struct node *current;
   struct node *next;

   int size = length();
   k = size ;

   for ( i = 0 ; i < size - 1 ; i++, k-- ) {
	current = head;
	next = head->next;

	for ( j = 1 ; j < k ; j++ ) {

	   if ( current->data > next->data ) {
		tempData = current->data;
		current->data = next->data;
		next->data = tempData;

		tempKey = current->key;
		current->key = next->key;
		next->key = tempKey;
	   }

	   current = current->next;
	   next = next->next;
	}
   }
}*/