#include <stdio.h>
#include <stdlib.h>

#define PIECE_EMPTY	0
#define PIECE_PAWN	1
#define PIECE_ROOK	2
#define PIECE_KNIGHT	3
#define PIECE_BISHOP	4
#define PIECE_QUEEN	5
#define PIECE_KING	6

typedef struct piece_s
{
	char team;
	char type;

} piece_t;

typedef struct board_s
{
	piece_t places[8][8];

} board_t;


board_t* board_create();
void board_destroy(board_t* b);

void board_print(board_t* b);
