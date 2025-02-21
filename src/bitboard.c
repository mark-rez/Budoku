#include <stdint.h>
#include "bitboard.h"

const U128 ROWS[] = {
    {511ULL, 0ULL}, 
    {261632ULL, 0ULL},
    {133955584ULL, 0ULL},
    {68585259008ULL, 0ULL},
    {35115652612096ULL, 0ULL},
    {17979214137393152ULL, 0ULL},
    {9205357638345293824ULL, 0ULL},
    {9223372036854775808ULL, 255ULL},
    {0ULL, 130816ULL}
};

const U128 COLUMNS[] = {
    {9241421688590303745ULL, 256ULL},
    {36099303471055874ULL, 513ULL},
    {72198606942111748ULL, 1026ULL},
    {144397213884223496ULL, 2052ULL},
    {288794427768446992ULL, 4104ULL},
    {577588855536893984ULL, 8208ULL},
    {1155177711073787968ULL, 16416ULL},
    {2310355422147575936ULL, 32832ULL},
    {4620710844295151872ULL, 65664ULL}
};

const U128 SQUARES[] = {
    {1838599ULL, 0ULL},
    {14708792ULL, 0ULL},
    {117670336ULL, 0ULL},
    {246772580483072ULL, 0ULL},
    {1974180643864576ULL, 0ULL},
    {15793445150916608ULL, 0ULL},
    {9349472826421149696ULL, 1795ULL},
    {1008806316530991104ULL, 14364ULL},
    {8070450532247928832ULL, 114912ULL}
};

void Bitboard_set_at(U128 *bitboard, int k) {
    if (k < 64) {
        bitboard->low |= (1ULL << k);
    } else {
        bitboard->high |= (1ULL << (k - 64));
    }
}

void Bitboard_clear_at(U128 *bitboard, int k) {
    if (k < 64) {
        bitboard->low &= ~(1ULL << k);
    } else {
        bitboard->high &= ~(1ULL << (k - 64));
    }
}

void Bitboard_unite(U128 *bitboard, const U128 *mask) {
    bitboard->low |= mask->low;
    bitboard->high |= mask->high;
}

void Bitboard_clear_with(U128 *bitboard, const U128 *mask) {
    bitboard->low &= ~mask->low;
    bitboard->high &= ~mask->high;
}

int Bitboard_is_set_at(const U128 *bitboard, int k) {
    if (k < 64) {
        return (bitboard->low & (1ULL << k)) != 0;
    } else {
        return (bitboard->high & (1ULL << (k - 64))) != 0;
    }
}