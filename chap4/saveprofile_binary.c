#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *fp;

  char name[] = "Takako Toyota";
  int age = 25;
  float height = 163.42;

  if ((fp = fopen("profile_binary.bin", "wb")) == NULL) {
    perror("profile_binary.bin");
    exit(EXIT_FAILURE);
  }

  fwrite(name, 1, sizeof(name), fp);
  fwrite(&age, sizeof(int), 1, fp);
  fwrite(&height, sizeof(float), 1, fp);
  if (fclose(fp) == EOF) {
    perror("profile_binary.bin");
    exit(EXIT_FAILURE);
  }
}
