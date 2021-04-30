#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  pid_t pid;
  int status;

  printf("Exec ps program...\n");
  pid = fork();
  if (pid == 0) {
    execlp("ps", "ps", "-1", NULL);
  } else if (0 < pid) {
    wait(&status);
    printf("done.\n");
  } else {
    perror("fork");
    exit(EXIT_FAILURE);
  }
}
