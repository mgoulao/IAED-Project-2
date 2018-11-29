#ifndef _LIST_
#define _LIST_

#include "task.h"

#define BIG_TASK_TIME 10000000
#define MAX_DESCRIPTION_SIZE 8000
#define DEPENDECIES_SIZE 80000
#define COMMAND_MAX_SIZE 9
#define CHECK_DEPENDECIES 1
#define NOT_CHECK_DEPENDECIES 0


void TLprintId(TaskList head);
void TLprint(TaskList head, char condition, unsigned long duration, int criticalPathValidation);
GlobalTaskList TLinsert(TaskList head, TaskList tail, Task task);
void TLdelete(TaskList head);
void TLdeleteAllTasks(GlobalTaskList globalTaskList);
TaskList TLsearch(TaskList head, unsigned long id);
int TLisEmpty(TaskList head);
int TLlength(TaskList head);
void ResetTasksLateStart(TaskList head);
unsigned long TLcalculateDuration(TaskList node);
int TLcalculateTasksTimes(TaskList head);
void TLcalculateLateStart(TaskList node, unsigned long duration);

#endif