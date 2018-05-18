#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "hashTable.h"

#define MAX_DESCRIPTION_SIZE 8000
#define DEPENDECIES_SIZE 1000000
#define COMMAND_MAX_SIZE 9

GlobalTaskList globalTaskList;

void add()
{
	char *end;
	struct taskListPointers dependeciesPointer;
	Task newTask;
	unsigned long id, duration, longFromCommand, canInsert = 1;
	char *s, description[MAX_DESCRIPTION_SIZE], ids[DEPENDECIES_SIZE];

	dependeciesPointer.head = NULL, dependeciesPointer.tail = NULL;

	if (scanf("%lu \"%[^\"]\" %lu", &id, description, &duration) != 3)
		printf("illegal arguments\n");
	else
	{
		if (HTsearch(id) != NULL)
		{
			printf("%s\n", "id already exists");
		}
		else
		{
			fgets(ids, DEPENDECIES_SIZE, stdin);
			if (strcmp(ids, "\n") != 0)
			{
				for (s = strtok(ids, " \t"); s; s = strtok(0, " \t"))
				{
					longFromCommand = strtoul(s, &end, 10);

					if (HTsearch(longFromCommand) == NULL)
					{
						printf("no such task\n");
						canInsert = 0;
						TLdelete(dependeciesPointer.head);
						break;
					}
					else
					{
						dependeciesPointer = TLinsert(dependeciesPointer.head, dependeciesPointer.tail,
													  HTsearch(longFromCommand)->task);
					}
				}
			}
			if (canInsert)
			{
				newTask = createTask(id, description, duration, dependeciesPointer.head);
				globalTaskList = TLinsert(globalTaskList.head, globalTaskList.tail, newTask);
				HTinsert(newTask);
			}
		}
	}
}

void printTaskbyDuration()
{
	char valueString[MAX_DESCRIPTION_SIZE];
	fgets(valueString, MAX_DESCRIPTION_SIZE, stdin);
	printf("printTaskbyDuration\n");
}

void listTasksByDuration(int criticalPathValidation)
{
	unsigned long duration;
	TaskList p;

	scanf("%lu", duration);

	if (duration)
	{
		for(p = globalTaskList.head; p; p = p->next) {
			if(p->task->)
		}
		if (criticalPathValidation)
		{
			printf("[0 CRITICAL]");
		}
	}
	else
	{
		if (criticalPathValidation)
		{
			printf("[0 CRITICAL]");
		}
	}
}

void printDependentTasks()
{
	unsigned long id;
	TaskList p, dependeciePointer = NULL;
	struct taskListPointers dependentTasks;
	dependentTasks.head = NULL;
	dependentTasks.tail = NULL;
	scanf("%lu", &id);

	for (p = globalTaskList.head; p; p = p->next)
	{
		dependeciePointer = TLsearch(p->task->ids, id);

		if (dependeciePointer)
		{
			dependentTasks = TLinsert(dependentTasks.head, dependentTasks.tail, p->task);
		}
	}

	printf("%lu:", id);
	if (TLlength(dependentTasks.head))
	{
		for (p = dependentTasks.head; p; p = p->next)
		{
			printf(" %lu", p->task->id);
		}
		printf("\n");
	}
	else
	{
		printf(" no dependencies\n");
	}
}

void removeTaskFromProject()
{
	unsigned long id;
	scanf("%lu", &id);
	TLdeleteAndFree(globalTaskList.head, id);
	HTdelete(id);
}

void readCommands()
{
	int criticalPathValidation = 0;
	char command[COMMAND_MAX_SIZE];
	while (scanf("%9s", command) == 1 && strcmp(command, "exit"))
	{
		/*printf("-%s\n", command);*/
		if (!strcmp(command, "add"))
		{
			add();
		}
		else if (!strcmp(command, "duration"))
		{
			listTasksByDuration(criticalPathValidation);
		}
		else if (!strcmp(command, "depend"))
		{
			printDependentTasks();
		}
		else if (!strcmp(command, "remove"))
		{
			removeTaskFromProject();
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
	unsigned long m = 1000;
	globalTaskList.head = NULL;
	globalTaskList.tail = NULL;
	HTinit(m);
	readCommands(globalTaskList.head, globalTaskList.tail);
	/*TLprint(globalTaskList.head);
	HTshow();*/
	return 0;
}