#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <math.h>

int H = 50;
int W = 100;

const char bg = ' ';
const char person='@';

//char grid[H][W];
int pos[2];
int i=1;

void boardInit(char grid[H][W]){
	for (int i=0; i<H; i++) {
		for (int j=0; j<W; j++) {
			grid[i][j]=bg;
		}
	}
	grid[pos[0]][pos[1]]=person;
}

void boardPrint(char grid[H][W]){
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_RED);
	for (int i=0; i<H; i++) {
		for (int j=0; j<W; j++) {
			if(i == pos[0] && j == pos[1]){
				attron(COLOR_PAIR(2));
				addch(grid[i][j]);
			}
			else{
				attron(COLOR_PAIR(1));
				addch(grid[i][j]);
			}
		}
		addstr("\n");
	}
	printw("X:%d", pos[1]);
	printw(" Y:%d", pos[0]);
}

int wrapCheck(){
	if (pos[0] == H) {
		pos[0]=0;
		return 1;
	}
	if (pos[0] < 0) {
		pos[0]=H-1;
		return 1;
	}
	if (pos[1] == W) {
		pos[1]=0;
		return 1;
	}
	if (pos[1] < 0) {
		pos[1]=W-1;
		return 1;
	}
	return 0;
}

void control( int c, int pos[],char grid[H][W]){
	switch (c) {
		case 'w':
			pos[0]--;
			if (wrapCheck()==0){
				grid[pos[0]][pos[1]]=person;
				grid[pos[0]+1][pos[1]]=bg;
			}else{
				grid[0][pos[1]]=bg;
			}
			break;
		case 's':
			pos[0]++;
			if (wrapCheck()==0){
				grid[pos[0]][pos[1]]=person;
				grid[pos[0]-1][pos[1]]=bg;
			}else{
				grid[H-1][pos[1]]=bg;
			}
			break;
		case 'a':
			pos[1]--;
			if (wrapCheck()==0){
				grid[pos[0]][pos[1]]=person;
				grid[pos[0]][pos[1]+1]=bg;
			}else{
				grid[pos[0]][0]=bg;
			}
			break;
		case 'd':
			pos[1]++;
			if (wrapCheck()==0){
				grid[pos[0]][pos[1]]=person;
				grid[pos[0]][pos[1]-1]=bg;
			}else{
				grid[pos[0]][W-1]=bg;
			}
			break;
		case 'q':
			exit(0);
			break;
	}
}

int main(){
  int col, row;
	initscr();
	start_color();
	getmaxyx(stdscr,row,col);
	H = row-1;
	W = col-1;
	pos[0]=H/2;
	pos[1]=W/2;
	char grid[H][W];
	boardInit(grid);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	while (1) {
		clear();
		boardPrint(grid);
		refresh();
		int c = getch();
		control(c, pos, grid);
	}
	endwin();
	return 0;
}
