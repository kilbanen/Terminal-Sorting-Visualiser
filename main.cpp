#include <ncurses.h>
#include <vector>
#include "bar.h"

int main() {
  initscr();
  curs_set(0);

  std::vector<Bar> bars;

  for(int i = 0; i < 40; i++) {
    bars.push_back(i);
    bars[i].draw(40, i);
  }

  getch();
  endwin();
  return 0;
}
