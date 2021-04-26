#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  struct stat st;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (lstat(argv[1], &st) < 0) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }

  printf("%s's owner id is %d.\n", argv[1], st.st_uid);
}
