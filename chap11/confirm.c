#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void stop();

int main() {
  signal(SIGINT, stop);
  while (1) {
    sleep(1);
    printf(".");
    fflush(stdout);
  }
}

void stop() {
  int ans;
  printf("Do you really stop?(y/n)");
  ans = getchar();
  if (ans == 'y')
    exit(EXIT_SUCCESS);
}
