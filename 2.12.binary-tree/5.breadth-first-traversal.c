// a queue is used to store the yet to be traversed parts of the tree

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int key;
  struct node *left, *right;
}NODE;

typedef struct queue {
  struct queue *next; // queue pointer
  struct node *node; // queue contents
}QUEUE;

void enqueue(QUEUE **queue, NODE *node) {
  QUEUE *q = *queue;
  QUEUE *new = (QUEUE *)malloc(sizeof(QUEUE));
  new->node = node;
  new->next = NULL;
  // add to the end of the queue
  if (q == NULL) {
    *queue = new;
  } else {
    while (q->next != NULL) {
      q = q->next;
    }
    q->next = new;
  }
}

NODE *dequeue(QUEUE **queue) {
  // return first node in the queue
  QUEUE *q = *queue;
  if (q != NULL) {
    *queue = q->next;
    return q->node;
  }
  return NULL;
}

int qlength(QUEUE *q) {
  int count = 0;
  while (q != NULL) {
    count += 1;
    q = q->next;
  }
  return count;
}

void breadthFirstTraversal(NODE *root) {
  if (root == NULL) return;
  QUEUE *q = NULL;
  enqueue(&q, root);
  int nodeCount = 1;
  while (nodeCount != 0) {
    NODE *node = dequeue(&q);
    printf("%d ", node->key);
    if (node->left != NULL) enqueue(&q, node->left);
    if (node->right != NULL) enqueue(&q, node->right);
    nodeCount -= 1;
    if (nodeCount == 0) {
      nodeCount = qlength(q);
      printf("\n");
    }
  }
}

NODE *newNode(int key) {
  NODE *node = (NODE *)malloc(sizeof(NODE));
  node->key = key;
  node->left =NULL;
  node->right = NULL;
  return node;
}

int main() {
  // simple tree
  NODE *root = newNode(1);
  root->left = newNode(2);
  root->right = newNode(3);
  root->left->left = newNode(4);
  root->left->right = newNode(5);
  root->right->left = newNode(6);
  breadthFirstTraversal(root);
  return 0;
}