#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "bar.h"

void swap(Bar *a, Bar *b) {
  Bar temp = *a;
  *a = *b;
  *b = temp;
  temp.xPos = a->xPos;
  a->xPos = b->xPos;
  b->xPos = temp.xPos;
  int oldAColour = a->colour;
  int oldBColour = b->colour;
  draw(*a, 3);
  draw(*b, 3);
  getch();
  draw(*a, oldBColour);
  draw(*b, oldAColour);
}

int isLessThan(Bar *a, Bar *b) {
  int oldAColour = a->colour;
  int oldBColour = b->colour;
  draw(*b, 3);
  getch();
  draw(*a, 3);
  getch();
  draw(*a, oldAColour);
  draw(*b, oldBColour);
  if(a->height < b->height)
    return 1;
  return 0;
}

void selectionSort(Bar *bars, int size) {
  for(int i = 0; i < size; i++) {
    int min = i;
    for(int j = i + 1; j < size; j++) {
      if(isLessThan(&bars[j], &bars[min]))
        min = j;
    }
    if(min != i)
      swap(&bars[min], &bars[i]);
    draw(bars[i], 2);
  }
}

void insertionSort(Bar *bars, int size) {
  for(int i = 1; i < size; i++) {
    draw(bars[i], 2);
    int j;
    for(j = i; j > 0 && isLessThan(&bars[j], &bars[j - 1]); j--) {
      swap(&bars[j], &bars[j - 1]);
    }
    draw(bars[i], 1);
  }
}

void bubbleSort(Bar *bars, int size) {
  for(int i = 1; i < size; i++) {
    for(int j = 0; j < size - i; j++) {
      if(isLessThan(&bars[j + 1], &bars[j]))
        swap(&bars[j + 1], &bars[j]);
    }
  }
}

void merge(Bar *bars, int low, int mid, int high) {
  Bar aux[high - low + 1];

  int i = low;
  int j = mid + 1;
  int k = 0;

  draw(bars[i], 2);
  draw(bars[j], 4);
  draw(bars[high], 2);

  while(i <= mid && j <= high) {
    if(isLessThan(&bars[i], &bars[j]))
      aux[k++] = bars[i++];
    else
      aux[k++] = bars[j++];
  }

  while(i <= mid)
    aux[k++] = bars[i++];

  while(j <= high)
    aux[k++] = bars[j++];


  for(i = low; i <= high; i++) {
    bars[i] = aux[i - low];
    bars[i].xPos = i;
    if(i == low || i == high)
      draw(bars[i], 2);
    else
      draw(bars[i], 1);
    getch();
  }

  draw(bars[low], 1);
  draw(bars[high], 1);
}

void mergeSort(Bar *bars, int low, int high) {
  if(low < high) {
    int mid = low + (high - low) / 2;
    mergeSort(bars, low, mid);
    mergeSort(bars, mid + 1, high);
    merge(bars, low, mid, high);
  }
}

int partition(Bar *bars, int low, int high) {
  Bar pivot = bars[high];
  int i = low - 1;
  for(int j = low; j <= high; j++) {
    if(!isLessThan(&pivot, &bars[j])) {
      i++;
      swap(&bars[i], &bars[j]);
    }
  }
  return i;
}

void quickSort(Bar *bars, int low, int high) {
  if(low >= 0 && high >= 0) {
    if(low < high) {
      int p = partition(bars, low, high);
      quickSort(bars, low, p - 1);
      quickSort(bars, p + 1, high);
    }
  }
}

void shuffle(Bar *bars, int size) {
  srand(time(0));
  for(int i = 0; i < size; i++)
    swap(&bars[rand() % size], &bars[rand() % size]);
}

int selectAlgorithm(WINDOW *menu, char *algorithms[]) {
  int ch, i = 0;
  while(( ch = wgetch(menu)) != '\n'){
    mvwprintw(menu, i+1, 2, "%s", algorithms[i]);
    switch(ch) {
    case KEY_UP:
      i--;
      if(i < 0)
        i = 5;
      break;
    case KEY_DOWN:
      i++;
      if(i > 5)
        i = 0;
      break;
    }
    wattron(menu, A_STANDOUT);
    mvwprintw( menu, i+1, 2, "%s", algorithms[i]);
    wattroff(menu, A_STANDOUT);
  }
  return i;
}

void runAlgorithm(int algorithmIndex, Bar* bars, int size) {
  switch(algorithmIndex) {
  case 0:
    selectionSort(bars, size);
    break;
  case 1:
    insertionSort(bars, size);
    break;
  case 2:
    bubbleSort(bars, size);
    break;
  case 3:
    mergeSort(bars, 0, size - 1);
    break;
  case 4:
    quickSort(bars, 0, size - 1);
    break;
  case 5:
    shuffle(bars, size);
  }
}

int main() {
  initscr();
  curs_set(0);
  noecho();
  start_color();

  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_BLACK, COLOR_GREEN);
  init_pair(3, COLOR_BLACK, COLOR_RED);
  init_pair(4, COLOR_BLACK, COLOR_CYAN);

  char *algorithms[] = {"Selection Sort", "Insertion Sort", "Bubble Sort", "Merge Sort", "Quick Sort", "Shuffle"};
  int ch, i, width = 14;
  WINDOW * menu = newwin( 10, 20, 1, 1 );
  box(menu, 0, 0);
  for(i = 0; i < 6; i++) {
    if( i == 0 ) 
      wattron(menu, A_STANDOUT);
    else
      wattroff(menu, A_STANDOUT);
    mvwprintw(menu, i+1, 2, "%s", algorithms[i]);
  }
  refresh();
  wrefresh(menu);
  i = 0;
  keypad(menu, TRUE);
  int algorithmIndex;

  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);
  int windowHeight = yMax / 2;
  int windowWidth = xMax / 2;
  int windowY = yMax / 4;
  int windowX = xMax / 4;

  WINDOW *win = newwin(windowHeight, windowWidth, windowY, windowX);
  box(win, 0, 0);
  refresh();
  wrefresh(win);

  srand(time(0));

  Bar bars[windowWidth - 2];
  
  for(int i = 0; i < windowWidth - 2; i++) {
    bars[i].height = (rand() % (windowHeight - 2)) + 1;
    bars[i].maxHeight = windowHeight - 2;
    bars[i].yPos = windowY + windowHeight - 2;
    bars[i].xPos = i;
    bars[i].xOffset = windowX + 1;
    bars[i].colour = 1;
    draw(bars[i], 1);
  }

  while(true) {
    algorithmIndex = selectAlgorithm(menu, algorithms);
    runAlgorithm(algorithmIndex, bars, windowWidth - 2);
  }

  getch();
  endwin();
  return 0;
}
