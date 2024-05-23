#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

void boardInit(int pos[2], int dimen[2], char grid[dimen[0]][dimen[1]], char person);
void boardPrint(int pos [2], int dimen[2], char grid[dimen[0]][dimen[1]], char err[]);

#endif

