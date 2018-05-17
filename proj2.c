#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "taskList.h"

#define COMMAND_MAX_SIZE 9

void addTaskToProject(ListNode head)
{
    int numberInputs;
    unsigned long id, duration, *ids = (unsigned long *)malloc(10 * sizeof(unsigned long));
    char description[TASK_DESC_SIZE], idsSequence[TASK_DESC_SIZE], *currentID;
    Task taskToAdd;
    numberInputs = scanf("%lu \"%[^\"]\" %lu", &id, description, &duration);
    if (numberInputs != 3)
    {
        printf("illegal arguments\n");
    }

    fgets(idsSequence, TASK_DESC_SIZE, stdin);
    for (currentID = strtok(idsSequence, " \t"); currentID; currentID = strtok(0, " \t"))
    {
        printf("ID: %s\n", currentID);
    }

    taskToAdd = newTask(id, description, duration, ids);
    showTask(taskToAdd);
    addTask(head, taskToAdd);
}

void printTaskbyDuration(ListNode head)
{
    char valueString[TASK_DESC_SIZE];
    fgets(valueString, TASK_DESC_SIZE, stdin);
    printf("printTaskbyDuration\n");
}

void listDependentTasks()
{
    printf("duration\n");
}

void removeTaskFromProject(ListNode head)
{
    unsigned long id;
    scanf("%lu", &id);
    deleteTask(head, id);
}

int main(int argc, char *argv[])
{
    char command[COMMAND_MAX_SIZE];
    ListNode head = (ListNode)malloc(sizeof(struct node));

    while (scanf("%9s", command) == 1 && strcmp(command, "exit"))
    {
        printf("%s\n", command);
        if (!strcmp(command, "add"))
        {
            addTaskToProject(head);
        }
        else if (!strcmp(command, "duration"))
        {
            listDependentTasks();
        }
        else if (!strcmp(command, "depend"))
        {
        }
        else if (!strcmp(command, "remove"))
        {
            removeTaskFromProject(head);
        }
        else if (!strcmp(command, "path"))
        {
        }
        else
        {
            printf("illegal arguments\n");
        }
    }

    /*fgets(c, TASK_DESC_SIZE, stdin);
    sscanf(c, "%s", d);
    printf("%s\n", d);

    scanf("%s", d);
    scanf("%8000s", a);
    scanf("%d", &e);
    fgets(c, TASK_DESC_SIZE, stdin);
    printf("%s\n", d);
    printf("%s\n", a);
    printf("%d\n", e);
    printf("%s\n", c);*/
    return 0;
}