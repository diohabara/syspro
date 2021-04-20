#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 512

int main(int argc, char *argv[]) {
  FILE *fpin, *fpout;

  if (argc < 3) {
    fprintf(stderr, "Usage: copy <origin> <destination>\n");
    exit(EXIT_FAILURE);
  }

  if ((fpin = fopen(argv[1], "r")) == NULL) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }

  if ((fpout = fopen(argv[2], "w")) == NULL) {
    perror(argv[2]);
    exit(EXIT_FAILURE);
  }

  char c;
  while ((c = fgetc(fpin)) != EOF) {
    fputc(c, fpout);
  }

  if (EOF == fclose(fpin)) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }

  if (EOF == fclose(fpout)) {
    perror(argv[2]);
    exit(EXIT_FAILURE);
  }
}
