#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 512
#define PROFILE_SIZE 20

typedef struct profile {
  char name[24];
  int age;
} profile;

int main(int argc, char *argv[]) {
  FILE *fp;
  int i = 0;
  profile list[PROFILE_SIZE];

  if (argc != 2) {
    fprintf(stderr, "Usage: read_profile <filename>\n");
    exit(EXIT_FAILURE);
  }

  if ((fp = fopen(argv[1], "r")) == NULL) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }

  char buf[BUFSIZE];
  char *sep = ",";
  while (fgets(buf, (BUFSIZE - 1), fp) != NULL) {
    char *name = strtok(buf, sep);
    char *age = strtok(NULL, sep);
    strcpy(list[i].name, name);
    list[i].age = (int)strtol(age, (char **)NULL, 10);
    i++;
  }

  for (int j = 0; j < i; j++) {
    printf("[NO.%d]\n\tname=%s\n\tage=%d\n", j, list[j].name, list[j].age);
  }

  if (fclose(fp) == EOF) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }
}
