#include "board.h"

#include <math.h>
#include <string.h>

const char* piece_names[] = {NULL, "pawn", "rook", "knight", "bishop", "queen", "king"};

void cn_to_coord(char* cn, coordinate_t coord);

void board_init(board_t b)
{
	memset(b, 0, sizeof(piece_t) * (8 * 8));

	/* Initialize the team of each place to -1 so that we don't have empty spaces
	parading around like they're part of the black team */

	int i, j;
	for(i = 0; i < 8; i++)
		for(j = 0; j < 8; j++)
			b[i][j].team = -1;

	for(i = 0; i < 2; i++)
	{
		b[i * 7][0].type = PIECE_ROOK;
		b[i * 7][0].team = (i == 0) ? TEAM_WHITE : TEAM_BLACK;

		b[i * 7][1].type = PIECE_KNIGHT;
		b[i * 7][1].team = (i == 0) ? TEAM_WHITE : TEAM_BLACK;

		b[i * 7][2].type = PIECE_BISHOP;
		b[i * 7][2].team = (i == 0) ? TEAM_WHITE : TEAM_BLACK;

		b[i * 7][3 + i].type = PIECE_QUEEN;
		b[i * 7][3 + i].team = (i == 0) ? TEAM_WHITE : TEAM_BLACK;

		b[i * 7][4 - i].type = PIECE_KING;
		b[i * 7][4 - i].team = (i == 0) ? TEAM_WHITE : TEAM_BLACK;

		b[i * 7][5].type = PIECE_BISHOP;
		b[i * 7][5].team = (i == 0) ? TEAM_WHITE : TEAM_BLACK;

		b[i * 7][6].type = PIECE_KNIGHT;
		b[i * 7][6].team = (i == 0) ? TEAM_WHITE : TEAM_BLACK;

		b[i * 7][7].type = PIECE_ROOK;
		b[i * 7][7].team = (i == 0) ? TEAM_WHITE : TEAM_BLACK;
	}

	for(i = 0; i < 8; i++)
	{
		 b[1][i].type = PIECE_PAWN;
		 b[1][i].team = TEAM_WHITE;

		 b[6][i].type = PIECE_PAWN;
		 b[6][i].team = TEAM_BLACK;
	}
}

void board_print(board_t b)
{
	printf("     A    B    C    D    E    F    G    H\n\n");

	int i;
	for(i = 0; i < 8; i++)
	{
		printf("%i  ", (8 - i));

		int j;
		for(j = 0; j < 8; j++)
		{
			char team_char = (b[j][i].team == TEAM_WHITE) ? '+' : '-';

			switch(b[j][i].type)
			{
				case PIECE_ROOK:   printf(" %cR  ", team_char); break;
				case PIECE_KNIGHT: printf(" %cKn ", team_char); break;
				case PIECE_BISHOP: printf(" %cB  ", team_char); break;
				case PIECE_QUEEN:  printf(" %cQ  ", team_char); break;
				case PIECE_KING:   printf(" %cK  ", team_char); break;
				case PIECE_PAWN:   printf(" %cP  ", team_char); break;
				case PIECE_EMPTY:  printf("  .  "); 		break;
			};
		}

		printf("\n\n");
	}
}

void board_move(board_t b, int team, char* src_cn, char* dest_cn)
{
	coordinate_t src_coord, dest_coord;

	cn_to_coord(src_cn, src_coord);
	cn_to_coord(dest_cn, dest_coord);

	char piece_type = b[src_coord[0]][src_coord[1]].type;

	if(b[src_coord[0]][src_coord[1]].team == team && is_valid_move(b, src_coord, dest_coord))
	{
		b[dest_coord[0]][dest_coord[1]].type = b[src_coord[0]][src_coord[1]].type;
		b[dest_coord[0]][dest_coord[1]].team = b[src_coord[0]][src_coord[1]].team;

		b[src_coord[0]][src_coord[1]].type = 0;
		b[src_coord[0]][src_coord[1]].team = -1;
	}
	else
		printf("Invalid move.\n");
}

// Convert chess notation to internal coordinates
void cn_to_coord(char* cn, coordinate_t coord)
{
	coord[0] = (cn[0] - 'A');
	coord[1] = 8 - (cn[1] - '0');
}

// Convert internal coordinates to chess notation
void coord_to_cn(coordinate_t coord, char* cn)
{
	memset(cn, 0, 3);

	cn[0] = coord[0] + 'A';
	cn[1] = coord[1] + '0';
}

// Confirm that a given move is legal
int is_valid_move(board_t b, coordinate_t src, coordinate_t dest)
{
	int i, j;
	for(i = 0; i < 2; i++)
	{
		if(src[i]  < 0 || src[i]  > 8) return 0;
		if(dest[i] < 0 || dest[i] > 8) return 0;
	}

	char src_type  = b[ src[0]][ src[1]].type,  src_team = b[ src[0]][ src[1]].team;
	char dest_type = b[dest[0]][dest[1]].type, dest_team = b[dest[0]][dest[1]].team;

	char direction = (src_team == TEAM_WHITE) ? 1 : -1;

	// This is no time for civil war
	if(dest_team == src_team) return 0;

	switch(src_type)
	{
		case PIECE_ROOK:
		break;

		case PIECE_KNIGHT:
			if(abs(dest[0] - src[0]) == 2 && abs(dest[1] - src[1]) == 1)
				return 1;
			if(abs(dest[0] - src[0]) == 1 && abs(dest[1] - src[1]) == 2)
				return 1;
		break;

		case PIECE_BISHOP:
		break;

		case PIECE_QUEEN:
		break;

		case PIECE_KING:
			if(dest_team != src_team && abs(dest[0] - src[0]) == 1 && abs(dest[1] - src[1]) == 1)
				return 1;
		break;

		case PIECE_PAWN:
			if(dest_type != 0 && dest_team != src_team && dest[0] - src[0] == direction && abs(dest[1] - src[1]) == 1)
				return 1;
			if(!dest_type && !b[dest[0]][dest[1]].type && src[0] == (src_team == TEAM_WHITE ? 1 : 6) && dest[1] == src[1] && dest[0] - src[0] == (2 * direction))
				return 1;
			if(!dest_type && dest[1] == src[1] && (dest[0] - src[0]) == direction)
				return 1;
		break;

		case PIECE_EMPTY: break;
	};

	return 0;
}
