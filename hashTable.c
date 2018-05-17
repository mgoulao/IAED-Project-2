#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "hashTable.h"

static TaskList *heads;

static int M;

void HTinit(int m) {
	int i;
	M = m;
	heads = (TaskList*)malloc(M * sizeof(TaskList));
	for (i = 0; i < M; i++) heads[i] = NULL;
}


TaskList HTsearch(unsigned long int id) {
	int i = hash(id, M);
	return TLsearch(heads[i], id);
}

void HTinsert(Task task) {
	int i = hash(key(task), M);
	TLinsert(heads[i], task);
}
void HTdelete(long id) {
	int i = hash(id, M);
	TLdelete(heads[i], id);
}