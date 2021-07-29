#include <ncurses.h>

class Bar {
  public:
    int height;
    int maxHeight;
    int yPos;
    int xPos;
    int colour;

    Bar() {
      height = 0;
      maxHeight = 0;
      yPos = 0;
      xPos = 0;
      colour = 1;
    }
    
    Bar(int height, int maxHeight, int yPos, int xPos) {
      this->height = height;
      this->maxHeight = maxHeight;
      this->yPos = yPos;
      this->xPos = xPos;
      colour = 1;
    }

    void draw() {
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

    void draw(int colour) {
      this->colour = colour;
      draw();
    }
};
