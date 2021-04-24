#include <stdio.h>
#include <stdlib.h>

struct profile {
  char name[18];
  int age;
  float height;
};

int main() {
  FILE *fp;

  struct profile list[4];

  if ((fp = fopen("list_binary.bin", "rb")) == NULL) {
    perror("list_binary.bin");
    exit(EXIT_FAILURE);
  }

  fread(list, sizeof(struct profile), 4, fp);
  if (fclose(fp) == EOF) {
    perror("list_binary.bin");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 3; i++) {
    printf("[No.%d] name=%s, age=%d, height=%.2f\n", i, list[i].name,
           list[i].age, list[i].height);
  }
}
