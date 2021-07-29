#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include "bar.h"

void swap(Bar *bars, int a, int b) {
  Bar temp = bars[a];
  bars[a] = bars[b];
  bars[b] = temp;
  temp.xPos = bars[a].xPos;
  bars[a].xPos = bars[b].xPos;
  bars[b].xPos = temp.xPos;
  int oldAColour = bars[a].colour;
  int oldBColour = bars[b].colour;
  bars[a].draw(3);
  bars[b].draw(3);
  getch();
  bars[a].draw(oldBColour);
  bars[b].draw(oldAColour);
}

int isLessThan(Bar *bars, int a, int b) {
  int oldAColour = bars[a].colour;
  int oldBColour = bars[b].colour;
  bars[b].draw(3);
  getch();
  bars[a].draw(3);
  getch();
  bars[a].draw(oldAColour);
  bars[b].draw(oldBColour);
  if(bars[a].height < bars[b].height)
    return 1;
  return 0;
}

void selectionSort(Bar *bars, int size) {
  for(int i = 0; i < size; i++) {
    int min = i;
    for(int j = i + 1; j < size; j++) {
      if(isLessThan(bars, j, min))
        min = j;
    }
    if(min != i)
      swap(bars, min, i);
    bars[i].draw(2);
  }
}

void insertionSort(Bar *bars, int size) {
  for(int i = 1; i < size; i++) {
    bars[i].draw(2);
    int j;
    for(j = i; j > 0 && isLessThan(bars, j, j - 1); j--) {
      swap(bars, j, j - 1);
    }
    bars[i].draw(1);
  }
}

void bubbleSort(Bar *bars, int size) {
  for(int i = 1; i < size; i++) {
    for(int j = 0; j < size - i; j++) {
      if(isLessThan(bars, j + 1, j))
        swap(bars, j + 1, j);
    }
  }
}

int main() {
  initscr();
  curs_set(0);
  noecho();
  start_color();

  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(3, COLOR_BLACK, COLOR_RED);

  srand(time(0));

  Bar bars[40];
  
  for(int i = 0; i < 40; i++) {
    bars[i] = Bar(rand() % 40, 40, 40, i);
    bars[i].draw();
  }

  getch();

  selectionSort(bars, 40);
  //insertionSort(bars, 40);
  //bubbleSort(bars, 40);

  getch();
  endwin();
  return 0;
}
