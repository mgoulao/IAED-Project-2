#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linkedList.h"

/*
 * Function:  createTask 
 * --------------------
 * Creates a new task and returns its pointer
 * 
 * id: id of the new task
 * description: description of the new task
 * duration: duration of the new task
 * idsHead: TaskList with the dependecies of the new task
 */
Task createTask(unsigned long id, char *description, unsigned long duration, TaskList idsHead)
{
	Task task = (Task)malloc(sizeof(struct task));
	task->id = id;
	task->description = (char*) malloc((strlen(description) + 1) * sizeof(char));
	strcpy(task->description, description);
	task->duration = duration;
	task->ids = idsHead;
	task->earlyStart = BIG_TASK_TIME;
	task->lateStart = BIG_TASK_TIME;
	return task;
}

/*
 * Function:  taskHasBiggerDuration 
 * --------------------
 * Returns 1 if the task has a duration bigger or equal to the given duration
 * 
 * task: Pointer to the task
 * duration: duration used to compare
 */
int taskHasBiggerDuration(Task task, unsigned long duration)
{
	return task->duration >= duration;
}

/*
 * Function:  criticalTask 
 * --------------------
 * Returns 1 if the task belongs to the critical Path
 * 
 * task: Pointer to the task
 */
int criticalTask(Task task)
{
	return task->earlyStart == task->lateStart;
}

/*
 * Function:  listTask 
 * --------------------
 * Prints the Task 
 * If the critical Path is valid <id> <descrição> <duração> [<early> <late>] <ids>
 * Otherwise <id> <descrição> <duração> <ids>
 * 
 * task: Pointer to the task
 * criticalPathValidation: flag used to know if the critical path is valid
 */
void listTask(Task task, int criticalPathValidation)
{
	printf("%lu \"%s\" %lu", task->id, task->description, task->duration);
	if (criticalPathValidation)
	{
		if (task->earlyStart == task->lateStart)
			printf(" [%lu %s]", task->earlyStart, "CRITICAL");
		else
			printf(" [%lu %lu]", task->earlyStart, task->lateStart);
	}
	TLprintId(task->ids);
}

/*
 * Function:  taskHasDependencies 
 * --------------------
 * Returns 1 if the task as dependencies
 * 
 * task: Pointer to the task
 */
int taskHasDependencies(Task task)
{
	int hasDependecies = 1;
	if (TLlength(task->ids) == 0)
		hasDependecies = 0;

	return hasDependecies;
}

/*
 * Function:  taskHasDependencies 
 * --------------------
 * Returns 1 if the task as dependents (successors)
 * 
 * head: Pointer for the first element of the TaskList
 * task: Pointer to the task
 */
int taskHasDependents(TaskList head, Task task)
{
	TaskList p, dependeciePointer = NULL;

	for (p = head; p; p = p->next)
	{
		dependeciePointer = TLsearch(p->task->ids, task->id);
		if (dependeciePointer)
			return 1;
	}

	return 0;
}

/*
 * Function:  taskHasDependencies 
 * --------------------
 * Returns a TaskList with dependent task
 * 
 * head: Pointer for the first element of the TaskList
 * id: id of the task 
 */
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
			dependentTasks = TLinsert(dependentTasks.head, dependentTasks.tail, p->task);
	}

	return dependentTasks.head;
}