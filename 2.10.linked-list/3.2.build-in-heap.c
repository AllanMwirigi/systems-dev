#include "type.h"

NODE *mylist, *node;

int printlist(NODE *p) {
  while (p) {
    printf("[%s %d]->", p->name, p->id);
    p = p->next;
  }
  printf("NULL\n");
}

// build linked list in program's heap area
int main() {
  int i;
  NODE *p;
  node = (NODE *)malloc(N*sizeof(NODE)); // node->N*72 bytes in heap
  // node points to the first element in the allocated memory containing N adjacent nodes, 
  // therefore can regard the memory area as an array and use node[i] to access each element
  // could also use *(p+i)
  
  for(i = 0; i < N; i++) {
    p = &node[i]; // access each NODE location in heap
    sprintf(p->name, "%s%d", "node", i); // the node's name set to "node i"
    p->id = i;
    p->next = p+1; // node[i].next = &node[i+1]
    // p+1 increments the pointer by the size of it's content i.e. no.bytes of it's data type
  }
  node[N-1].next = 0;
  mylist = &node[0];
  printlist(mylist);
  return 0;
}

// build linked list in program's heap area but with individually allocated nodes
int main2() {
  int i;
  NODE *p, *q;
  for(i = 0; i < N; i++) {
    p = (NODE *)malloc(sizeof(NODE)); // allocate a node on the heap
    sprintf(p->name, "%s%d", "node", i);
    p->id = i;
    p->next = 0; // node[i].next = 0
    if (i == 0) {
      mylist = q = p; // mylist -> node0; q->current node
    }
    // next pointer of previous node should point to current node
    // except for i = 0 where next is set to itself; this is corrected on the next pass
    q->next = p; // node[i-1].next = node[i]
    q = p; // update previous pointer
  }
  printlist(mylist);
  return 0;
}