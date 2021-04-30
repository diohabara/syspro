#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd;
  char buffer[256];

  fd = open("fifofile", O_WRONLY);
  fgets(buffer, 256, stdin);
  write(fd, buffer, strlen(buffer) + 1);
  printf("SERVER: Sent message...%s", buffer);
  close(fd);
}
