#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedList.h"

/*void TLprint(ListPointers listPointers) {
   struct node *ptr = head;
   printf("\n[ ");

   while (ptr != NULL) {
      printf("(%d,%d) ", ptr->key, ptr->data);
      ptr = ptr->next;
   }

   printf(" ]");
}
*/
void TLinsert(ListPointers listPointers, Task task) {
   TaskList p, link = (struct node*) malloc(sizeof(struct node));

   for (p = listPointers->head; p->next; p = p->next);
   p->next = link;
   link->task = task;
   link->next = NULL;
}

void TLdelete(ListPointers listPointers, unsigned long id) {
   TaskList current, previous = listPointers->head;
   int exist = 0;

   for (current = listPointers->head; current->next; current = current->next,
         previous = current)
   {
      if (current->task->id == id) {
         exist = 1;
         if (taskHasDependencies(current->task)) {
            printf("%s\n", "task with dependencies");
         } else {
            previous->next = current->next;
            free(current);
         }
         break;
      }
   }

   if (!exist) {
      printf("%s\n", "no such task");
   }
}

int TLisEmpty(ListPointers listPointers) {
   return listPointers->head == NULL;
}

int TLlength(ListPointers listPointers) {
   int length = 0;
   struct node *current;

   for (current = listPointers->head; current != NULL; current = current->next) {
      length++;
   }

   return length;
}

TaskList TLsearch(ListPointers listPointers, unsigned long id) {

   TaskList current = listPointers->head;

   if (listPointers->head == NULL) {
      return NULL;
   }

   while (current->task->id != id) {

      if (current->next == NULL) {
         return NULL;
      } else {
         current = current->next;
      }
   }

   return current;
}
/*
TaskList TLdelete(int key) {

   struct node* current = head;
   struct node* previous = NULL;

   if (head == NULL) {
      return NULL;
   }

   while (current->key != key) {

      if (current->next == NULL) {
         return NULL;
      } else {
         previous = current;
         current = current->next;
      }
   }

   if (current == head) {
      head = head->next;
   } else {
      previous->next = current->next;
   }

   return current;
}

void TLsort() {

   int i, j, k, tempKey, tempData;
   struct node *current;
   struct node *next;

   int size = length();
   k = size ;

   for ( i = 0 ; i < size - 1 ; i++, k-- ) {
      current = head;
      next = head->next;

      for ( j = 1 ; j < k ; j++ ) {

         if ( current->data > next->data ) {
            tempData = current->data;
            current->data = next->data;
            next->data = tempData;

            tempKey = current->key;
            current->key = next->key;
            next->key = tempKey;
         }

         current = current->next;
         next = next->next;
      }
   }
}*/