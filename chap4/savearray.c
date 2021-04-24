#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *bfp, *tfp;

  int array[50][50][50];
  for (int i = 0; i < 50; i++) {
    for (int j = 0; j < 50; j++) {
      for (int k = 0; k < 50; k++) {
        array[i][j][k] = rand();
      }
    }
  }

  // binary file
  if ((bfp = fopen("array.bin", "wb")) == NULL) {
    perror("array.bin");
    exit(EXIT_FAILURE);
  }
  fwrite(array, sizeof(int), 50 * 50 * 50, bfp);
  if (fclose(bfp) == EOF) {
    perror("array.bin");
    exit(EXIT_FAILURE);
  }

  // text file
  if ((tfp = fopen("array.txt", "w")) == NULL) {
    perror("array.txt");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < 50; i++) {
    for (int j = 0; j < 50; j++) {
      for (int k = 0; k < 50; k++) {
        fprintf(tfp, "%d", array[i][j][k]);
      }
    }
  }
  if (fclose(tfp) == EOF) {
    perror("array.txt");
    exit(EXIT_FAILURE);
  }

  system("stat -f\%z array.bin");
  system("stat -f\%z array.txt");

  /* because txt files store data as text(ASCII form), compared with
   * binary text, have bigger file size. */
}
