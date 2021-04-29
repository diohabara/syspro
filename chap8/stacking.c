#include <stdio.h>
#include <stdlib.h>

int funcA(int);
int funcB(int);
char *funcC(int);

int funcA(int a) {
  int retA;
  a++;
  retA = funcB(a);
  return retA;
}

int funcB(int b) {
  int retB;
  retB = b * b;
  return retB;
}

char *funcC(int c) {
  char *retC;
  int i;
  retC = (char *)malloc(sizeof(char) * c);
  for (i = 0; i < c; i++)
    retC[i] = 'x';
  return retC;
}

int main() {
  int ret;
  char *str;
  ret = funcA(10);
  str = funcC(ret);

  printf("str=%s\n", str);
}
