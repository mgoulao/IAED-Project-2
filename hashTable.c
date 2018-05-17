#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "hashTable.h"

static GlobalTaskList *hashTableTaskLists;

static int M;

void HTinit(int m) {
	int i;
	M = m;
	hashTableTaskLists = (GlobalTaskList*)malloc(M * sizeof(GlobalTaskList));
	for (i = 0; i < M; i++) {
		hashTableTaskLists[i].head = NULL;
		hashTableTaskLists[i].tail = NULL;
	}
}

TaskList HTsearch(unsigned long int id) {
	int i = hash(id, M);
	return TLsearch(hashTableTaskLists[i].head, id);
}

void HTinsert(Task task) {
	int i = hash(key(task), M);
	hashTableTaskLists[i] = TLinsert(hashTableTaskLists[i].head, hashTableTaskLists[i].tail, task);
}

void HTdelete(long id) {
	int i = hash(id, M);
	TaskList current, previous = hashTableTaskLists[i].head;

	for (current = hashTableTaskLists[i].head; current->next; current = current->next,
		previous = current)
	{
		if (current->task->id == id)
		{
			if (!taskHasDependencies(current->task))
			{
				previous->next = current->next;

			}
			break;
		}
	}
}

void HTshow() {
	int i;
	for (i = 0; i < M; i++) {
		TLprint(hashTableTaskLists[i].head);
	}
}