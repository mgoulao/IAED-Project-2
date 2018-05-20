#ifndef _LIST_
#define _LIST_
#define BIG_TASK_TIME 10000000
#define MAX_DESCRIPTION_SIZE 8000
#define DEPENDECIES_SIZE 80000
#define COMMAND_MAX_SIZE 9

typedef struct task *Task;
typedef struct node *TaskList;

struct task
{
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
int taskHasDependencies(Task task);
int taskHasDependents(TaskList head, Task task);
int taskHasBiggerDuration(Task task, unsigned long duration);
int criticalTask(Task task);
void listTask(Task task, int criticalPathValidation);
TaskList getDependentTasks(TaskList head, unsigned long id);

void TLprintId(TaskList head);
void TLprint(TaskList head, char condition, unsigned long duration, int criticalPathValidation);
GlobalTaskList TLinsert(TaskList head, TaskList tail, Task task);
void TLdelete(TaskList head);
GlobalTaskList TLTaskdelete(GlobalTaskList globalTaskList, unsigned long id);
TaskList TLsearch(TaskList head, unsigned long id);
int TLisEmpty(TaskList head);
int TLlength(TaskList head);
void ResetTasksTime(TaskList head);
int TLcalculateTasksTimes(TaskList head);
void TLcalculateLateStart(TaskList node, unsigned long duration);

#endif