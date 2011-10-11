#include "board.h"

board_t* board_create()
{
	board_t* b = calloc(1, sizeof(board_t));

	int i;
	for(i = 0; i < 2; i++)
	{
		b->places[0][i * 7].type = PIECE_ROOK;
		b->places[0][i * 7].team = i;

		b->places[1][i * 7].type = PIECE_KNIGHT;
		b->places[1][i * 7].team = i;

		b->places[2][i * 7].type = PIECE_BISHOP;
		b->places[2][i * 7].team = i;

		b->places[3 + i][i * 7].type = PIECE_QUEEN;
		b->places[3 + i][i * 7].team = i;

		b->places[4 - i][i * 7].type = PIECE_KING;
		b->places[4 - i][i * 7].team = i;

		b->places[5][i * 7].type = PIECE_BISHOP;
		b->places[5][i * 7].team = i;

		b->places[6][i * 7].type = PIECE_KNIGHT;
		b->places[6][i * 7].team = i;

		b->places[7][i * 7].type = PIECE_ROOK;
		b->places[7][i * 7].team = i;
	}

	for(i = 0; i < 8; i++)
	{
		 b->places[i][1].type = PIECE_PAWN;
		 b->places[i][1].team = 0;

		 b->places[i][6].type = PIECE_PAWN;
		 b->places[i][6].team = 1;
	}

	return b;
}

void board_destroy(board_t* b)
{
	free(b);
}

void board_print(board_t* b)
{
	printf("        A   B   C   D   E   F   G   H\n\n");

	int i;
	for(i = 0; i < 8; i++)
	{
		printf("%i      ", i);

		int j;
		for(j = 0; j < 8; j++)
		{
			char team_char = (b->places[i][j].team) ? '+' : '-';

			switch(b->places[i][j].type)
			{
				case PIECE_ROOK:   printf("%cR  ", team_char); break;
				case PIECE_KNIGHT: printf("%cKn ", team_char); break;
				case PIECE_BISHOP: printf("%cB  ", team_char); break;
				case PIECE_QUEEN:  printf("%cQ  ", team_char); break;
				case PIECE_KING:   printf("%cK  ", team_char); break;
				case PIECE_PAWN:   printf("%cP  ", team_char); break;
				case PIECE_EMPTY:  printf(" .  "); 	       break;
			};
		}

		printf("\n");
	}
}
