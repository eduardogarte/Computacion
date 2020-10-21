#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include <time.h>

#include "c:\TURBOC3\SOURCE\kernel-z\datos.h"

#define STACK_SIZE 1024

/**
 * @brief Defines the Set of Registers available in DOS
 */
struct internal_register_set_t {
  unsigned bp;
  unsigned di;
  unsigned si;
  unsigned ds;
  unsigned es;
  unsigned dx;
  unsigned cx;
  unsigned bx;
  unsigned ax;
  unsigned ip;
  unsigned cs;
  unsigned flags;
};


typedef struct internal_register_set_t  process_registers_t;

typedef void (*task_t) (void);

//process_control_block_t *running_taskP = NULL;

process_control_block_t PCB[8];


/* copy string */

char *strdup (const char *s) { 
    char *d = malloc (strlen (s) + 1); // Space for length plus nul 
    if (d == NULL) return NULL;   // No memory 
    strcpy (d,s);      // Copy the characters 
    return d;       // Return the new string 
} 


/**
 * @brief Initializes a task.
 *
 * Captures the process info and stores it in the PCB (Process Control Block).
 *
 * @param taskP     Function pointer of the task to register.
 * @param task_id   An identified for the task.
 */

/*
void init_task(task_t taskP, unsigned task_id, const char *task_name, 
               unsigned int x, unsigned int y, unsigned int width, unsigned int height)
*/

void init_task(task_t taskP, unsigned task_id, const char *task_name)
{

process_registers_t *regP = NULL;

  printf("Initializing task: %u: %s\n", task_id, task_name);

  regP = (process_registers_t *) (PCB[task_id].stack + STACK_SIZE -
sizeof(process_registers_t));

  PCB[task_id].sp = FP_OFF((process_registers_t far *) regP);
  PCB[task_id].ss = FP_SEG((process_registers_t far *) regP);

  regP->cs = FP_SEG(taskP);
  regP->ip = FP_OFF(taskP);
  regP->ds = _DS;
  regP->es = _DS;
  regP->flags = 0x20;

  PCB[task_id].DirSeg = FP_SEG(taskP);
  PCB[task_id].DirOff = FP_OFF(taskP);

  PCB[task_id].id = task_id;
  PCB[task_id].name = strdup(task_name);
  PCB[task_id].state = READY;
  PCB[task_id].priority = 0;

/*
  PCB[task_id].panel.x = x;
  PCB[task_id].panel.y = y;
  PCB[task_id].panel.width = width;
  PCB[task_id].panel.height = height;

  PCB[task_id].where_x = 0;
  PCB[task_id].where_y = 0;
*/

  enqueue_task(task_id);

}
