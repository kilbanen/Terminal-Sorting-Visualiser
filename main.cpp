#include <ncurses.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "bar.h"

int main() {
  initscr();
  curs_set(0);

  srand(time(0));

  std::vector<Bar> bars;

  for(int i = 0; i < 40; i++) {
    bars.push_back(rand() % 40);
    bars[i].draw(40, i);
  }

  getch();
  endwin();
  return 0;
}
