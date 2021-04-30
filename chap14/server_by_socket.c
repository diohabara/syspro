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

int main(int argc, char *argv[]) {
  unsigned short port;
  int srcSocket;
  int dstSocket;

  /* sockaddr_in: struct */
  struct sockaddr_in srcAddr;
  struct sockaddr_in dstAddr;
  int dstAddrSize = sizeof(dstAddr);

  /* parameters */

  int numrcv;
  char buffer[BUFFER_SIZE];
  if (argc != 2) {
    fprintf(stderr, "Usage: %%server <port> \n");
    exit(EXIT_FAILURE);
  }

  /* create socket */
  srcSocket = socket(PF_INET, SOCK_STREAM, 0);

  /* bind port and info */
  port = (unsigned short)atoi(argv[1]);
  /* sockaddr_in: set of struct */
  memset(&srcAddr, 0, sizeof(srcAddr));
  srcAddr.sin_port = htons(port);
  srcAddr.sin_family = PF_INET;
  srcAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  printf("Address = %s, Port = %u\n", inet_ntoa(srcAddr.sin_addr), port);
  bind(srcSocket, (struct sockAddr *)&srcAddr, sizeof(srcAddr));

  listen(srcSocket, 1);

  printf("Waiting for connection...\n");
  dstSocket = accept(srcSocket, (struct sockaddr *)&dstAddr, &dstAddrSize);

  printf("Connected from %s\n", inet_ntoa(dstAddr.sin_addr));

  while (1) {
    memset(buffer, 0, BUFFER_SIZE);
    numrcv = recv(dstSocket, buffer, BUFFER_SIZE, 0);
    if (numrcv == 0 || numrcv == -1) {
      close(dstSocket);
      break;
    }
    printf("received: %s\n", buffer);
    send(dstSocket, buffer, numrcv, 0);
    if (strncmp(buffer, "quit", 4) == 0)
      break;
  }
}
