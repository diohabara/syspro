#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int id, tmp, i;
  int *counter;
  int num;
  struct shmid_ds buf;

  srand((unsigned)time(NULL));
  if (argc == 1) {
    if ((id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1) {
      perror("shmget");
      exit(EXIT_FAILURE);
    }
    printf("shared memory ID = %d\n", id);
  } else if (argc == 2) {
    id = atoi(argv[1]);
  } else {
    fprintf(stderr, "%s [<shared memory ID>]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  printf("Input the number to add. >");
  scanf("%d", &num);

  counter = (int *)shmat(id, 0, 0);
  if (argc == 1) {
    *counter = 0;
  }

  for (i = 0; i < 3; i++) {
    tmp = *counter;
    fprintf(stderr, "counter:%d", tmp);
    sleep(rand() % 4);
    tmp += num;
    *counter = tmp;
    fprintf(stderr, " -> %d\n", *counter);
  }
  shmctl(id, IPC_STAT, &buf);
  if (shmdt(counter) == -1) {
    perror("shmdt");
    exit(EXIT_FAILURE);
  }
  if (buf.shm_nattch == 1) {
    if (shmctl(id, IPC_RMID, 0) == -1) {
      perror("chmctl");
    }
  }
}
