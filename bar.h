#include <ncurses.h>

class Bar {
  public:
    int height;
    void draw(int yPos, int xPos) {
      attron(A_STANDOUT);
      for(int i = 0; i < height; i++) {
        move(yPos + i, xPos);
        printw("%d", i);
      }
      attroff(A_STANDOUT);
    }
};
