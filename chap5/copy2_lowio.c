#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define COPYSIZE 256

double getETime() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + (double)tv.tv_usec * 1e-6;
}

int main(int argc, char *argv[]) {
  int fdin, fdout;
  double st, en;
  char buf[COPYSIZE];

  if (argc != 3) {
    fprintf(stderr, "Usage: ./copy2_lowio <original copy> <copy>\n");
    exit(EXIT_FAILURE);
  }

  if ((fdin = open(argv[1], O_RDONLY)) < 0) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }

  if ((fdout = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0) {
    perror(argv[2]);
    exit(EXIT_FAILURE);
  }

  st = getETime();
  while (read(fdin, buf, COPYSIZE) == 1) {
    write(fdout, buf, COPYSIZE);
  }
  en = getETime();
  close(fdin);
  close(fdout);

  printf("Elapsed Time: %.6f\n", en - st);
}
