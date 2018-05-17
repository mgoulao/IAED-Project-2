#define TASK_DESC_SIZE 8000

typedef struct node *ListNode;

typedef struct
{
    unsigned long id, duration, *ids;
    char description[TASK_DESC_SIZE];
} Task;

struct node
{
    Task task;
    ListNode next;
};


Task newTask(unsigned long id, char description[TASK_DESC_SIZE], unsigned long duration, unsigned long *ids);

ListNode newNode(Task task);

void addTask(ListNode head, Task task);

void showTask(Task task);

void deleteTask(ListNode head, unsigned long id);
