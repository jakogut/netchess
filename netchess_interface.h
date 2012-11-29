#ifndef NETCHESS_INTERFACE_H_
#define NETCHESS_INTERFACE_H_

#define MAX_TOKENS 3
#define TOKEN_LENGTH 32
#define MAX_INPUT_LENGTH 96

#include <string.h>
#include <stdlib.h>

#include "netchess_engine.h"

void nci_help();

void nci_shell(board_t board);

void tokenize(char* str, char** tokens);
int cmd_to_idx(char* cmd);

#endif
