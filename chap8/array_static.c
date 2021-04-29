#include <stdio.h>

int main() {
  int array[16];
  int i;

  for (i = 0; i < 16; i++) {
    array[i] = i * 3;
  }

  for (i = 0; i < 16; i++) {
    printf("array[%d]=%d\n", i, array[i]);
  }
}
