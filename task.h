#ifndef _TASK_
#define _TASK_

typedef struct task *Task;
typedef struct node *TaskList;

struct task
{
	int numberOfDependents;
	unsigned long id, duration, earlyStart, lateStart;
	char *description;
	TaskList ids;
};

struct node
{
	Task task;
	struct node *next;
};

typedef struct taskListPointers
{
	TaskList head, tail;
	int criticalPathValidation;
} GlobalTaskList;

Task createTask(unsigned long id, char *description, unsigned long duration, TaskList idsHead);
GlobalTaskList deleteTask(GlobalTaskList globalTaskList, unsigned long id, int checkDependecies);
void incrementnumberOfDependents(TaskList head);
int taskHasDependencies(Task task);
int taskHasDependents(TaskList head, Task task);
int taskHasBiggerDuration(Task task, unsigned long duration);
int criticalTask(Task task);
void listTask(Task task, int criticalPathValidation);
TaskList getDependentTasks(TaskList head, unsigned long id);

#endif