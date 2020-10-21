/*-----------------------------------------------------------------------------
 *  A program that simulates a scheduler in DOS.
 *
 *  The program defines four tasks that run concurrently. The tasks are
 *  suspended and resumed by a context-switching routine that is executed every
 *  ~50 ms (when the IRQ8 interruption is received.)
 *
 *  As per the assignment instructions, the four user tasks are as follows:
 *
 *  1) A Bouncing ball
 *  2) Print characters to the screen
 *  3) A clock
 *  4) Another clock
 *
 *  It uses the dos.h library provided by Turbo-C.
 *  To build:
 *    TCC -IC:\TURBOC3\INCLUDE -LC:\TURBOC3\LIB SCHED.C
 * --------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include <time.h>
//#include <graphics.h>

#include "c:\TURBOC3\SOURCE\kernel-z\procesos.h"
#include "c:\TURBOC3\SOURCE\kernel-z\colas.h"
#include "c:\TURBOC3\SOURCE\kernel-z\pripro.h"
#include "c:\TURBOC3\SOURCE\kernel-z\datos.h"

#define IRQ8 0x08

#if 0
#define DEBUG
#endif


void interrupt (*old_routine)(void);

int j = 0;


int current_task = -1;

/**
 * @brief Function that schedules the next task to be run.
 *
 * @return Nothing.
 */

void interrupt context_switch()
{
  disable();

  if (current_task < 0) {
//    printf("No task currently running\n");
  }
  else {
    PCB[current_task].ss = _SS;
    PCB[current_task].sp = _SP;

/*
    PCB[current_task].where_x = wherex();
    PCB[current_task].where_y = wherey();
*/

//    printf("Enqueueing: %d\n", current_task);

    enqueue_task(current_task);
  }

  current_task = dequeue_task();

//  printf("Dequeued: %d\n", current_task);

/*
  if (i%20 == 0) {
    j++;
    printf("Time elapsed: %d seconds\n", j);
  }

  i++;
*/

  /* Finish the program after 30 seconds */
  if (j >= 10) {
    setvect(IRQ8, old_routine);
    old_routine();
    enable();
    exit (0);
  }

  if (current_task != -1) {
//    gotoxy(PCB[current_task].where_x, PCB[current_task].where_y);
    _SS = PCB[current_task].ss;
    _SP = PCB[current_task].sp;
  }

  old_routine();
  enable();
}


/**
 * The main() function:
 *  1) Sets the context_switch function to be executed when the real-time clock
 *     interrupt is triggered.
 *
 *  2) Registers four tasks.
 *
 *  3) Let the context_switch function drive the scheduling of the four tasks.
 */

//int gdriver=DETECT,gmode;

int main()
{

//  initgraph(&gdriver,&gmode,"c:\\turboc3\\bgi");

  initgrafica();

  old_routine = getvect(IRQ8);

  init_queue();

/*
  init_task(bouncing_ball, 1, "Bouncing Ball", 
            SCREEN_X, SCREEN_Y, 
            SCREEN_W / 2, SCREEN_H / 2);

  init_task(clock1, 2, "Clock 1", 
            SCREEN_X + SCREEN_W / 2, SCREEN_Y, 
            SCREEN_W / 2, SCREEN_H / 2);

  init_task(characters, 3, "Printing Chars to Screen", 
            SCREEN_X, SCREEN_Y + SCREEN_H / 2, 
            SCREEN_W / 2, SCREEN_H / 2);

  init_task(clock2, 4, "Clock 2", 
            SCREEN_X + SCREEN_W / 2, SCREEN_Y + SCREEN_H / 2, 
            SCREEN_W / 2, SCREEN_H / 2);

*/

//  init_task(bouncing_ball, 1, "Bouncing Ball");

  //init_task(juego, 1, "Juego de la Vibora");
  init_task(juego2, 1, "Ping pong");
  init_task(clock1, 2, "Clock 1");
/*
  init_task(characters, 3, "Printing Chars to Screen");
*/
  init_task(clock2, 4, "Clock 2");

  getch();

//  draw_screen(SCREEN_X, SCREEN_Y, SCREEN_W, SCREEN_H);

  setvect(IRQ8, context_switch);

  do {
  } while(!kbhit());

  setvect(IRQ8, old_routine);
  return 0;
}
