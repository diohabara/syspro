#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  struct stat st;
  DIR *directory;
  mode_t filetype;
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
    printf("%s", ent->d_name);
    filetype = st.st_mode & S_IFMT;
    if (filetype & S_IFDIR) {
      printf("/");
    }
    if (filetype & S_IFLNK) {
      printf("@");
    }
    printf("\n");
  }
  closedir(directory);
}
