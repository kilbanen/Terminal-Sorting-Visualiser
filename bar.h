#include <ncurses.h>

typedef struct Bar
{
    int height;
    int maxHeight;
    int yPos;
    int xPos;
    int xOffset;
    int colour;
} Bar;

void draw(Bar bar, int colour) {
  bar.colour = colour;
  attron(COLOR_PAIR(colour));
  for(int i = 0; i < bar.height; i++) {
    move(bar.yPos - i, bar.xPos + bar.xOffset);
    printw(" ");
  }
  attroff(COLOR_PAIR(colour));
  for(int i = bar.height; i < bar.maxHeight; i++) {
    move(bar.yPos - i, bar.xPos + bar.xOffset);
    printw(" ");
  }
}
