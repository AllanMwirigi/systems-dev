// nodes are linked together in two directions, forward and backward
// each node has two pointers: prev and next

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  struct node *prev;
  struct node *next;
  int key;
}NODE;

void insertToEnd(NODE **list, int key) {
  NODE *p = *list;
  NODE *newNode = (NODE *)malloc(sizeof(NODE));
  newNode->key = key;
  newNode->next = NULL;

  if (p == NULL) {
    newNode->prev = NULL;
    *list = newNode;
  } else {
    while (p->next != NULL) {
      if (p->key == newNode->key) {
        return;
      }
      p = p->next;
    }
    newNode->prev = p;
    p->next = newNode;
  }
}

void insertToFront(NODE **list, int key) {
  NODE *p = *list;
  NODE *newNode = (NODE *)malloc(sizeof(NODE));
  newNode->key = key;
  newNode->prev = NULL;
  if (p == NULL) {
    newNode->next = NULL;
    *list = newNode;
    return;
  }
  newNode->next = p;
  p->prev = newNode;
  *list = newNode;
}

NODE *search(NODE *p, int key) {
  printf("search for %d = ", key);
  while (p != NULL) {
    if (p->key == key) {
      return p;
    }
    p = p->next;
  }
  return NULL;
}

void delete(NODE **list, int key) {
  printf("delete %d\n", key);
  NODE *p = *list;
  if (p->key == key) {
    p->next->prev = NULL;
    *list = p->next;
    free(p);
    return;
  }
  while (p != NULL) {
    if (p->key == key) {
      if (p->prev != NULL) p->prev->next = p->next; // update next pointer of the previous node
      if (p->next != NULL) p->next->prev = p->prev; // update prev pointer of the next node
      free(p);
      return;
    }
    p = p->next;
  }
}

void printForward(NODE *p) {
  printf("Print Forward: ");
  while (p != NULL) {
    printf("[node %d]->", p->key);
    p = p->next;
  }
  printf("[NULL]\n");
}

void printBackward(NODE *p) {
  printf("Print Backward: ");
  if (p != NULL) {
    while (p->next != NULL) {
      // step to last node
      p = p->next;
    }
    while(p != NULL) {
      printf("[node %d]->", p->key);
      p = p->prev;
    }
  }
  printf("[NULL]\n");
}

NODE *dlist;
int main() {
  int i;
  NODE *p;
  for (i = 0; i < 10; i++) {
    insertToEnd(&dlist, i);
  }
  printForward(dlist);
  // printBackward(dlist);
  insertToFront(&dlist, -1);
  printForward(dlist);
  NODE *found = search(dlist, 15);
  found != NULL ? printf("[node %d]\n", found->key) : printf("[NULL]\n");
  delete(&dlist, -1);
  printForward(dlist);
  printBackward(dlist);
  return 0;
}

