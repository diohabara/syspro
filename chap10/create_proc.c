#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main() {
  pid_t ret;

  printf("[BEFORE FORK]\n Process ID : %d\t Parent Process ID : %d\n", getpid(),
         getpid());
  ret = fork();
  srand(time(NULL));
  printf("[AFTER FORK]\n Process ID : %d\t Parent Process ID : %d\n", getpid(),
         getpid());
  printf("[id=%d] Retrun Value of Fork : %d\n", getpid(), ret);
  printf("\n");
  sleep(1);
  for (int i = 0; i < 5; i++) {
    printf("(%d) for loop i=%d\n", getpid(), i);
    sleep(rand() % 3);
    int i;
  }
  if (ret == 0) {
    printf("(%d) End the child process\n", getpid());
  } else if (0 < ret) {
    printf("(%d) End the parent process\n", getpid());
  } else {
    perror("ERROR");
    exit(EXIT_FAILURE);
  }
}
