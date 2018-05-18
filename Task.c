#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linkedList.h"


Task createTask(unsigned long id, char *description, unsigned long duration, TaskList idsHead) {
	Task task = (Task) malloc(sizeof(struct task));
	task->id = id;
	strcpy(task->description,description);
	task->duration = duration;
	task->ids = idsHead;
	return task;
}

void listTask(TaskList head, int condition , int criticalPathValidation) {
	TaskList p;
	for (p = head; p; p = p->next)
	{
		printf("%lu \"%s\" %lu", p->task->id, p->task->description, p->task->duration);
		if(criticalPathValidation) {
			printf("[  ]")
		}
	}
	printf("\n");
} 

int taskHasDependencies(Task task) {
	int hasDependecies = 1;
	printf("%d\n", TLlength(task->ids));
	if (TLlength(task->ids) == 0) {
		hasDependecies = 0;
	}
	return hasDependecies;
}