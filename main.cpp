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
      if(bars[j].height < bars[min].height)
        min = j;
    }
    if(min != i) {
      swap(bars, min, i);
      bars[min].draw(40, min);
      bars[i].draw(40, i);
      getch();
    }
  }
}

int main() {
  initscr();
  curs_set(0);

  srand(time(0));

  Bar bars[80];
  
  for(int i = 0; i < 80; i++) {
    bars[i] = Bar(rand() % 40, 40);
    bars[i].draw(40, i);
  }

  getch();

  selectionSort(bars, 80);

  getch();
  endwin();
  return 0;
}
