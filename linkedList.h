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

void TLprint(TaskList head);
GlobalTaskList TLinsert(TaskList head, TaskList tail, Task task);
void TLdelete(TaskList head);
void TLdeleteAndFree(TaskList head, unsigned long id);
TaskList TLsearch(TaskList head, unsigned long id);
int TLlength(TaskList head);
