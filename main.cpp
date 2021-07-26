#include <ncurses.h>
#include "bar.h"

int main() {
  initscr();
  curs_set(0);
  Bar bar;
  bar.height = 7;
  bar.draw(5, 5);
  getch();
  endwin();
  return 0;
}
