#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char str[] = "Hello World";
void *thtest(void *arg);

int main() {
  pthread_t th1, th2;
  void *rval;

  if (pthread_create(&th1, NULL, thtest, (void *)"th1") != 0) {
    perror("Thread creation failed.\n");
    exit(EXIT_FAILURE);
  }

  if (pthread_create(&th2, NULL, thtest, (void *)"th2") != 0) {
    perror("Thread creationa failed\n");
    exit(EXIT_FAILURE);
  }

  /* wait for th1 finish while executing join */
  printf("the process joins with thread th1\n");
  if (pthread_join(th1, &rval) != 0) {
    perror("Fialed to join with th1.\n");
  } else {
    printf("th1 (thead number:%d) ends.\n", *((int *)rval));
  }

  /* wait for th2 finish while executing join */
  printf("the process joins with thread th2\n");
  if (pthread_join(th2, &rval) != 0) {
    perror("Failed to join with th2.\n");
  } else {
    printf("th2 (thread number:%d) ends\n", *((int *)rval));
  }
  printf("process ends.\n");
}

void *thtest(void *arg) {
  int i;
  int *thread_id = (int *)malloc(sizeof(int));
  *thread_id = pthread_self(); /* get self thread number */
  printf("[%s] str = %s\n", (char *)arg, str);
  /* output global variable, str */
  sleep(rand() % 5);
  pthread_exit((void *)thread_id);
}
