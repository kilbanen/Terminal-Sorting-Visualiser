#include <ncurses.h>
#include "bar.h"

int main() {
  initscr();
  curs_set(0);

  Bar bars[5] = {Bar(17), Bar(9), Bar(12), Bar(16), Bar(6)};

  for(int i = 0; i < 5; i++) {
    bars[i].draw(20, i);
  }

  getch();
  endwin();
  return 0;
}
