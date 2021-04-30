#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void chop(char *);

int main() {
  char str[256];
  int fd[2];
  pid_t ret;
  int status;

  if (pipe(fd) < 0) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  ret = fork();

  if (ret == 0) {
    read(fd[0], str, sizeof(str));
    printf("A child process: My parent said,\"%s\"\n", str);
  } else if (ret == -1) {
    perror("fork");
    exit(1);
  } else {
    printf("A parent process: input any string> ");
    fgets(str, sizeof(str), stdin);
    chop(str);
    write(fd[1], str, sizeof(str));
    wait(&status);
  }
}

void chop(char *str) {
  str[strlen(str) - 1] = '\0';
  return;
}
