#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include <string>
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
  a->draw(3);
  b->draw(3);
  getch();
  a->draw(oldBColour);
  b->draw(oldAColour);
}

int isLessThan(Bar *a, Bar *b) {
  int oldAColour = a->colour;
  int oldBColour = b->colour;
  b->draw(3);
  getch();
  a->draw(3);
  getch();
  a->draw(oldAColour);
  b->draw(oldBColour);
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
    bars[i].draw(2);
  }
}

void insertionSort(Bar *bars, int size) {
  for(int i = 1; i < size; i++) {
    bars[i].draw(2);
    int j;
    for(j = i; j > 0 && isLessThan(&bars[j], &bars[j - 1]); j--) {
      swap(&bars[j], &bars[j - 1]);
    }
    bars[i].draw(1);
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

  bars[i].draw(2);
  bars[j].draw(4);
  bars[high].draw(2);

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
      bars[i].draw(2);
    else
      bars[i].draw(1);
    getch();
  }

  bars[low].draw(1);
  bars[high].draw(1);
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

int main() {
  initscr();
  curs_set(0);
  noecho();
  start_color();

  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_BLACK, COLOR_GREEN);
  init_pair(3, COLOR_BLACK, COLOR_RED);
  init_pair(4, COLOR_BLACK, COLOR_CYAN);

  std::string algorithms[] = {"Selection Sort", "Insertion Sort", "Bubble Sort", "Merge Sort", "Quick Sort"};
  int ch, i, width = 14;
  WINDOW * menu = newwin( 10, 20, 1, 1 );
  box(menu, 0, 0);
  for(i = 0; i < 5; i++) {
    if( i == 0 ) 
      wattron(menu, A_STANDOUT);
    else
      wattroff(menu, A_STANDOUT);
    mvwprintw(menu, i+1, 2, "%s", algorithms[i].c_str());
  }
  refresh();
  wrefresh(menu);
  i = 0;
  keypad(menu, TRUE);
  while(( ch = wgetch(menu)) != '\n'){
    mvwprintw(menu, i+1, 2, "%s", algorithms[i].c_str());
    switch(ch) {
    case KEY_UP:
      i--;
      if(i < 0)
        i = 4;
      break;
    case KEY_DOWN:
      i++;
      if(i > 4)
        i = 0;
      break;
    }
    wattron(menu, A_STANDOUT);
    mvwprintw( menu, i+1, 2, "%s", algorithms[i].c_str());
    wattroff(menu, A_STANDOUT);
  }
  delwin(menu);

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
    bars[i] = Bar((rand() % (windowHeight - 2)) + 1, windowHeight - 2, windowY + windowHeight - 2 , i, windowX + 1);
    bars[i].draw();
  }

  switch(getch()) {
  case 's':
    selectionSort(bars, windowWidth - 2);
    break;
  case 'i':
    insertionSort(bars, windowWidth - 2);
    break;
  case 'b':
    bubbleSort(bars, windowWidth - 2);
    break;
  case 'm':
    mergeSort(bars, 0, windowWidth - 3);
    break;
  default:
    quickSort(bars, 0, windowWidth - 3);
  }

  getch();
  endwin();
  return 0;
}
