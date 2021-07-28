#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include "bar.h"

void swap(Bar *bars, int a, int b) {
  Bar temp = bars[a];
  bars[a] = bars[b];
  bars[b] = temp;
  bars[a].draw(a, 3);
  bars[b].draw(b, 3);
  getch();
}

int isLessThan(Bar *bars, int a, int b) {
  bars[b].draw(b, 3);
  bars[a].draw(a, 1);
  getch();
  bars[a].draw(a, 3);
  getch();
  bars[b].draw(b, 1);
  bars[a].draw(a, 1);
  if(bars[a].height < bars[b].height)
    return 1;
  return 0;
}

void selectionSort(Bar *bars, int size) {
  for(int i = 0; i < size; i++) {
    int min = i;
    for(int j = i + 1; j < size; j++) {
      if(isLessThan(bars, j, min)) {
        bars[min].draw(min, 1);
        min = j;
      }
    }
    if(min != i) {
      swap(bars, min, i);
      bars[min].draw(min, 1);
    }
    bars[i].draw(i, 2);
    getch();
  }
}

void insertionSort(Bar *bars, int size) {
  for(int i = 1; i < size; i++) {
    bars[i - 1].draw(i - 1, 1);
    int j;
    for(j = i; j > 0 && isLessThan(bars, j, j - 1); j--) {
      swap(bars, j, j - 1);
      bars[j].draw(j, 1);
      bars[j - 1].draw(j - 1, 1);
      bars[i].draw(i, 2);
    }
    bars[j].draw(j, 1);
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

  srand(time(0));

  Bar bars[40];
  
  for(int i = 0; i < 40; i++) {
    bars[i] = Bar(rand() % 40, 40, 40);
    bars[i].draw(i, 1);
  }

  getch();

  //selectionSort(bars, 40);
  insertionSort(bars, 40);

  getch();
  endwin();
  return 0;
}
