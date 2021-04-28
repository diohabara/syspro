#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  struct stat st;
  DIR *directory;
  struct dirent *ent;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filepath>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  directory = opendir(argv[1]);
  if (!directory) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }

  while ((ent = readdir(directory)) != NULL) {
    if (lstat(ent->d_name, &st) < 0) {
      perror(ent->d_name);
      exit(EXIT_FAILURE);
    }
    char *name = ent->d_name;
    if (name[strlen(name) - 1] == '~') {
      char ans;
      printf("Do you remove the file %s ?[y/n/q]", name);
      scanf("%c", &ans);
      if (ans == 'y') {
        unlink(name);
      } else if (ans == 'q') {
        break;
      }
    }
  }
}
