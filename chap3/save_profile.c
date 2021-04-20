#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct profile {
  char name[24];
  int age;
} profile;

int main(int argc, char *argv[]) {
  FILE *fp;
  int i;

  profile list[3] = {
      {"Tomoko Tanaka", 19}, {"Miya Sakai", 21}, {"Ayane Yamamoto", 20}};

  if (argc != 2) {
    fprintf(stderr, "Usage: save_prifle <filename>\n");
    exit(EXIT_FAILURE);
  }

  if ((fp = fopen(argv[1], "w")) == NULL) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }

  fprintf(fp, "name.age\n");
  for (i = 0; i < 3; i++) {
    if (fprintf(fp, "%s,%d\n", list[i].name, list[i].age) < 0) {
      perror(argv[1]);
      fclose(fp);
      exit(EXIT_FAILURE);
    }
  }

  if (fclose(fp) == EOF) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }
}
