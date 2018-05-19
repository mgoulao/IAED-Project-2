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
	task->earlyStart = BIG_TASK_TIME;
	task->lateStart = BIG_TASK_TIME;
	return task;
}

int taskHasBiggerDuration(Task task, unsigned long duration)
{
	return task->duration >= duration;
}

int criticalTask(Task task)
{
	return task->earlyStart == task->lateStart;
}

void listTask(Task task, int criticalPathValidation)
{
	printf("%lu \"%s\" %lu", task->id, task->description, task->duration);
	if (criticalPathValidation)
	{
		if (task->earlyStart == task->lateStart)
		{
			printf(" [%lu %s]", task->earlyStart, "CRITICAL");
		}
		else
		{
			printf(" [%lu %lu]", task->earlyStart, task->lateStart);
		}
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

int taskHasDependents(TaskList head, Task task)
{
	TaskList dependentsHead = NULL;

	dependentsHead = getDependentTasks(head, task->id);

	if (dependentsHead == NULL)
	{
		return 0;
	}

	return 1;
}

TaskList getDependentTasks(TaskList head, unsigned long id)
{
	TaskList p, dependeciePointer = NULL;
	struct taskListPointers dependentTasks;
	dependentTasks.head = NULL;
	dependentTasks.tail = NULL;

	for (p = head; p; p = p->next)
	{
		dependeciePointer = TLsearch(p->task->ids, id);
		if (dependeciePointer)
		{
			dependentTasks = TLinsert(dependentTasks.head, dependentTasks.tail, p->task);
		}
	}

	return dependentTasks.head;
}