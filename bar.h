#include <ncurses.h>

class Bar {
  public:
    int height;
    int maxHeight;

    Bar() {
      height = 0;
      maxHeight = 0;
    }
    
    Bar(int height, int maxHeight) {
      this->height = height;
      this->maxHeight = maxHeight;
    }

    void draw(int yPos, int xPos, int color) {
      attron(COLOR_PAIR(color));
      for(int i = 0; i < height; i++) {
        move(yPos - i, xPos);
        printw(" ");
      }
      attroff(COLOR_PAIR(color));
      for(int i = height; i < maxHeight; i++) {
        move(yPos - i, xPos);
        printw(" ");
      }
    }
};
