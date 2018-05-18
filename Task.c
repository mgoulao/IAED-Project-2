#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linkedList.h"

Task createTask(unsigned long id, char *description, unsigned long duration, TaskList idsHead)
{
	Task task = (Task)malloc(sizeof(struct task));
	task->id = id;
	strcpy(task->description, description);
	task->duration = duration;
	task->ids = idsHead;
	return task;
}

int taskHasBiggerDuration(Task task, unsigned long duration)
{
	return task->duration >= duration;
}

int criticalTask(Task task)
{
	return 1;
}

void listTask(Task task, int criticalPathValidation)
{
	printf("%lu \"%s\" %lu", task->id, task->description, task->duration);
	if (criticalPathValidation)
	{
		printf("[  ]");
	}
	TLprintId(task->ids);
}

int taskHasDependencies(Task task)
{
	int hasDependecies = 1;
	if (TLlength(task->ids) == 0)
	{
		hasDependecies = 0;
	}
	return hasDependecies;
}

int taskHasDependents(GlobalTaskList globalTaskList, Task task)
{
	int hasDependents = 1;
	TaskList dependentsHead = NULL;

	dependentsHead = getDependentTasks(globalTaskList, task->id);

	if (dependentsHead == NULL)
	{
		return 0;
	}

	if (!TLlength(dependentsHead))
		hasDependents = 0;

	return hasDependents;
}

TaskList getDependentTasks(GlobalTaskList globalTaskList, unsigned long id)
{
	TaskList p, dependeciePointer = NULL;
	struct taskListPointers dependentTasks;
	dependentTasks.head = NULL;
	dependentTasks.tail = NULL;

	for (p = globalTaskList.head; p; p = p->next)
	{
		dependeciePointer = TLsearch(p->task->ids, id);

		if (dependeciePointer)
		{
			dependentTasks = TLinsert(dependentTasks.head, dependentTasks.tail, p->task);
		}
	}
	return dependentTasks.head;
}