#include <stdio.h>
#include <stdlib.h>

int func(int);

int main(int argc, char *argv[]) {
  int result;
  if (argc != 2) {
    fprintf(stderr, "Usage: %s sum <number>", argv[0]);
    exit(EXIT_FAILURE);
  }
  result = func(atoi(argv[1]));
  printf("results = %d\n", result);
}

int func(int a) {
  int ret;
  if (1 < a) {
    ret = a + func(a - 1);
  } else if (a == 1) {
    ret = a;
  }
  return ret;
}
