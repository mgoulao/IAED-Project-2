#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "hashTable.h"

GlobalTaskList globalTaskList;

void addTaskToProject(unsigned long id, char *description, unsigned long duration, GlobalTaskList dependeciesPointer)
{
	Task newTask;
	incrementnumberOfDependents(dependeciesPointer.head);
	newTask = createTask(id, description, duration, dependeciesPointer.head);
	globalTaskList = TLinsert(globalTaskList.head, globalTaskList.tail, newTask);
	HTinsert(newTask);
	globalTaskList.criticalPathValidation = 0;
}

/*
 * Function:  add 
 * --------------------
 * Adds a Task to a global TaskList and a HashTable
 * 
 * command: add id descrição duração ids
 * 
 */
void add()
{
	char *end, *s, description[MAX_DESCRIPTION_SIZE], ids[DEPENDECIES_SIZE];
	struct taskListPointers dependeciesPointer;
	unsigned long numberInputs = 0, id, duration, longFromCommand, canInsert = 1;
	dependeciesPointer.head = NULL, dependeciesPointer.tail = NULL;

	numberInputs = scanf("%lu \"%[^\"]\" %lu", &id, description, &duration);
	fgets(ids, DEPENDECIES_SIZE, stdin);

	if (numberInputs != 3 || id == 0 || duration == 0)
		printf("illegal arguments\n");
	else
	{
		if (HTsearch(id) != NULL)
			printf("%s\n", "id already exists");
		else
		{
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
						dependeciesPointer = TLinsert(dependeciesPointer.head, dependeciesPointer.tail,
													  HTsearch(longFromCommand)->task);
				}
			}
			if (canInsert)
			{
				addTaskToProject(id, description, duration, dependeciesPointer);
			}
		}
	}
}

/*
 * Function:  listTasksByDuration 
 * --------------------
 * List all Tasks with duration bigger or equal
 * to the value given or list all Tasks if 
 * the value is omitted list all Tasks
 * 
 * command: duration || duration value
 * 
 */
void listTasksByDuration()
{
	unsigned long duration = 0;
	if (getchar() != '\n')
		scanf("%lu", &duration);

	if (duration)
		TLprint(globalTaskList.head, 'd', duration, globalTaskList.criticalPathValidation);
	else
		TLprint(globalTaskList.head, 'a', 0, globalTaskList.criticalPathValidation);
}

/*
 * Function:  printDependentTasks 
 * --------------------
 * Prints the dependent Tasks id's of
 * the Task indicated in the command
 * 
 * command: depend id
 * 
 */
void printDependentTasks()
{
	unsigned long id;
	TaskList p, dependentTasksHead = NULL;

	if (scanf("%lu", &id) != 1 || id == 0)

		printf("illegal arguments\n");

	else
	{
		if (TLisEmpty(HTsearch(id)))
			printf("no such task\n");
		else
		{
			dependentTasksHead = getDependentTasks(globalTaskList.head, id);

			printf("%lu:", id);
			if (TLlength(dependentTasksHead))
			{
				for (p = dependentTasksHead; p; p = p->next)
					printf(" %lu", p->task->id);

				printf("\n");
			}
			else
				printf(" no dependencies\n");

			TLdelete(dependentTasksHead);
		}
	}
}

/*
 * Function:  removeTaskFromProject 
 * --------------------
 * Removes a given task from the Project
 * 
 * command: remove id
 * 
 */
void removeTaskFromProject()
{
	unsigned long id;
	if (scanf("%lu", &id) != 1 || id == 0)
		printf("illegal arguments\n");
	else
		globalTaskList = deleteTask(globalTaskList, id, CHECK_DEPENDECIES);
}

/*
 * Function:  removeTaskFromProject 
 * --------------------
 * Lists all the Tasks in the Critical Path
 * by the order of insertion
 * 
 * command: path
 * 
 */
void listTasksFromCriticalPath()
{
	unsigned long duration;

	duration = TLcalculateTasksTimes(globalTaskList.head);
	TLprint(globalTaskList.head, 'c', duration, globalTaskList.criticalPathValidation);
	printf("project duration = %lu\n", duration);
}

/*
 * Function:  readCommands 
 * --------------------
 * Reads the program commands from the 
 * stdin
 * 
 */
void readCommands()
{
	char command[COMMAND_MAX_SIZE];
	while (scanf("%9s", command) == 1 && strcmp(command, "exit"))
	{
		if (!strcmp(command, "add"))
			add();
		else if (!strcmp(command, "duration"))
			listTasksByDuration();
		else if (!strcmp(command, "depend"))
			printDependentTasks();
		else if (!strcmp(command, "remove"))
			removeTaskFromProject();
		else if (!strcmp(command, "path"))
		{
			globalTaskList.criticalPathValidation = 1;
			listTasksFromCriticalPath();
		}
		else
			printf("illegal arguments\n");
	}
}

int main()
{
	unsigned long m = 1000;
	globalTaskList.head = NULL;
	globalTaskList.tail = NULL;
	globalTaskList.criticalPathValidation = 0;

	HTinit(m);

	readCommands(globalTaskList.head, globalTaskList.tail);

	TLdeleteAllTasks(globalTaskList);
	HTdelete();

	return 0;
}