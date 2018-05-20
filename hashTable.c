#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "hashTable.h"

static GlobalTaskList *hashTableTaskLists;

static int M;

/*
 * Function:  HTinit 
 * --------------------
 * Initialize the HashTable with a size of m
 * 
 * m: size of the HashTable
 */
void HTinit(int m)
{
	int i;
	M = m;
	hashTableTaskLists = (GlobalTaskList *)malloc(M * sizeof(GlobalTaskList));
	for (i = 0; i < M; i++)
	{
		hashTableTaskLists[i].head = NULL;
		hashTableTaskLists[i].tail = NULL;
	}
}

/*
 * Function:  HTsearch 
 * --------------------
 * Search for a Task with a given Id and returns the node Pointer
 * 
 * id: Requested Task id
 */
TaskList HTsearch(unsigned long int id)
{
	int i = hash(id, M);
	return TLsearch(hashTableTaskLists[i].head, id);
}

/*
 * Function:  HTinsert 
 * --------------------
 * Insert the Task to the HashTable
 * 
 * task: The task to insert
 */
void HTinsert(Task task)
{
	int i = hash(key(task), M);
	hashTableTaskLists[i] = TLinsert(hashTableTaskLists[i].head, hashTableTaskLists[i].tail, task);
}

/*
 * Function:  HTdelete 
 * --------------------
 * Deletes the Task from  HashTable
 * 
 * id: Id of the Task to delete
 */
void HTdelete(unsigned long id)
{
	int i = hash(id, M);
	TaskList current, previous;

	for (current = hashTableTaskLists[i].head, previous = NULL; current; previous = current,
		current = current->next)
	{
		if (current->task->id == id)
		{
			if (previous == NULL)
			{
				hashTableTaskLists[i].head = current->next;
			}
			else
			{
				if (current->next == NULL)
				{
					hashTableTaskLists[i].tail = previous;
					hashTableTaskLists[i].tail->next = NULL;
				}
				previous->next = current->next;
			}
			free(current);
			break;
		}
	}
}