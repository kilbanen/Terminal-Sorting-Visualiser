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
    bars.push_back(Bar(rand() % 40, 40));
    bars[i].draw(40, i);
  }

  getch();

  Bar temp = bars[0];
  bars[0] = bars[1];
  bars[1] = temp;
  
  bars[0].draw(40, 0);
  bars[1].draw(40, 1);

  getch();
  endwin();
  return 0;
}
