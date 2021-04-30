#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid;
  int status;
  int fd;

  printf("Exec ps program...\n");
  pid = fork();
  if (pid == 0) {
    if ((fd = open("processlist.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644)) ==
        -1) {
      perror("open failed");
      exit(EXIT_FAILURE);
    }
    close(1);
    if (dup(fd) != 1) {
      perror("dup failed");
      close(fd);
      exit(EXIT_FAILURE);
    }
    execlp("ps", "ps", "-1", NULL);
    close(fd);
  } else if (0 < pid) {
    wait(&status);
    printf("done.\n");
  } else {
    perror("fork");
    exit(EXIT_FAILURE);
  }
}
