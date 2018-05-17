#include <stdio.h>
#include <stdlib.h>
#include "taskList.h"

Task newTask(unsigned long id, char description[TASK_DESC_SIZE], unsigned long duration, unsigned long *ids)
{
    Task task;
    task.id = id;
    task.duration = duration;
    task.ids = ids;
    return task;
}

ListNode newNode(Task task)
{
    ListNode listNode = (ListNode)malloc(sizeof(struct node));
    listNode->next = NULL;
    listNode->task = task;
    return listNode;
}

void addTask(ListNode head, Task task)
{
    int exists = 0;
    ListNode current = head;
    while (current->next != NULL)
    {
        if (current->next->task.id == task.id)
        {
            printf("id already exists\n");
            exists = 1;
            break;
        }
        current = current->next;
    }
    if (!exists)
    {
        current->next = newNode(task);
    }
}

void showTask(Task task)
{
    printf("ShowTask\n");
}

void deleteTask(ListNode head, unsigned long id)
{
    int exists = 0;
    ListNode current = head, previous = 0;
    while (current->next != NULL)
    {
        if (current->next->task.id == id)
        {
            exists = 1;
            break;
        }
        previous = current;
        current = current->next;
    }
    if (exists)
    {
        if(sizeof(current->task.ids) == 0) {
            previous->next = current->next;
            free(current);
        } else {
            printf("task with dependencies\n");
        }
    } else {
        printf("no such task\n");
    }
}