#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"

int main(int argc, char** argv) {
    size_t size = 3;
    bool isGameOver = 0;
    uint8_t** board =  mallocBoard(size);

    bool turnFlag = false;
    uint8_t player;
    while(!isGameOver) {
        clearConsole();
        printBoard(board, size);
        printTurn(turnFlag);
        getInput(board, size, turnFlag ? PLAYER_TWO : PLAYER_ONE);

        if(player = checkBoard(board, size)) {
            isGameOver = true;
            clearConsole();
            printf("\n\n\t\t\tPLAYER %d WINS!!!\n\n", player);
            printBoard(board, size);
            printf("\n\n\n");
        }

        if(!doesBoardHaveFreeSpace(board, size)) {
            isGameOver = true;
            clearConsole();
            printf("\n\n\t\t\\tTie!!\n\n");
            printBoard(board, size);
            printf("\n\n\n");
        }

        turnFlag = !turnFlag;
    }

    freeBoard(board, size);
    return 0;
}

uint8_t checkBoard(uint8_t** board, uint32_t size) {
    for (size_t i = 0; i < size; i++)
    {
        // Check Rows
        if(
            board[i][0] != WHITESPACE &&
            board[i][0] == board[i][1] && board[i][1] == board[i][2]
        ) {
            uint8_t player = board[i][0];
            clearBoard(board, size);
            board[i][0] = board[i][1] = board[i][2] = player;

            return player;
        }

        // Check Columns
        if(
            board[0][i] != WHITESPACE &&
            board[0][i] == board[1][i] && board[1][i] == board[2][i]
        )
        {
            uint8_t player = board[0][i];
            clearBoard(board, size);
            board[0][i] = board[1][i] = board[2][i] = player;
            return player;
        }

        // First Diag

        if(
            board[0][0] != WHITESPACE &&
            board[0][0] == board[1][1] && board[1][1] == board[2][2]
        ) {
            uint8_t player = board[0][0];
            clearBoard(board, size);
            board[0][0] = board[1][1] = board[2][2] = player;

            return player;
        }

        // Second Diag
        if(
            board[0][2] != WHITESPACE &&
            board[0][2] == board[1][1] && board[1][1] == board[2][0]
        ) {
            uint8_t player = board[0][2];
            clearBoard(board, size);
            board[0][2] = board[1][1] = board[2][0] = player;

            return player;
        }
    }

    return 0;
}

void printBoard(uint8_t** board, uint32_t size) {
    printf("\n\n");
    for (size_t i = 0; i < size; i++) {
        printf("\t\t\t");
        for (size_t j = 0; j < size; j++) {
            char cell = WHITESPACE_CHAR;

            if (board[i][j] == PLAYER_ONE) {
                cell = PLAYER_ONE_CHAR;
            }
            
            if (board[i][j] == PLAYER_TWO) {
                cell = PLAYER_TWO_CHAR;
            }

            printf("[ %c ] ", cell);
        }
        
        printf("\n\n");
    }
}

void clearConsole() {
    printf("\033[2J\033[1;1H");
}

uint8_t** mallocBoard(uint8_t size) {
    uint8_t** board;

    board = malloc(sizeof(uint8_t) * size);
    
    for (size_t i = 0; i < size; i++) {
        board[i] = malloc(sizeof(uint8_t) * size);
    }

    return board;
}

void freeBoard(uint8_t** board, uint8_t size) {
    for (size_t i = 0; i < size; i++) {
        free(board[i]);
    }

    free(board);
}

void clearBoard(uint8_t** board, uint8_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++)
        {
            board[i][j] = 0;
        }
    }
}

bool doesBoardHaveFreeSpace(uint8_t** board, uint8_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++)
        {
            if(board[i][j] == 0)
                return true;
        }
    }

    return false;
}

void printTurn(uint8_t turnFlag) {
    printf("\n\t\t\t");
    if(turnFlag) {
        printf("Player 2 turn (O)!\n");
    } else {
        printf("Player 1 turn (X)!\n");
    }
}

void getInput(uint8_t** board, uint8_t size, uint8_t player) {
    size_t x, y;

    while (1)
    {
        do
        {
            printf("\n\t\t\tPlease select row (1 - %lld): ", size); 
            scanf("%lld", &x);
        } while (!x || x < 1 || x > size);

        do
        {
            printf("\n\t\t\tPlease select col (1 - %lld): ", size);
            scanf("%lld", &y);
        } while (!y || y < 1 || y > size);

        if(
            board[x - 1][y - 1] != PLAYER_ONE &&
            board[x - 1][y - 1] != PLAYER_TWO
        ) {
            break;
        }
        
        clearConsole();
        printBoard(board, size);
        printTurn(player);
        printf("\n\n\t\tThis place is already taken! try again!!!\n\n");
    }

    board[x - 1][y - 1] = player;
}
