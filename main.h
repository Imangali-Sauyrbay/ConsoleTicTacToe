#ifndef _TICTAKTOE_
#define _TICTAKTOE_

#include <stdint.h>

#define WHITESPACE_CHAR ' '
#define WHITESPACE 0
#define PLAYER_ONE 1
#define PLAYER_TWO 2
#define PLAYER_ONE_CHAR 'X'
#define PLAYER_TWO_CHAR 'O'

void printBoard(uint8_t**, uint32_t);
void clearConsole();
void clearBoard(uint8_t**, uint8_t);
uint8_t** mallocBoard(uint8_t);
void freeBoard(uint8_t**, uint8_t);
void printTurn(uint8_t);
void getInput(uint8_t**, uint8_t, uint8_t);
uint8_t checkBoard(uint8_t**, uint32_t);
bool doesBoardHaveFreeSpace(uint8_t**, uint8_t);

#endif