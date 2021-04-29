#include <stdio.h>
#include <stdlib.h>

int main() {
  int *array;
  int i;
  int length;

  printf("input length of array > ");
  scanf("%d", &length);

  array = (int *)malloc(sizeof(int) * length);

  for (i = 0; i < length; i++) {
    array[i] = i * 3;
  }

  for (i = 0; i < length; i++) {
    printf("array[%d]=%d\n", i, array[i]);
  }

  free(array);
}
