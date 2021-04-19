#include <stdio.h>

int main(int argc, char *argv[]) {
  int i;
  printf("Number of args is %d\n", argc);
  printf("The 0th argument is \"%s\" \
            (this is comand name)\n", argv[0]);
  for (i = 1; i < argc; i++) {
    printf("The %dth argument is \"%s\"\n", i, argv[i]);
  }
}
