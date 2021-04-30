#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFSIZE 512

int argsplit(char *str, char *argv[]);
void chop(char *str);

int main() {
  pid_t ret;
  int status, cnt = 0;
  char str[BUFSIZE];
  char *argv[20];
  while (1) {
    printf("mysh[%d]", cnt++);
    if (fgets(str, BUFSIZE, stdin) == NULL) {
      perror(str);
      exit(EXIT_FAILURE);
    }
    chop(str);
    argsplit(str, argv);
    if (strcmp(argv[0], "quit") == 0)
      break;
    ret = fork();
    /* (1) */
    if (ret == 0) {
      execvp(argv[0], argv);
    } else if (0 < ret) {
      wait(&status);
    } else {
      perror("fork");
      exit(EXIT_FAILURE);
    }
  }
}

int argsplit(char *str, char *argv[]) { /* (2) */
  int argc = 0;
  const char s[] = " ";
  char *token;
  token = strtok(str, s);
  while (token != NULL) {
    argv[argc++] = token;
    token = strtok(NULL, s);
  }
  argv[argc] = NULL;
  return argc;
}

void chop(char *str) { str[strlen(str) - 1] = '\0'; }
