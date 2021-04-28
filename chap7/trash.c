#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *get_last_token(char path[]) {
  char *token;
  token = strtok(path, "/");
  char *last_token;
  while (token != NULL) {
    last_token = token;
    token = strtok(NULL, "/");
  }
  return last_token;
}

int main(int argc, char *argv[]) {
  int res;
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filepath>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char *dest = strncat("~/Trash", argv[1], strlen(argv[1]));
  if ((res = link(argv[1], dest) != 1)) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }
  unlink(argv[1]);
}
