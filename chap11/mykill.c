#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  pid_t pid;
  if (argc != 2) {
    fprintf(stderr, "Usage: mykill <process id>\n");
    exit(EXIT_FAILURE);
  }
  pid = atoi(argv[1]);
  if (kill(pid, SIGTERM) < 0)
    perror("Kill");
}
