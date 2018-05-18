#ifndef _LIST_
#define _LIST_

typedef struct task *Task;
typedef struct node *TaskList;

struct task
{
	unsigned long id, duration;
	char description[8000];
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
} GlobalTaskList;

Task createTask(unsigned long id, char *description, unsigned long duration, TaskList idsHead);
int taskHasDependencies(Task task);
int taskHasDependents(GlobalTaskList globalTaskList, Task task);
int taskHasBiggerDuration(Task task, unsigned long duration);
int criticalTask(Task task);
void listTask(Task task, int criticalPathValidation);
TaskList getDependentTasks(GlobalTaskList globalTaskList, unsigned long id);

void TLprintId(TaskList head);
void TLprint(TaskList head, char condition, unsigned long duration, int criticalPathValidation);
GlobalTaskList TLinsert(TaskList head, TaskList tail, Task task);
void TLdelete(TaskList head);
GlobalTaskList TLTaskdelete(GlobalTaskList globalTaskList, unsigned long id);
TaskList TLsearch(TaskList head, unsigned long id);
int TLlength(TaskList head);

#endif