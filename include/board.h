#ifndef BOARD_H
#define BOARD_H

#include "bitboard.h"

#define BOARD_SIZE 9
#define NUMBER_OF_DIGITS 9

typedef struct Board {
    U128 occupancies[NUMBER_OF_DIGITS];
    U128 candidates[NUMBER_OF_DIGITS];
} Board;

Board Board_new();
void Board_set(Board *board, char string[BOARD_SIZE * BOARD_SIZE + 1]);
void Board_clear(Board *board);
void Board_print(Board *board);
U128 Board_get_occupancy(Board *board);
int Board_solve(Board *board);

#endif
