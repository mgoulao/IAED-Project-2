#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedList.h"
#include "hashTable.h"

void TLprintId(TaskList head)
{
	TaskList p;
	for (p = head; p; p = p->next)
	{
		printf(" %lu", p->task->id);
	}
	printf("\n");
}

void TLprint(TaskList head, char condition, unsigned long duration, int criticalPathValidation)
{
	TaskList p;
	for (p = head; p; p = p->next)
	{
		if (condition == 'd' && taskHasBiggerDuration(p->task, duration))
		{
			listTask(p->task, criticalPathValidation);
		}
		else if (condition == 'c' && criticalTask(p->task))
		{
			listTask(p->task, criticalPathValidation);
		}
	}
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

GlobalTaskList TLTaskdelete(GlobalTaskList globalTaskList, unsigned long id)
{
	TaskList current, previous;
	int exist = 0;

	for (current = globalTaskList.head, previous = NULL; current; previous = current,
		current = current->next)
	{

		if (current->task->id == id)
		{
			exist = 1;

			if (taskHasDependents(globalTaskList, current->task))
			{
				printf("%s\n", "task with dependencies");
			}
			else
			{
				if (previous == NULL)
				{
					globalTaskList.head = current->next;
				}
				else
				{
					
					if (current->next == NULL)
					{
						globalTaskList.tail = previous;
						globalTaskList.tail->next = NULL;
					}
					previous->next = current->next;
				}
				free(current->task);
				free(current);
				HTdelete(id);
			}
			break;
		}
	}

	if (!exist)
		printf("%s\n", "no such task");
	return globalTaskList;
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

	if (head == NULL)
	{
		return 0;
	}
	for (current = head; current; current = current->next)
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

}*/