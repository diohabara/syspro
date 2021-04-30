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

  mkfifo("fifofile", 0777);
  fd = open("fifofile", O_RDONLY);
  read(fd, buffer, 256);
  printf("RECEIVER: Message..%s", buffer);
  close(fd);
}
