#ifndef NETCHESS_ENGINE_H_
#define NETCHESS_ENGINE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PIECE_EMPTY	0
#define PIECE_PAWN	1
#define PIECE_ROOK	2
#define PIECE_KNIGHT	3
#define PIECE_BISHOP	4
#define PIECE_QUEEN	5
#define PIECE_KING	6

#define TEAM_WHITE 0
#define TEAM_BLACK 1

typedef uint8_t coordinate_t[2];

typedef struct piece_s
{
	char team;
	char type;

} piece_t;

typedef piece_t board_t[8][8];

void nce_init();

void nce_print(board_t b);

void nce_move(board_t b, int team, char* src, char* dest);

int nce_evaluate(board_t b);

int clear_path(board_t b, coordinate_t src, coordinate_t dest);

void cn_to_coord(char* cn, coordinate_t coord);

void coord_to_cn(coordinate_t coord, char* cn);

/* Convert a string to a different case

        if case == 0, lower case
        if case == 1, upper case	*/
char* change_case(int new_case, char* str);

#endif
