#include <stdio.h>
#include <stdlib.h>

int main() {
  int *a;
  int *b;
  int c = 0;
  a = (int *)malloc(sizeof(int) * 15000000);
  b = (int *)malloc(sizeof(int) * 10000000);
  printf("&a=%x,&b=%x,&i=%x\n", a, b, &c);
  free(a);
  free(b);
}
