#ifndef _HASH_
#define _HASH_

#define key(a) (a->id)
#define hash(A,B) (A%B)

typedef struct hashNode {
	Task task;
	struct node *next;
}*HashTable;

void HTinit(int m);

TaskList HTsearch(unsigned long int id);

void HTinsert(Task task);

void HTdelete();

void HTdeleteTask(unsigned long id);

#endif