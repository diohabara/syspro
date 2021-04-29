#include <stdio.h>
#include <stdlib.h>

/* global */
int ex1 = 532;
int ex2;

main() {
  static int st1 = 100;
  static int st2;
  int local = 0;
  static char array_static[1024];
  char array_local[1024];
  char *array_dynamic;

  array_dynamic = (char *)malloc(1024);

  printf("---- variables ----\n");
  printf("ex1\t\t:%8x\n", &ex1);
  printf("ex2\t\t:%8x\n", &ex2);
  printf("st1\t\t:%8x\n", &st1);
  printf("st2\t\t:%8x\n", &st2);
  printf("local\t\t:%8x\n", &local);

  printf("---- arrays ----\n");
  printf("array_static\t\t:%8x\n", array_static);
  printf("array_local\t\t:%8x\n", array_local);
  printf("*array_dynamic\t\t:%8x\n", &array_dynamic);
  printf("array_dynamic\t\t:%8x\n", array_dynamic);

  printf("---- arrays ----\n");
  printf("main\t\t:%8x\n", main);
  printf("printf\t\t:%8x\n", printf);
}
