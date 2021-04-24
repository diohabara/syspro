#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *fp;
  char name[14];
  int age;
  float height;

  if ((fp = fopen("profile_binary.bin", "rb")) == NULL) {
    perror("profile_binary.bin");
    exit(EXIT_FAILURE);
  }
  if (fread(name, 1, 14, fp) != 14) {
    perror("name");
    fclose(fp);
    exit(EXIT_FAILURE);
  }
  if (fread(&age, sizeof(int), 1, fp) != 1) {
    perror("age");
    fclose(fp);
    exit(EXIT_FAILURE);
  }
  if (fread(&height, sizeof(float), 1, fp) != 1) {
    perror("height");
    fclose(fp);
    exit(EXIT_FAILURE);
  }
  if (fclose(fp) == EOF) {
    perror("profile_binary.bin");
    exit(EXIT_FAILURE);
  }

  printf("name=%s\n", name);
  printf("age=%d\n", age);
  printf("height=%f\n", height);
}
