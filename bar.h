#include <ncurses.h>

class Bar {
  public:
    int height;
    int maxHeight;
    int yPos;

    Bar() {
      height = 0;
      maxHeight = 0;
      yPos = 0;
    }
    
    Bar(int height, int maxHeight, int yPos) {
      this->height = height;
      this->maxHeight = maxHeight;
      this->yPos = yPos;
    }

    void draw(int xPos, int color) {
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
