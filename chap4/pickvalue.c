#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr, "Usage: %s <num> <num> <num>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  FILE *fp;
  int num;
  long i, j, k;

  if ((fp = fopen("array.bin", "rb")) == NULL) {
    perror("array.bin");
    exit(EXIT_FAILURE);
  }

  i = atoi(argv[1]);
  j = atoi(argv[2]);
  k = atoi(argv[3]);
  long offset = 100 * i + 10 * j + k - 1;
  fseek(fp, offset, SEEK_SET);

  fread(&num, sizeof(int), 1, fp);
  if (fclose(fp) == EOF) {
    perror("array.bin");
    exit(EXIT_FAILURE);
  }

  printf("The value of (%ld,%ld,%ld) is %d\n", i, j, k, num);
}
