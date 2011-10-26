#ifndef BOARD_H_
#define BOARD_H_

#include <stdio.h>
#include <stdlib.h>

#define PIECE_EMPTY	0
#define PIECE_PAWN	1
#define PIECE_ROOK	2
#define PIECE_KNIGHT	3
#define PIECE_BISHOP	4
#define PIECE_QUEEN	5
#define PIECE_KING	6

#define TEAM_WHITE 0
#define TEAM_BLACK 1

typedef char coordinate_t[2];

typedef struct piece_s
{
	char team;
	char type;

} piece_t;

typedef piece_t board_t[8][8];

void board_init();

void board_print(board_t b);

void board_move(board_t b, int team, char* src, char* dest);

void cn_to_coord(char* cn, coordinate_t coord);

void coord_to_cn(coordinate_t coord, char* cn);

#endif
