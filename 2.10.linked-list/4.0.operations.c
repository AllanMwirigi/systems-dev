#include "type.h"

/****************************** TRAVERSAL ******************************/
// step through the elements in sequential order
void printList(NODE *p) {
  printf("printList: ");
  while (p) {
    printf("[%s]->", p->name);
    p = p->next;
  }
  printf("NULL\n");
}

void printListRecursive(NODE *p) {
  if (p == 0) { 
    printf("NULL\n");
    return;
  }
  printf("[%s]->", p->name);
  printListRecursive(p->next);
  // NOTE: printListRecursive(p+1) would only work for list created as a contiguous array in mem
}

// sum of node values in a linked list
int sum(NODE *p) {
  int sum = 0;
  while(p) {
    sum += p->id;
    p = p->next;
  }
  return sum;
}
int sumRecursive(NODE *p) {
  if (p == 0) return 0;
  return p->id + sumRecursive(p->next);
}

// access previous node during traversal of singly linked list
void printPrevious(NODE * p) {
  printf("printPrevious: ");
  NODE *prev = 0;
  while (p) {
    if (prev == 0) printf("NULL");
    else printf("<-[node%d]", prev->id);
    prev = p;
    p = p->next;
  }
  printf("<-[node%d]<-NULL\n", prev->id);
}

/****************************** SEARCH *****************************************/
// search list for node with a given key, returning a pointer to the node or NULL
// if it does not exist
NODE *search(NODE *node, int key) {
  while(node) {
    if (node->id == key) return node;
    node = node->next;
  }
  return NULL;
}

/****************************** INSERT ********************************************/
// insert new element into the list based on specific criterion
NODE *insertEnd(NODE **list, NODE *newNode) {
  NODE *p = *list;
  if (p == 0) {
    // list is empty, insert the new node as the first element
    *list = newNode;
  } else {
    // step to last element
    while (p->next) {
      if (newNode->id == p->id) {
        // prevent insertion if key not unique
        return NULL;
      }
      p = p->next;
    }
    p->next = newNode;
  }
  newNode->next = 0;
  return newNode;
}

/******************************** PRIORITY QUEUE ************************************/
// is a singly linked list ordered by priority, with high priority values in front
// nodes with same priority are ordered FIFO
// for this example, assuming that id is the priority, with 0 as highest priority
// for an opposite priority order, just reverse the two conditions checked
NODE *enqueue(NODE **list, NODE *newNode) {
  NODE *p = *list;
  if (p == 0 || newNode->id < p->id) {
    // list is empty or newNode has higher priority than the first node in the list
    *list = newNode;
    newNode->next = p;
  } else {
    // step to first node whose priority is lower than the newNode's
    // i.e. the node that causes a break out of this loop
    while (p->next && newNode->id >= p->next->id) {
      p = p->next;
    }
    newNode->next = p->next;
    p->next = newNode;
  }
  return newNode;
}

/******************************** DELETION *******************************************/
// delete node with the given key from the list, if it exists
// since the operation may modify the list, the list must be passed by reference
// returns the deleted node's pointer, which may be used to free it, if was dynamically allocated
NODE *delete(NODE **list, int key) {
  if (*list == 0) {
    // empty list
    return NULL;
  }
  NODE *p = *list;
  if (p->id == key) {
    // matched node at the beginning of the list
    *list = p->next;
    return p;
  }
  NODE *q = p->next; // p is current node, q is the next node
  while (q) {
    if (q->id == key) {
      p->next = q->next; // delete q from the list
      return q;
    }
    // advance the pointers
    p = q;
    q = q->next;
  }
  // no node matched
  return NULL;
}



NODE *mylist, nodes[N];
int main() {
  int i;
  NODE *p;
  for (i = 0; i < N; i++) {
    p = &nodes[i];
    p->id = i;
    sprintf(p->name, "node %d", i);
    if (i == N-1) p->next = 0;
    else p->next = p+1; // = &nodes[i+1];

    // nodes[i].id = i;
    // sprintf(nodes[i].name, "node%d", i);
    // if (i == N-1) nodes[i].next = 0;
    // else nodes[i].next = &nodes[i+1];
  }
  mylist = &nodes[0];

  printList(mylist);
  printListRecursive(mylist);
  printPrevious(mylist);
  printf("Sum: %d\n", sum(mylist));
  printf("Sum Recursive: %d\n", sumRecursive(mylist));

  NODE *found = search(mylist, 4);
  printf("Search for id 4 = [%s]\n", found ? found->name : "NULL");

  NODE *newNode = (NODE *)malloc(sizeof(NODE));
  if (newNode != 0) { // would otherwise mean that out of heap memory
    newNode->id = 10;
    // (*newNode).name = "node10"; ??????
    sprintf(newNode->name, "node %d", 10);

    // insert operation may modify the list itself, pass list param by reference i.e. pass addr
    NODE *inserted = insertEnd(&mylist, newNode);
    printf("Inserted [%s]\n", inserted ? inserted->name : "EXISTS");
    printList(mylist);
    NODE *deleted = delete(&mylist, 10);
    printf("Deleted [%s]\n", deleted ? deleted->name : "NO MATCH");
    printList(mylist);
    free(deleted);
  }

  NODE *newNode2 = (NODE *)malloc(sizeof(NODE));
  if (newNode2 != 0) { // would otherwise mean that out of heap memory
    newNode2->id = 4;
    sprintf(newNode2->name, "node %d v2", 4);

    NODE *enqueued = enqueue(&mylist, newNode2);
    printf("Enqueued [%s]\n", enqueued->name);
    printList(mylist);
  }
  return 0;
}