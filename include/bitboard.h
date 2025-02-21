#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>

#define FULL_BITBOARD {18446744073709551615ULL, 131071ULL}

typedef struct {
    uint64_t low;
    uint64_t high;
} U128;

extern const U128 ROWS[];
extern const U128 COLUMNS[];
extern const U128 SQUARES[];

void Bitboard_set_at(U128 *bitboard, int k);
void Bitboard_clear_at(U128 *bitboard, int k);
int Bitboard_is_set_at(const U128 *bitboard, int k);
void Bitboard_unite(U128 *bitboard, const U128 *mask);
void Bitboard_clear_with(U128 *bitboard, const U128 *mask);

#endif
