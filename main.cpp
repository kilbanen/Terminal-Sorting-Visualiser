#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include "bar.h"

void swap(Bar *bars, int a, int b) {
  Bar temp = bars[a];
  bars[a] = bars[b];
  bars[b] = temp;
}

void selectionSort(Bar *bars, int size) {
  for(int i = 0; i < size; i++) {
    int min = i;
    for(int j = i + 1; j < size; j++) {
      bars[min].draw(min, 1);
      bars[j].draw(j, 3);
      getch();
      bars[j].draw(j, 1);
      bars[min].draw(min, 3);
      getch();
      if(bars[j].height < bars[min].height) {
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
    for(int j = i; j > 0 && bars[j].height < bars[j - 1].height; j--) {
      swap(bars, j, j - 1);
      bars[j].draw(j, 1);
      bars[j - 1].draw(j - 1 , 1);
      getch();
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
