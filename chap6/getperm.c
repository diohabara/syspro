#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  struct stat st;
  mode_t accesstype;
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filepath>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  if (lstat(argv[1], &st) < 0) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }

  accesstype = st.st_mode & ~S_IFMT;
  printf("For user:");
  if (accesstype & S_IRUSR) {
    printf(" read");
  }
  if (accesstype & S_IWUSR) {
    printf(" write");
  }
  if (accesstype & S_IXUSR) {
    printf(" execute");
  }
  printf("\n");
  printf("For group:");
  if (accesstype & S_IRGRP) {
    printf(" read");
  }
  if (accesstype & S_IRGRP) {
    printf(" write");
  }
  if (accesstype & S_IXGRP) {
    printf(" execute");
  }
  printf("\n");
  printf("For others:");
  if (accesstype & S_IROTH) {
    printf(" read");
  }
  if (accesstype & S_IWOTH) {
    printf(" write");
  }
  if (accesstype & S_IXOTH) {
    printf(" execute");
  }
  printf("\n");
}
