#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include <time.h>

#include "c:\TURBOC3\SOURCE\kernel-z\colas.h"

#define AVAILABLE    -1
#define READY_QUEUE_SIZE 4

typedef struct {
  int slots[READY_QUEUE_SIZE];

  int front;
  int rear;
  int count;

  int next_free;
  int current_slot;
} queue_t;

queue_t ready_queue;

/*---------------------------------------------------------------------------
 *                          READY QUEUE API
 *-------------------------------------------------------------------------*/
/**
 * @brief Initialized the queue of processes that are in READY state. */

void imprime_queue(){
queue_t *q;
int k;

  q = &ready_queue;

  printf("\n cola:"); 
  for (k = 0; k < READY_QUEUE_SIZE; k++) 
    printf("%d,",q->slots[k]);
  
}

void init_queue()
{
  
  queue_t *q;
  int k;

  q = &ready_queue;

  for (k = 0; k < READY_QUEUE_SIZE; k++) 
      q->slots[k] = AVAILABLE;

  q->count = 0;
  q->front = 0;
  q->rear = -1;
}


/*
void init_queue()
{
  int k;
  for (k = 0; k < READY_QUEUE_SIZE; k++) {
    q->slots[k] = AVAILABLE;
  }

  q->count = 0;
  q->front = 0;
  q->rear = -1;
}
*/

/**
 * @brief Check if the queue is empty
 *
 * @param q - pointer to the queue structure
 *
 * @return 1 if empty; 0 otherwise
 */
int is_empty(queue_t *q)
{
  return q->count == 0;
}

/**
 * @brief Check if the queue is full
 *
 * @param q - pointer to the queue structure
 *
 * @return 1 if full; 0 otherwise
 */
int is_full(queue_t *q)
{
  return q->count == READY_QUEUE_SIZE;
}

/**
 * @brief Return the number of elements in the queue
 *
 * @param q - pointer to the queue structure
 *
 * @return The number of elements in the queue
 */
int sizeq(queue_t *q)
{
  return q->count;
}

/**
 * @brief Add an element to the queue
 *
 * @param q - pointer to the queue structure
 * @param value - value to enqueue
 */

void enqueue(queue_t *q, int value)
{
int k;

  if (!is_full(q)) {
    q->rear = (q->rear + 1) % READY_QUEUE_SIZE;
    q->slots[q->rear] = value;
    q->count ++;
  }
/*
  printf("\n value: %d = ",value);
  for (k = 0; k < READY_QUEUE_SIZE; k++) 
    printf("%d,",q->slots[k]);
  */
}

/**
 * @brief Gets the next element in the queue.
 *
 * @param q - pointer to the queue structure.
 *
 * @return The next element in the queue or -1 if empty
 */
int dequeue(queue_t *q) 
{
  int data = -1;

  if (!is_empty(q)) {
    data = q->slots[q->front];

    q->front = (q->front + 1) % READY_QUEUE_SIZE;
    q->count --;
  }

  return data;
}


/*---------------------------------------------------------------------------
 *                          SCHEDULER API
 *-------------------------------------------------------------------------*/
/**
 * @brief Enqueue a READY task.
 *
 * @param task_id   Task to be enqueued.
 */
void enqueue_task(int task_id)
{
  enqueue(&ready_queue, task_id);
}

/**
 * @brief Dequeue the next task to be run.
 *
 * @return A task_id  that identifies the next process to run.
 */
int dequeue_task()
{
  return dequeue(&ready_queue);
}
