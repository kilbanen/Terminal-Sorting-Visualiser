#include <ncurses.h>

class Bar {
  public:
    int height;
    int maxHeight;
    int yPos;
    int colour;

    Bar() {
      height = 0;
      maxHeight = 0;
      yPos = 0;
      colour = 1;
    }
    
    Bar(int height, int maxHeight, int yPos) {
      this->height = height;
      this->maxHeight = maxHeight;
      this->yPos = yPos;
      colour = 1;
    }

    void draw(int xPos) {
      attron(COLOR_PAIR(colour));
      for(int i = 0; i < height; i++) {
        move(yPos - i, xPos);
        printw(" ");
      }
      attroff(COLOR_PAIR(colour));
      for(int i = height; i < maxHeight; i++) {
        move(yPos - i, xPos);
        printw(" ");
      }
    }

    void draw(int xPos, int colour) {
      this->colour = colour;
      draw(xPos);
    }
};
