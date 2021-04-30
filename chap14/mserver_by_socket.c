#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 256
#define SOCK_MAX 4
#define UNUSED (-1)

int main(int argc, char *argv[]) {
  unsigned short port;
  int sockets[6];

  int max;
  fd_set readfds;

  max = 1;

  struct sockaddr_in srcAddr;
  struct sockaddr_in dstAddr;

  int dstAddrSize = sizeof(dstAddr);

  int numrcv;
  char buffer[BUFFER_SIZE];

  if (argc != 2) {
    fprintf(stderr, "Usage: %% server <port>\n");
    exit(EXIT_FAILURE);
  }
  port = (unsigned short)atoi(argv[1]);
  memset(&srcAddr, 0, sizeof(srcAddr));
  srcAddr.sin_port = htons(port);
  srcAddr.sin_family = PF_INET;
  srcAddr.sin_addr.s_addr = htonl(INADDR_ANY);

  printf("Address = %s, Port = %u\n", inet_ntoa(srcAddr.sin_addr), port);

  sockets[0] = socket(PF_INET, SOCK_STREAM, 0);

  bind(sockets[0], (struct sockaddr *)&srcAddr, sizeof(srcAddr));

  listen(sockets[0], SOCK_MAX + 1);

  while (1) {
    FD_ZERO(&readfds);
    for (int i = 0; i < max; i++) {
      if (sockets[i] != UNUSED)
        FD_SET(sockets[i], &readfds);
    }
    if (select(FD_SETSIZE, &readfds, NULL, NULL, NULL) == -1) {
      perror("select");
      exit(EXIT_FAILURE);
    }
    for (int i = 1; i < max; i++) {
      if (sockets[i] != UNUSED) {
        if (FD_ISSET(sockets[i], &readfds)) {
          memset(buffer, 0, BUFFER_SIZE);
          numrcv = recv(sockets[i], buffer, BUFFER_SIZE, 0);
          if (numrcv == 0 || numrcv == -1) {
            int status = close(sockets[i]);
            sockets[i] = UNUSED;
          }
          printf("received: %s\n", buffer);
          send(sockets[i], buffer, numrcv, 0);
          if (strncmp(buffer, "quit", 4) == 0) {
            int status = close(sockets[i]);
            sockets[i] = UNUSED;
          }
        }
      }

      if (FD_ISSET(sockets[0], &readfds)) {
        printf("Accept New connection.\n");
        for (int i = 0; i < max; i++) {
          if (sockets[i] == UNUSED) {
            break;
          }
          sockets[i] =
              accept(sockets[0], (struct sockaddr *)&dstAddr, &dstAddrSize);
          if (i < SOCK_MAX + 1) {
            printf("client accepted (%d) from %s\n", i,
                   inet_ntoa(dstAddr.sin_addr));
          }
          if (i == max)
            max++;
          else {
            for (; max > 0; max--)
              if (sockets[max] != UNUSED)
                break;
          }
        }
      } else {
        printf("refuse connection.\n");
        strcpy(buffer, "Server is too busy.\n");
        write(sockets[i], buffer, strlen(buffer));
        close(sockets[i]);
      }
    }
  }
}
