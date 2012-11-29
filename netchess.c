#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "netchess_interface.h"
#include "netchess_engine.h"

int main()
{
	board_t b;
	nce_init(b);

	nci_shell(b);

	return 0;
}
