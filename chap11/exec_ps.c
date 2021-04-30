#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Exec ps program...\n");
  execlp("ps", "ps", "-1", NULL);
  printf("done.\n");
}
