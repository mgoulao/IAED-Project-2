#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "hashTable.h"

#define MAX_DESCRIPTION_SIZE 8000
#define DEPENDECIES_SIZE 1000000
#define COMMAND_MAX_SIZE 9

void add(TaskList head, TaskList tail)
{
	TaskList dependeciesHead = NULL;
	unsigned long id, duration;
	char *s, description[MAX_DESCRIPTION_SIZE], ids[DEPENDECIES_SIZE];

	if (scanf("%lu \"%[^\"]\" %lu", &id, description, &duration) != 3)
	{
		printf("illegal arguments\n");
	}
	else
	{
		if (HTsearch(id) != NULL)
		{
			printf("%s\n", "id already exists");
		}
		else
		{
			fgets(ids, DEPENDECIES_SIZE, stdin);

			for (s = strtok(ids, " \t"); s; s = strtok(0, " \t"))
			{
				printf("dependecies ID: %s\n", ids);

			}
		}
		TLinsert(head, tail, newTask(id, description, duration, dependeciesHead));
	}
}

void printTaskbyDuration(TaskList head)
{
    char valueString[MAX_DESCRIPTION_SIZE];
    fgets(valueString, MAX_DESCRIPTION_SIZE, stdin);
    printf("printTaskbyDuration\n");
}

void listDependentTasks()
{
    printf("duration\n");
}

void removeTaskFromProject(TaskList head)
{
    unsigned long id;
    scanf("%lu", &id);
    TLdelete(head, id);
}

void readCommands(TaskList head, TaskList tail)
{
	char command[COMMAND_MAX_SIZE];
	while (scanf("%9s", command) == 1 && strcmp(command, "exit"))
	{
		printf("%s\n", command);
		if (!strcmp(command, "add"))
		{
			add(head, tail);
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
}

int main(int argc, char const *argv[])
{
	unsigned long m = 10;
	TaskList head = NULL;
	TaskList tail = NULL;
	HTinit(m);
	readCommands(head, tail);
	return 0;
}