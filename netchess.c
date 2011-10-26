#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"

#define MAX_TOKENS 3
#define TOKEN_LENGTH 32
#define MAX_INPUT_LENGTH 96

const char* commands[] = {"q", "help", "board", "move", "turn", 0};

const char* team_names[] = {"White", "Black"};

static void tokenize(char* str, char** tokens);
static int cmd_to_idx(char* cmd);

int victory_check(board_t b)
{
	return 0;
}

void print_help()
{
	printf("Help text here.\n");
}

void chess_shell(board_t board)
{
	int i, run = 1;
	char* tokens[MAX_TOKENS];
	char  str[MAX_INPUT_LENGTH];

	char team = 0, turn_change = 0;

	board_t temp_board;
	memcpy(temp_board, board, sizeof(piece_t) * (8 * 8));

	for(i = 0; i < MAX_TOKENS; i++) tokens[i] = malloc(TOKEN_LENGTH + 1);

	printf("Game starts with the white(+) team.\n");

	while(run)
	{
		if(turn_change)
		{
			printf("%s team moves\n: ", team_names[team]);
			turn_change = 0;
		}
			 else printf(": ");

		for(i = 0; i < MAX_TOKENS; i++) memset(tokens[i], 0, TOKEN_LENGTH);

		fgets(str, MAX_INPUT_LENGTH, stdin);
		tokenize(str, (char**)tokens);

		switch(cmd_to_idx(tokens[0]))
		{
			case -0x1:
				printf("\n\"%s\" is not a valid command. Type \"help\" for instructions.\n", tokens[0]);
			break;
			case  0x0:
				run = 0;
			break;
			case  0x1:
				print_help();
			break;
			case  0x2:
				board_print(temp_board);
			break;
			case  0x3:
				memcpy(temp_board, board, sizeof(piece_t) * (8 * 8));
				board_move(temp_board, team, tokens[1], tokens[2]);
			break;
			case  0x4:
				memcpy(board, temp_board, sizeof(piece_t) * (8 * 8));
				team ^= 1, turn_change = 1;
			break;
		};
	}
}

int main()
{
	board_t b;
	board_init(b);

	chess_shell(b);

	return 0;
}

void tokenize(char* str, char** tokens)
{
	int i = 0;
	char* token = strtok(str, "     \n");

	for(i = 0; token && (i < MAX_TOKENS); i++)
	{
		strcpy(tokens[i], token);
		token = strtok(NULL, "  \n");
	}
}

int cmd_to_idx(char* cmd)
{
	int i;
	for(i = 0; commands[i]; i++)
		if(strcmp(cmd, commands[i]) == 0) return i;

	return -1;
}

