#include "board.h"
#include "control.h"
#include <stdlib.h>
#include <curses.h>

const char bg = ' ';
const char person='@';
const char barrier='#';


int dimen[2] = {50,100}; 
int pos[2];

char barrierChar;

/*struct tuple{
	int x;
	int y;
};

struct tuple barriers[10];

void barrierInit( struct tuple barCoord[10], char grid[dimen[0]][dimen[1]] ){
	for (int i=0; i<10; i++) {
		if (barCoord[i].y<dimen[0] && barCoord[i].x<dimen[1]){
			grid[barCoord[i].y][barCoord[i].x]='#';

		}
	}
}*/


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
	boardInit(pos, dimen, grid, bg, person);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	while (1) {
		clear();
		boardPrint(pos,dimen,grid,err);
		refresh();
		int c = getch();
		controlHandler(c, pos, dimen, grid, bg, person);
	}
	free(err);
	endwin();
	return 0;
}
