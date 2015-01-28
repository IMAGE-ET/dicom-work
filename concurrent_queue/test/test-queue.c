#include "queue.h"
#include "stdio.h"

int main() {
  int i;
  static void *buffer[100];
  int values[10];
  int *retVal;
  //queue_t myqueue = QUEUE_INITIALIZER(buffer);
  queue_t myqueue;
  queue_init(&myqueue, buffer, 100);

  for(i = 0; i < 10; i++) {
    values[i] = i * 10;
    queue_enqueue(&myqueue, (void *) (&values[i]));
  }
  while(queue_size(&myqueue) > 0) {
    retVal = (int *)queue_dequeue(&myqueue);
    printf("Value: %d\n", *retVal);
  }
  return 1;
}
