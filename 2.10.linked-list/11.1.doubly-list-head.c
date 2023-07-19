// A better representation of a doubly linked list involves the use of a list head which is a
// dummy node whose next points to the first node in the list and prev points to the last node.
// Is initialized with its prev and next pointers pointing to itself and later updated as above
// Additionally, when added, the first node's prev and the last node's next, point to the 
// list head therefore there are no NULL pointers in the list
// This creates kind of a circular structure and mitigates unnecessary/inefficient steps to 
// perform some operations e.g. insertEnd

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  struct node *prev;
  struct node *next;
  int key;
}NODE;

void insertEnd(NODE *list, int key) {
  NODE *head = list;
  NODE *newNode = (NODE *)malloc(sizeof(NODE));
  newNode->key = key;
  NODE *last = head->prev; // could be the list head or an actual node if list not empty
  last->next = newNode;
  newNode->prev = last;
  head->prev = newNode; // make new node the last node
  newNode->next = head;
}

void insertFront(NODE *head, int key) {
  NODE *newNode = (NODE *)malloc(sizeof(NODE));
  newNode->key = key;
  NODE *first = head->next;
  newNode->next = first;
  first->prev = newNode;
  newNode->prev = head;
  head->next = newNode;
}

NODE* search(NODE *head, int key) {
  printf("search for %d = ", key);
  NODE *p = head->next;
  while(p != head) {
    if (p->key == key) {
      return p;
    }
    p = p->next;
  }
  return NULL;
}

void delete(NODE *head, int key) {
  printf("delete %d = ", key);
  NODE *p = head->next;
  while(p != head) {
    if (p->key == key) {
      p->prev->next = p->next;
      p->next->prev = p->prev;
      free(p);
      printf("true\n");
      return;
    }
    p = p->next;
  }
  printf("false\n");
}

void printForward(NODE *head) {
  printf("Print Forward: [head]->");
  NODE *p = head->next; // first node
  while (p != head) {
    printf("[node %d]->", p->key);
    p = p->next;
  }
  printf("[head]\n");
}

void printBackward(NODE *head) {
  printf("Print Backward: [head]");
  NODE *p = head->prev; // last node
  while(p != head) {
    printf("<-[node %d]", p->key);
    p = p->prev;
  }
  printf("<-[head]\n");
}

NODE dlist;
int main() {
  int i;
  dlist.next = dlist.prev = &dlist; // empty list just with dummy list head
  for (i = 0; i < 10; i++) {
    insertEnd(&dlist, i);
  }
  printForward(&dlist);
  // printBackward(&dlist);
  insertFront(&dlist, -1);
  printForward(&dlist);
  NODE *found = search(&dlist, 15);
  found != NULL ? printf("[node %d]\n", found->key) : printf("[NULL]\n");
  delete(&dlist, -1);
  printForward(&dlist);
  return 0;
}