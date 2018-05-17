typedef struct task *Task;
typedef struct node *TaskList;

typedef struct task {
	unsigned long id, duration;
	char *description;
	TaskList ids;
}*Task;

typedef struct node {
	Task task;
	struct node *next;
} *TaskList;

Task newTask(unsigned long id, char *description, unsigned long duration, TaskList idsHead);
int taskHasDependencies(Task task);

void TLprint(TaskList head);
void TLinsert(TaskList head, TaskList tail, Task task);
void TLdelete(TaskList head, unsigned long id);
TaskList TLsearch(TaskList head, unsigned long id);
