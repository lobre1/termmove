#include "board.h"
#include <curses.h>


void boardInit(int pos[2], int dimen[2], char grid[dimen[0]][dimen[1]], char bg, char person){
	for (int i=0; i<dimen[0]; i++) {
		for (int j=0; j<dimen[1]; j++) {
			grid[i][j]=bg;
		}
	}
	grid[pos[0]][pos[1]]=person;
	grid[pos[0]][pos[1]]=person;
}

void boardPrint(int pos [2], int dimen[2], char grid[dimen[0]][dimen[1]], char err[]){
  init_pair(1, COLOR_RED, COLOR_RED);
  init_pair(2, COLOR_WHITE, COLOR_RED);
	for (int i=0; i<dimen[0]; i++) {
		for (int j=0; j<dimen[1]; j++) {
			if(i == pos[0] && j == pos[1]){
				attron(COLOR_PAIR(1));
				addch(grid[i][j]);
				attroff(COLOR_PAIR(1));
			}
			else{
				addch(grid[i][j]);
			}
		}
		addstr("\n");
	}
	printw("X:%d", pos[1]);
	printw(" Y:%d", pos[0]);
	printw("     ");
	attron(COLOR_PAIR(2));
	printw("%s", err);
	attroff(COLOR_PAIR(2));
}
