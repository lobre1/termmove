#include "control.h"
#include "board.h"
#include <ncurses.h>
#include <stdlib.h>


void borderCheck( int pos[], int dimen[] ){
	if (pos[0] == dimen[0]-1) {
		pos[0]=1;
	}
	if (pos[0] < 1) {
		pos[0]=dimen[0]-2;
	}
	if (pos[1] == dimen[1]-1) {
		pos[1]=1;
	}
	if (pos[1] < 1) {
		pos[1]=dimen[1]-2;
	}
}

void controlHandler( int c, int pos[], int dimen[2], char grid[dimen[0]][dimen[1]], char person){
	grid[pos[0]][pos[1]]=' ';
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
	borderCheck(pos, dimen);
	grid[pos[0]][pos[1]]=person;
}
