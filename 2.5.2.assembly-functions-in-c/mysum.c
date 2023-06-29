#include <stdio.h>

// compile 32bit - gcc -m32 -o combined.out -Wall mysum.c mysum-helpers.s && ./combined.out
extern int mysum(int x, int y);

int main() {
  int a, b, sum;
  a = 3; b = 2;
  sum = mysum(a, b);
  printf("Sum is %d\n", sum);
}