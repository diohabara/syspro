#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  DIR *directory;
  struct dirent *ent;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filepath>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* (1) open directory */
  directory = opendir(argv[1]);
  if (!directory) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }
  /* (2) remove directory entry */
  while ((ent = readdir(directory)) != NULL) {
    printf("%s\t\n", ent->d_name);
  }
  /* (3) close directory */
  closedir(directory);
}
