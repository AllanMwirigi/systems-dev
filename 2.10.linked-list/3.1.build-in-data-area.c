// construct and print linked list

#include "type.h"

NODE *mylist, node[N]; // in bss section of program runtime image

int printlist(NODE *p) {
  while (p) {
    printf("[%s %d]->", p->name, p->id);
    p = p->next;
  }
  printf("NULL\n");
}

int main() {
  int i;
  NODE *p;
  for (i =0; i < N; i++) {
    p = &node[i];
    sprintf(p->name, "%s%d", "node", i); // the node's name set to "node i"
    p->id = i;
    p->next = p+1; // node[i].next = &node[i+1]
    // p+1 increments the pointer by the size of it's content i.e. no.bytes of it's data type
  }
  node[N-1].next = 0;
  mylist = &node[0]; // mylist points to first node
  printlist(mylist);
  return 0;
}