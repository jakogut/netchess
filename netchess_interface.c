#include "netchess_interface.h"

const char* commands[] = {"q", "help", "board", "move", "undo", "turn", 0};

const char* team_names[] = {"White(+)", "Black(-)"};

void nci_help()
{
        printf( "NetChess follows standard chess rules."
                "\nThe game starts with the white team making the first move."

                "\n\nCOMMAND		EFFECT"
                "\nq		Quit"

                "\n\nhelp       \tPrint documentation"

                "\n\nboard      \tPrint the game board"

                "\n\nmove       \tTakes two chess coordinates as arguments,"
                "\n             \tand sets a piece to be moved at the end of the turn."

		"\n\nundo	\tUndo any pending move"

                "\n\nturn       \tEnds the current player's turn, and"
                "\n             \tfinalizes their moves"

                "\n\n" );
}

void nci_shell(board_t board)
{
        int run = 1;
        char* tokens[MAX_TOKENS];
        char  str[MAX_INPUT_LENGTH];

        uint8_t team = 0, turn_change = 0;

        board_t temp_board;
        memcpy(temp_board, board, sizeof(piece_t) * (8 * 8));

        for(int i = 0; i < MAX_TOKENS; i++) tokens[i] = malloc(TOKEN_LENGTH + 1);

        printf("Game starts with the %s team.\n", team_names[team]);

        while(run)
        {
                if(turn_change)
                {
                        turn_change = 0;

			if(nce_check(board, team)) printf("*-- You are in check. --*\n");
                        printf("%s team moves\n: ", team_names[team]);
                }
                         else printf(": ");

                for(int i = 0; i < MAX_TOKENS; i++) memset(tokens[i], 0, TOKEN_LENGTH);

                fgets(str, MAX_INPUT_LENGTH, stdin);
                tokenize(str, (char**)tokens);

                switch(cmd_to_idx(change_case(0, tokens[0])))
                {
/* Invalid Command */	case -0x1:
				printf("\n\"%s\" is not a valid command. Type \"help\" for instructions.\n", tokens[0]);
                        break;
/* Quit */		case  0x0:
				run = 0;
                        break;
/* Help */		case  0x1:
				nci_help();
                        break;
/* Print Board */	case  0x2:
				nce_print(temp_board);
			break;
/*  Move */		case  0x3:
				memcpy(temp_board, board, sizeof(piece_t) * (8 * 8));
				nce_move(temp_board, team, tokens[1], tokens[2]);
			break;
/* Undo */		case  0x4:
				memcpy(temp_board, board, sizeof(piece_t) * (8 * 8));
				printf("Pending moves undone.\n");
			break;
/* Turn */		case  0x5:
				switch(nce_evaluate(temp_board))
				{
					case 0:
						memcpy(board, temp_board, sizeof(piece_t) * (8 * 8));
						team ^= 1, turn_change = 1;
					break;
	/* White Check */		case 1:
						if(team == TEAM_WHITE) printf("You may not end your turn in check.\n");
						memcpy(temp_board, board, sizeof(piece_t) * (8 * 8));
					break;
	/* White Mate */		case 2:
					break;
	/* Black Check */		case 3:
						if(team == TEAM_BLACK) printf("You may not end your turn in check.\n");
						memcpy(temp_board, board, sizeof(piece_t) * (8 * 8));
					break;
	/* Black Mate */		case 4:
					break;
				};
			break;
		};
	}

	for(int i = 0; i < MAX_TOKENS; i++) free(tokens[i]);
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

// Convert a text command to a corresponding instruction index
int cmd_to_idx(char* cmd)
{
        int i;
        for(i = 0; commands[i]; i++)
                if(strcmp(cmd, commands[i]) == 0) return i;

        return -1;
}
