#include <stdio.h>
#include <stdlib.h>

#include "board.h"

int victory_check(board_t* b)
{
	return 0;
}

int main()
{
	board_t* b = board_create();

	board_print(b);

	board_destroy(b);

	return 0;
}
