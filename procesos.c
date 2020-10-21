/* Procesos de usuario */

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include <time.h>

#include "c:\TURBOC3\SOURCE\kernel-z\procesos.h"


 /*---------------------------------------------------------------------------
 *                          USER TASKS
 *-------------------------------------------------------------------------*/

void task1()
{
  int k = 0;
  unsigned long int jj = 0;

  unsigned int x = SCREEN_X;
  unsigned int y = SCREEN_Y;

  while (1) {
    if (++jj >= 10000/SPEEDUP_FACTOR) {
      gotoxy(x,y);
      printf("This is task 1. Iteration: %d", ++k);
      jj = 0;
    }
  }

  return;
}

void bouncing_ball()
{
  unsigned long int jj = 0;
  char ball = 219; // The ascii code of a rectangle
  char empty = ' ';

  unsigned int x = SCREEN_X;
  unsigned int y = SCREEN_Y;
  unsigned int w = SCREEN_W / 2 - 1;
  unsigned int h = SCREEN_H / 2 - 2;

  int dx = 1;
  int dy = -1;
  int cur_x = x;
  int cur_y = y;
  int prev_x = x;
  int prev_y = y;

  gotoxy(cur_x,cur_y);
  putch(ball);

  while (1) {
    if (++jj >= 10000/SPEEDUP_FACTOR) {

      if (cur_x >= x + w && dx > 0) {
        dx *= -1;
      }
      else if (cur_x <= x && dx < 0) {
        dx *= -1;
      }
      prev_x = cur_x;
      cur_x += dx;

      if (cur_y >= y + h && dy > 0) {
        dy *= -1;
      }
      else if (cur_y <= y && dy < 0) {
        dy *= -1;
      }
      prev_y = cur_y;
      cur_y += dy;

      gotoxy(prev_x,prev_y);
      printf("%c", empty);

      gotoxy(cur_x,cur_y);
      printf("%c", ball);

      jj = 0;
    }
  }

  return;
}

void characters()
{
  unsigned long int jj = 0;
  int i;
  unsigned int x = SCREEN_X;
  unsigned int y = SCREEN_Y + SCREEN_H / 2;
  unsigned int w = SCREEN_W / 2 - 1;
  unsigned int h = SCREEN_H / 2;

  unsigned int cur_x = x;
  unsigned int cur_y = y;
  unsigned int min_char = '!';
  unsigned int max_char = '~';
  unsigned int cur_char = min_char;

  char empty_line[] = "";

  while (1) {
    if (++jj >= 10000/SPEEDUP_FACTOR) {
      jj = 0;

      // Clear the panel if we are starting over
      // from the top
      if (cur_x == x && cur_y == y) {
        for (i=y; i <= y+h; i++) {
          gotoxy(x, i);
          printf("%.*s", w + 1, empty_line);
        }
      }

      gotoxy(cur_x, cur_y);
      printf("%c", cur_char);

      if (++ cur_x > x + w) {
        cur_x = x;
        
        if (++ cur_y > y + h) {
          cur_y = y;
        }
      }

      if (++ cur_char > max_char) {
        cur_char = min_char;
      }
    }
  }

  return;
}

void clock1()
{
  time_t now;
  struct tm *tm_now;
  char   timebuff[64];
  unsigned long int jj = 0;

  unsigned int x = SCREEN_X + SCREEN_W / 2;
  unsigned int y = SCREEN_Y;
  unsigned int w = SCREEN_W / 2;
  unsigned int h = SCREEN_H / 2;
  unsigned int mid_x = x + w / 2;
  unsigned int mid_y = y + h / 2 - 1;

  while (1) {
    if (++jj >= 10000/SPEEDUP_FACTOR) {
      now = time(NULL);
      tm_now = localtime(&now);
      strftime(timebuff, sizeof(timebuff), "%H:%M:%S", tm_now);

      gotoxy(mid_x - strlen(timebuff) / 2, mid_y);
      printf("%s", timebuff);
      jj = 0;
    }
  }

  return;
}

void clock2()
{
  time_t now;
  struct tm *tm_now;
  char   timebuff[64];
  unsigned long int jj = 0;

  unsigned int x = SCREEN_X + SCREEN_W / 2;
  unsigned int y = SCREEN_Y + SCREEN_H / 2;
  unsigned int w = SCREEN_W / 2;
  unsigned int h = SCREEN_H / 2;
  unsigned int mid_x = x + w / 2;
  unsigned int mid_y = y + h / 2 - 1;

  while (1) {
    if (++jj >= 10000/SPEEDUP_FACTOR) {
      now = time(NULL);
      tm_now = localtime(&now);
      strftime(timebuff, sizeof(timebuff), "%H:%M:%S", tm_now);

      gotoxy(mid_x - strlen(timebuff) / 2, mid_y);
      printf("%s", timebuff);
      jj = 0;
    }
  }

  return;
}


void draw_screen(unsigned int x, unsigned int y, unsigned int w, unsigned int h)
{
  unsigned int mid_x = x + w / 2;
  unsigned int mid_y = y + h / 2 - 1;
  int i = 0;

  clrscr();

  for (i=x; i<=w; i++) {
    gotoxy(i, mid_y);
    putch(205); 
  }

  for (i=y; i<=h; i++) {
    gotoxy(mid_x, i);
    putch(186);
  }

  gotoxy(mid_x, mid_y);
  putch(206);

  gotoxy(0, 0);
  return;
}

