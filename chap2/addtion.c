#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  long a, b, c;
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <num> <num>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  char *ptr1, *ptr2;
  a = strtol(argv[1], &ptr1, 10);
  b = strtol(argv[2], &ptr2, 10);
  c = a + b;
  if (errno == EINVAL || errno == ERANGE) {
    perror("ERROR(hex2dex)");
    exit(EXIT_FAILURE);
  } else if (errno != 0) {
    perror("Unexpected ERROR(hex2dec)");
    exit(EXIT_FAILURE);
  } else if (ptr1 == argv[1] || ptr2 == argv[2]) {
    fprintf(stderr, "No hex number is found.");
    exit(EXIT_FAILURE);
  } else if (*ptr1 != '\0' || *ptr2 == '\0') {
    fprintf(stderr, "Has character unrepresentative by decimal numbers");
    exit(EXIT_FAILURE);
  }
  printf("%ld + %ld = %ld\n", a, b, c);
}
