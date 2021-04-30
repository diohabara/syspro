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
  char *destination;
  unsigned short port;
  int dstSocket;
  struct sockaddr_in dstAddr;
  int numrcv;

  char buffer[BUFFER_SIZE];

  if (argc != 3) {
    fprintf(stderr, "Usage: %% client <address> <port>\n");
    exit(-1);
  }
  destination = argv[1];
  port = (unsigned short)atoi(argv[2]);

  dstSocket = socket(PF_INET, SOCK_STREAM, 0);

  memset(&dstAddr, 0, sizeof(dstAddr));
  dstAddr.sin_port = htons(port);
  dstAddr.sin_family = PF_INET;
  dstAddr.sin_addr.s_addr = inet_addr(destination);
  printf("Trying to connect to %s: \n", destination);
  connect(dstSocket, (struct sockaddr *)&dstAddr, sizeof(dstAddr));

  char message[256];
  while (1) {
    memset(message, 0, 256);
    printf(">");
    fgets(message, 256, stdin);
    message[strlen(message) - 1] = '\0';
    send(dstSocket, message, strlen(message), 0);
    numrcv = recv(dstSocket, buffer, BUFFER_SIZE, 0);
    if (numrcv == 0 || numrcv == -1) {
      close(dstSocket);
      break;
    }
    printf("from server: %s\n", buffer);
    if (strncmp(buffer, "quit", 4) == 0)
      break;
  }

  close(dstSocket);
}
