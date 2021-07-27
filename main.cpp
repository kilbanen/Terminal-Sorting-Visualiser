#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include "bar.h"

void swap(Bar *bars, int a, int b) {
  Bar temp = bars[a];
  bars[a] = bars[b];
  bars[b] = temp;
}

int main() {
  initscr();
  curs_set(0);

  srand(time(0));

  Bar bars[40];
  
  for(int i = 0; i < 40; i++) {
    bars[i] = Bar(rand() % 40, 40);
    bars[i].draw(40, i);
  }

  getch();

  swap(bars, 0, 1);
  bars[0].draw(40, 0);
  bars[1].draw(40, 1);

  getch();
  endwin();
  return 0;
}
