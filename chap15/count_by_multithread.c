#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int value = 50;
void *calc1(void *arg);
void *calc2(void *arg);

typedef struct {
  char name[64];
  pthread_mutex_t *mlock;
} ThreadArgs;

int main() {
  pthread_t th1, th2;
  void *rval;
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

  /* create thread th1 */
  ThreadArgs args1 = {"th1", &mutex};
  if (pthread_create(&th1, NULL, calc1, (void *)&args1) != 0) {
    perror("Thread creation failed.\n");
    exit(EXIT_FAILURE);
  }

  /* create thread th2 */
  ThreadArgs args2 = {"th2", &mutex};
  if (pthread_create(&th2, NULL, calc2, (void *)&args2) != 0) {
    perror("Thread creation failed.\n");
    exit(EXIT_FAILURE);
  }

  /* join thread th1 */
  if (pthread_join(th1, &rval) != 0) {
    perror("Failed to join with th1.\n");
    exit(EXIT_FAILURE);
  }

  /* join thread th2 */
  if (pthread_join(th2, &rval) != 0) {
    perror("Failed to join with th2.\n");
    exit(EXIT_FAILURE);
  }
}

void *calc1(void *arg) {
  ThreadArgs *targs = (ThreadArgs *)arg;
  int prev;
  sleep(rand() % 3);

  printf("[%s] trying to lock...\n", targs->name);
  pthread_mutex_lock(targs->mlock);
  printf("[%s] locked...\n", targs->name);
  prev = value;
  sleep(rand() % 5);
  value = prev + 10;
  printf("[%s] %d -> %d\n", (char *)targs->name, prev, value);
  pthread_mutex_unlock(targs->mlock);
  printf("[%s] unlock\n", targs->name);
}

void *calc2(void *arg) {
  ThreadArgs *targs = (ThreadArgs *)arg;
  int prev;
  sleep(rand() % 3);

  printf("[%s] trying to lock...\n", targs->name);
  pthread_mutex_lock(targs->mlock);
  printf("[%s] locked...\n", targs->name);
  prev = value;
  sleep(rand() % 5);
  value = prev * 10;
  printf("[%s] %d -> %d\n", (char *)targs->name, prev, value);
  pthread_mutex_unlock(targs->mlock);
  printf("[%s] unlock\n", targs->name);
}
