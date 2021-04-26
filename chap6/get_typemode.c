#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  struct stat st;
  mode_t filetype;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filepath>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  if (lstat(argv[1], &st) < 0) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }

  filetype = st.st_mode & S_IFMT;
  printf("filetype:");
  switch (filetype) {
  case S_IFIFO:
    printf("FIFO\n");
    break;
  case S_IFCHR:
    printf("Character device\n");
    break;
  case S_IFDIR:
    printf("Directory\n");
    break;
  case S_IFBLK:
    printf("Block device\n");
    break;
  case S_IFREG:
    printf("Regular file\n");
    break;
  case S_IFLNK:
    printf("Symbolic link\n");
    break;
  case S_IFSOCK:
    printf("Socket\n");
    break;
  default:
    printf("Unknown type\n");
  }
  printf("Access authorities: %o\n", st.st_mode & ~S_IFMT);
}
