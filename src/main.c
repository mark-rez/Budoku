#include "board.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <bitboard_string>\n", argv[0]);
        return 1;
    }
    
    Board board = Board_new();
    Board_set(&board, argv[1]);
    Board_solve(&board);
    Board_print(&board);

    return 0;
}
