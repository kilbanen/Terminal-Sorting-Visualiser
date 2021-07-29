#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include "bar.h"

void swap(Bar *a, Bar *b) {
  Bar temp = *a;
  *a = *b;
  *b = temp;
  temp.xPos = a->xPos;
  a->xPos = b->xPos;
  b->xPos = temp.xPos;
  int oldAColour = a->colour;
  int oldBColour = b->colour;
  a->draw(3);
  b->draw(3);
  getch();
  a->draw(oldBColour);
  b->draw(oldAColour);
}

int isLessThan(Bar *a, Bar *b) {
  int oldAColour = a->colour;
  int oldBColour = b->colour;
  b->draw(3);
  getch();
  a->draw(3);
  getch();
  a->draw(oldAColour);
  b->draw(oldBColour);
  if(a->height < b->height)
    return 1;
  return 0;
}

void selectionSort(Bar *bars, int size) {
  for(int i = 0; i < size; i++) {
    int min = i;
    for(int j = i + 1; j < size; j++) {
      if(isLessThan(&bars[j], &bars[min]))
        min = j;
    }
    if(min != i)
      swap(&bars[min], &bars[i]);
    bars[i].draw(2);
  }
}

void insertionSort(Bar *bars, int size) {
  for(int i = 1; i < size; i++) {
    bars[i].draw(2);
    int j;
    for(j = i; j > 0 && isLessThan(&bars[j], &bars[j - 1]); j--) {
      swap(&bars[j], &bars[j - 1]);
    }
    bars[i].draw(1);
  }
}

void bubbleSort(Bar *bars, int size) {
  for(int i = 1; i < size; i++) {
    for(int j = 0; j < size - i; j++) {
      if(isLessThan(&bars[j + 1], &bars[j]))
        swap(&bars[j + 1], &bars[j]);
    }
  }
}

int main() {
  initscr();
  curs_set(0);
  noecho();
  start_color();

  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(3, COLOR_BLACK, COLOR_RED);

  int yMax, xMax, yBeg, xBeg;
  getmaxyx(stdscr, yMax, xMax);

  WINDOW *win = newwin(yMax / 2, xMax / 2, yMax / 4, xMax / 4);
  box(win, 0, 0);
  refresh();
  wrefresh(win);

  srand(time(0));

  Bar bars[xMax / 2 - 2];
  
  for(int i = 0; i < xMax / 2 - 2; i++) {
    bars[i] = Bar((rand() % (yMax / 2 - 2)) + 1, yMax / 2 - 2, yMax / 4 * 3 - 2 , xMax / 4 + i + 1);
    bars[i].draw();
  }

  switch(getch()) {
  case 's':
    selectionSort(bars, xMax / 2 - 2);
    break;
  case 'i':
    insertionSort(bars, xMax / 2 - 2);
    break;
  default:
    bubbleSort(bars, xMax / 2 - 2);
  }

  getch();
  endwin();
  return 0;
}
