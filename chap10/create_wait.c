#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main() {
  pid_t ret;
  int status;

  ret = fork();
  if (ret == 0) {
    sleep(3);
    printf("This is a child process\n");
  } else if (0 < ret) {
    wait(&status);
    printf("This is a parent process\n");
  } else {
    perror("fork");
    exit(EXIT_FAILURE);
  }
}
