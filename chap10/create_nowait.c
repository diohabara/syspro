#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t ret;

  ret = fork();
  if (ret == 0) {
    sleep(3);
    printf("This is a child process\n");
  } else if (0 < ret) {
    printf("This is a parent process\n");
  } else {
    perror("fork");
    exit(EXIT_FAILURE);
  }
}
