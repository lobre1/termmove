#include "control.h"
#include <ncurses.h>
#include <stdlib.h>


void controlHandler( int c, int pos[], int dimen[2], char grid[dimen[0]][dimen[1]], char bg, char person){
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
	if (pos[0] == dimen[0]) {
		pos[0]=0;
	}
	if (pos[0] < 0) {
		pos[0]=dimen[0]-1;
	}
	if (pos[1] == dimen[1]) {
		pos[1]=0;
	}
	if (pos[1] < 0) {
		pos[1]=dimen[1]-1;
	}
	grid[pos[0]][pos[1]]=person;
}
