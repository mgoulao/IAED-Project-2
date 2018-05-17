#include <stdlib.h>
#include <string.h>
#include "linkedList.h"


Task createTask(unsigned long id, char *description, unsigned long duration, TaskList idsHead) {
	Task task = (Task) malloc(sizeof(struct task));
	task->id = id;
	strcpy(task->description,description);
	task->duration = duration;
	task->ids = idsHead;
	return task;
}

int taskHasDependencies(Task task) {
	int hasDependecies = 1;
	if (sizeof(task->ids) == 0) {
		hasDependecies = 0;
	}
	return hasDependecies;
}