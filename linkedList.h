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

typedef struct {
	TaskList head, tail;
} *ListPointers;

Task newTask(unsigned long id, char *description, unsigned long duration, TaskList idsHead);
int taskHasDependencies(Task task);

void TLprint(ListPointers listPointers);
void TLinsert(ListPointers listPointers, Task task);
void TLdelete(ListPointers listPointers, unsigned long id);
TaskList TLsearch(ListPointers listPointers, unsigned long id);
