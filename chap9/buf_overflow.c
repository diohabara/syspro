#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_stack(int *addr, int count) {
  int i, j;
  char values[4];
  printf("       address |value(int)|value(char)\n");
  printf("-------------------------------------\n");
  for (i = 0; i < count; i++) {
    printf("%p | %08x | ", addr + i, *(addr + i));
    memcpy(values, (addr + i), 4);
    for (j = 0; j < 4; j++) {
      if (values[j] == '\0')
        values[j] = '*';
      else if (values[j] < 32 || 126 < values[j])
        values[j] = '.';
      printf("%c ", values[j]);
    }
    printf("\n");
  }
}

void getprofile() {
  char firstname[4];
  char lastname[4];
  int id;

  printf("Input your id >");
  scanf("%d", &id);
  printf("Input your first name >");
  scanf("%s", firstname);
  printf("[BEFORE inputting the last name]\n");
  show_stack(&id, 10);

  printf("Input your last name >");
  scanf("%s", lastname);
  printf("[AFTER inputting the last name]\n");
  show_stack(&id, 10);
  printf("ID=%d, firstname=%s lastname=%s\n", id, firstname, lastname);
}

void malicious_func() {
  printf("!!!!!!!!!!!!!!!!!!!!!!!!\n");
  printf("Welcom to malicious code\n");
  printf("!!!!!!!!!!!!!!!!!!!!!!!!\n");
  exit(1);
}
int main() { getprofile(0x1111111); }
