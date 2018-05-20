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
 * Function:  TLinsert 
 * --------------------
 * Inserts a Task in a TaskList
 * 
 * head: Pointer to the first element of the TaskList
 * tail: Pointer to the last element of the TaskList
 * task: Pointer to the task 
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

/*
 * Function:  TLdelete 
 * --------------------
 * Deletes a given TaskList, but not the Tasks
 * 
 * head: Pointer to the first element of the TaskList
 */
void TLdelete(TaskList head)
{
	TaskList current;

	if (!TLisEmpty(head))
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
 * Deletes a given TaskList, but not the Tasks
 * 
 * head: Pointer to the first element of the TaskList
 */
void TLdeleteAllTasks(GlobalTaskList globalTaskList)
{
	if (!TLisEmpty(globalTaskList.head))
	{
		while (globalTaskList.head)
		{
			globalTaskList = deleteTask(globalTaskList, globalTaskList.head->task->id, NOT_CHECK_DEPENDECIES);
		}
	}
}

/*
 * Function:  TLdelete 
 * --------------------
 * Checks if the TaskList is empty
 * 
 * head: Pointer to the first element of the TaskList
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
 * head: Pointer to the first element of the TaskList
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
 * head: Pointer to the first element of the TaskList
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
 * head: Pointer to the first element of the TaskList
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
 * node: Pointer to the node with the Task
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
 * node: Pointer to the node with the Task
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
 * head: Pointer to the first element of the TaskList
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