#include <stdio.h>

// https://stackoverflow.com/a/65839661
// x86-64 Linux - compile and link with gcc, then run, as:
// $ gcc -o combined.out -Wall get-registers.c get-register-helpers.s && ./combined.out

extern int get_ebp();
extern int get_esp();

int main() {
  int ebp, esp;
  ebp = get_ebp();
  esp = get_esp();
  printf("ebp=%8x   esp=%8x\n", ebp, esp);
}