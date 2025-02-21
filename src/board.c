#include <stdio.h>
#include "bitboard.h"
#include "board.h"

Board Board_new() {
    Board board = {
        .occupancies = {
            {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}
        },
        .candidates = {
            FULL_BITBOARD,
            FULL_BITBOARD,
            FULL_BITBOARD,
            FULL_BITBOARD,
            FULL_BITBOARD,
            FULL_BITBOARD,
            FULL_BITBOARD,
            FULL_BITBOARD,
            FULL_BITBOARD
        }
    };
    return board;
}

void Board_set(Board *board, char string[BOARD_SIZE * BOARD_SIZE + 1]) {
    Board_clear(board);
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        char c = string[i];
        if (c == '.') continue;  // Skip empty cells

        int x = i % BOARD_SIZE;
        int y = i / BOARD_SIZE;
        int digit = c - '0' - 1;

        // Set bit for the current number
        Bitboard_set_at(&board->occupancies[digit], i);

        // Clear candidates for the row, column, and square
        Bitboard_clear_with(&board->candidates[digit], &COLUMNS[x]);
        Bitboard_clear_with(&board->candidates[digit], &ROWS[y]);
        Bitboard_clear_with(&board->candidates[digit], &SQUARES[(x / 3) + (y / 3) * 3]);
    }
}

void Board_clear(Board *board) {
    U128 empty = {0};
    U128 filled = FULL_BITBOARD;

    for (int i = 0; i < BOARD_SIZE; i++) {
        board->occupancies[i] = empty;
        board->candidates[i] = filled;
    }
}

U128 Board_get_occupancy(Board *board) {
    U128 o = board->occupancies[0];
    for (int i = 1; i < BOARD_SIZE; i++) {
        Bitboard_unite(&o, &board->occupancies[i]);
    }
    return o;
}

int Board_solve(Board *board) {
    U128 current_occupancy = Board_get_occupancy(board);

    int pos = -1, minimal_count = 9, best_candidates[BOARD_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        if (Bitboard_is_set_at(&current_occupancy, i)) continue;

        int count = 0, candidate_digits[BOARD_SIZE];
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (Bitboard_is_set_at(&board->candidates[j], i)) {
                candidate_digits[count++] = j;
            }
        }

        if (count < minimal_count) {
            pos = i;
            minimal_count = count;
            for (int k = 0; k < count; k++) {
                best_candidates[k] = candidate_digits[k];
            }
            if (count == 1) break;  
        }
    }

    if (pos == -1) {
        return 1; 
    }

    int x = pos % BOARD_SIZE;
    int y = pos / BOARD_SIZE;

    U128 row_mask = ROWS[y];
    U128 col_mask = COLUMNS[x];
    U128 square_mask = SQUARES[(x / 3) + (y / 3) * 3];

    for (int i = 0; i < minimal_count; i++) {
        int digit = best_candidates[i];

        U128 saved_candidates = board->candidates[digit];

        Bitboard_clear_with(&board->candidates[digit], &col_mask);
        Bitboard_clear_with(&board->candidates[digit], &row_mask);
        Bitboard_clear_with(&board->candidates[digit], &square_mask);
        Bitboard_set_at(&board->occupancies[digit], pos);

        if (Board_solve(board)) {
            return 1;
        }

        board->candidates[digit] = saved_candidates;
        Bitboard_clear_at(&board->occupancies[digit], pos);
    }
    return 0;
}

void Board_print(Board *board) {
    printf("*-----------------------*\n");

    for (int y = 0; y < BOARD_SIZE; y++) {
        if (y % 3 == 0 && y != 0) {
            printf("|-------+-------+-------|\n");
        }

        for (int x = 0; x < BOARD_SIZE; x++) {
            int pos = x + y * BOARD_SIZE;
            char value = '.';

            for (int digit = 0; digit < BOARD_SIZE; digit++) {
                if (Bitboard_is_set_at(&board->occupancies[digit], pos)) {
                    value = digit + '1';
                    break;
                }
            }
                    
            if (x % 3 == 0) {
                printf("| ");
            }

            printf("%c ", value);
        }
        printf("|\n");
    }
    printf("*-----------------------*\n");
}