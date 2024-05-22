#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <math.h>
#include <string.h>

const char bg = ' ';
const char person='@';


int dimen[2] = {50,100};
int pos[2];

void boardInit(char grid[dimen[0]][dimen[1]]){
	for (int i=0; i<dimen[0]; i++) {
		for (int j=0; j<dimen[1]; j++) {
			grid[i][j]=bg;
		}
	}
	grid[pos[0]][pos[1]]=person;
}

void boardPrint(char grid[dimen[0]][dimen[1]], char err[]){
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

int wrapCheck(){
	if (pos[0] == dimen[0]) {
		pos[0]=0;
		return 1;
	}
	if (pos[0] < 0) {
		pos[0]=dimen[0]-1;
		return 1;
	}
	if (pos[1] == dimen[1]) {
		pos[1]=0;
		return 1;
	}
	if (pos[1] < 0) {
		pos[1]=dimen[1]-1;
		return 1;
	}
	return 0;
}

void control( int c, int pos[],char grid[dimen[0]][dimen[1]]){
	grid[pos[0]][pos[1]]=bg;
	switch (c) {
		case 'w':
			pos[0]--;
			break;
		case 's':
			pos[0]++;
			break;
		case 'a':
			pos[1]--;
			break;
		case 'd':
			pos[1]++;
			break;
		case 'q':
			endwin();
			exit(0);
			break;
	}
	wrapCheck();
	grid[pos[0]][pos[1]]=person;
}

void init(){
	getmaxyx(stdscr,dimen[0],dimen[1]);
	dimen[0]--;
	dimen[1]--;
	pos[0]=(dimen[0])/2;
	pos[1]=(dimen[1])/2;
}

char * argHandling( int argc, char **argv){
	switch (argc) {
		case 3:
			dimen[1]=atoi(argv[2]);
			dimen[0]=atoi(argv[1]);
			if (dimen[1] < 0 && dimen[0] < 0) {
				init();
				return"Dimensions should be >0, Defaulting to full terminal.";
			}else{
				pos[0]=(dimen[0]-1)/2;
				pos[1]=(dimen[1]-1)/2;
				return" ";
			}
			break;
		case 1:
				init();
				return" ";
			break;
		default:
			init();
			return"Invalid number of arguments, Defaulting to full terminal";
			break;
	}
	return" ";
}

int main(int argc, char **argv){
	char *err = malloc(256);
	initscr();
	start_color();
	err = argHandling(argc, argv);
	char grid[dimen[0]][dimen[1]];
	boardInit(grid);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	while (1) {
		clear();
		boardPrint(grid, err);
		refresh();
		int c = getch();
		control(c, pos, grid);
	}
	free(err);
	endwin();
	return 0;
}
