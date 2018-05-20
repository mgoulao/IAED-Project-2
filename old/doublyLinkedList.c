#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedList.h"
#include "hashTable.h"

/*
 * Function:  TLprintId 
 * --------------------
 * Prints all tasks Id from TaskList by insertion order 
 * 
 * head: Pointer for the first element of the TaskList
 */
void TLprintId(TaskList head)
{
	TaskList p;
	for (p = head; p; p = p->next)
	{
		printf(" %lu", p->task->id);
	}
	printf("\n");
}

/*
 * Function:  TLprint 
 * --------------------
 * Prints all tasks from TaskList by insertion order, that check the given condition 
 * 
 * head: Pointer for the first element of the TaskList
 * condition: Selects the condition
 * duration: minimum duration that a task must have to be printed
 * criticalPathValidation: flag used to know if the critical path is valid
 */
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
		else if (condition == 'a')
		{
			listTask(p->task, criticalPathValidation);
		}
	}
}

/*
 * Function:  TLprintId 
 * --------------------
 * Prints all task Id from TaskList by insertion order 
 * 
 * head: Pointer for the first element of the TaskList
 */
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
		link->prev = NULL;
	}
	else
	{
		tail->next = link;
		link->prev = tail;
		tail = link;
		link->task = task;
		link->next = NULL;
	}

	listPointers.head = head;
	listPointers.tail = tail;
	return listPointers;
}

/*
 * Function:  TLTaskdelete 
 * --------------------
 * Deletes a given Task from the TaskList 
 * 
 * globalTaskList: struct with Pointers to the beginning and end of the TaskList
 * id: ID of the Task to delete
 */
GlobalTaskList TLTaskdelete(GlobalTaskList globalTaskList, unsigned long id)
{
	TaskList current;

	current = HTsearch(id);

	if (current)
	{
		if (taskHasDependents(globalTaskList.head, current->task))
		{
			printf("%s\n", "task with dependencies");
		}
		else
		{
			printf("desc -- %s prev -- %lu next -- %lu \n", current->task->description, current->prev, current->next);
			if (current->prev == NULL)
			{
				printf("first");
				globalTaskList.head = current->next;
				if(current->next)
					current->next->prev = NULL;
			}
			else
			{
				if (current->next == NULL)
				{
					printf("last");
					globalTaskList.tail = current->prev;
					globalTaskList.tail->next = NULL;
				} else 
					current->next->prev = current->prev;
				current->prev->next = current->next;
			}
			globalTaskList.criticalPathValidation = 0;
			
			/*HTdelete(id);*/
			/*free(current->task->description);
			free(current->task);*/
			free(current);
			
		}
	}
	else
		printf("%s\n", "no such task");

	return globalTaskList;
	/*
	TaskList current, previous;
	int exist = 0;

	for (current = globalTaskList.head, previous = NULL; current; previous = current,
		current = current->next)
	{

		if (current->task->id == id)
		{
			exist = 1;

			if (taskHasDependents(globalTaskList.head, current->task))
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
				globalTaskList.criticalPathValidation = 0;
				free(current->task->description);
				free(current->task);
				free(current);
				HTdelete(id);
			}
			break;
		}
	}

	if (!exist)
		printf("%s\n", "no such task");*/
	return globalTaskList;
}

/*
 * Function:  TLdelete 
 * --------------------
 * Deletes a given TaskList, but not the Tasks
 * 
 * head: Pointer for the first element of the TaskList
 */
void TLdelete(TaskList head)
{
	TaskList current;

	if (TLlength(head) > 0)
	{
		while (head)
		{
			current = head;
			head = current->next;

			free(current);
		}
	}
}

/*
 * Function:  TLdelete 
 * --------------------
 * Checks if the TaskList is empty
 * 
 * head: Pointer for the first element of the TaskList
 */
int TLisEmpty(TaskList head)
{
	return head == NULL;
}

/*
 * Function:  TLlength 
 * --------------------
 * Returns the TaskList length
 * 
 * head: Pointer for the first element of the TaskList
 */
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

/*
 * Function:  TLsearch 
 * --------------------
 * Returns a Pointer to the position of the node with the requested Task
 * 
 * head: Pointer for the first element of the TaskList
 * id: Id of the requested Task
 */
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
 * Function:  ResetTasksLateStart 
 * --------------------
 * Sets Late Start to BIG_TASK_TIME to all Tasks of the TaskList
 * 
 * head: Pointer for the first element of the TaskList
 */
void ResetTasksLateStart(TaskList head)
{
	TaskList p;

	for (p = head; p; p = p->next)
	{
		/*p->task->earlyStart = BIG_TASK_TIME;*/
		p->task->lateStart = BIG_TASK_TIME;
	}
}

/*
 * Function:  TLcalculateDuration 
 * --------------------
 * Calculates Path duration and the earlyStart of the Task inside the node
 * 
 * node: Pointer for the node with the Task
 */
unsigned long TLcalculateDuration(TaskList node)
{
	unsigned long biggerTime = 0, currentTime = 0;
	TaskList p;
	if (TLisEmpty(node->task->ids))
	{
		node->task->earlyStart = 0;
		return node->task->duration;
	}
	if (node->task->earlyStart != BIG_TASK_TIME)
	{
		return node->task->earlyStart + node->task->duration;
	}
	for (p = node->task->ids; p; p = p->next)
	{
		currentTime = TLcalculateDuration(p);
		if (biggerTime < currentTime)
		{
			biggerTime = currentTime;
		}
	}

	node->task->earlyStart = biggerTime;
	return biggerTime + node->task->duration;
}

/*
 * Function:  TLcalculateLateStart 
 * --------------------
 * Calculates the lateStart of the Task inside the node
 * 
 * node: Pointer for the node with the Task
 * duration: lateStart of the successor or the Path duration
 */
void TLcalculateLateStart(TaskList node, unsigned long duration)
{
	TaskList p;
	if (TLisEmpty(node->task->ids) && duration - node->task->duration <= node->task->lateStart)
	{
		node->task->lateStart = duration - node->task->duration;
	}
	else if (duration - node->task->duration <= node->task->lateStart)
	{
		node->task->lateStart = duration - node->task->duration;
		/*printf("--- id -- %lu -- early -- %lu -- late .. %lu \n", node->task->id, node->task->earlyStart, node->task->lateStart);*/

		for (p = node->task->ids; p; p = p->next)
			TLcalculateLateStart(p, duration - node->task->duration);
	}
}

/*
 * Function:  TLcalculateTasksTimes 
 * --------------------
 * Calculates lateStart and earlyStart for all Tasks
 * and returns the Path duration
 * 
 * head: Pointer for the first element of the TaskList
 */
int TLcalculateTasksTimes(TaskList head)
{
	unsigned long duration = 0, currentTime;
	TaskList p;
	/*Calculate Early Start*/
	for (p = head; p; p = p->next)
	{
		if (!taskHasDependents(head, p->task))
		{
			/*printf("--- end --- id-- %lu \n", p->task->id);*/
			currentTime = TLcalculateDuration(p);
			if (currentTime > duration)
			{
				duration = currentTime;
				ResetTasksLateStart(head);
			}
		}
	}

	/*Calculate Late Start*/
	for (p = head; p; p = p->next)
	{
		if (!taskHasDependents(head, p->task))
			TLcalculateLateStart(p, duration);
	}

	return duration;
}