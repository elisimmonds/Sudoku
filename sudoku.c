// Eli Simmonds
// Homework 3
// Sudoku.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>

#define length 9
#define correctSize 45

void printBoard(char board[][length]);
void rowContainsDigits(char board[][length], int row);
void colContainsDigits(char board[][length], int col);
void subGridContainsDigits(char board[][length], int row, int col);

int main (int argc, char * argv[]) {
    char sudokuBoard[9][9];
    
    FILE *ifp;
    char *mode = "r";
    printf("%s\n", argv[1]);
    ifp = fopen(argv[1], mode);
    if (ifp == NULL) {
        fprintf(stderr, "Can't open input input file!\n");
        exit(1);
    }
    
    char c = fgetc(ifp);
    int row, col = 0;
    while (c != EOF) {
        if (c != ' ') {
//            printf("%c (%i, %i)\n", c, row, col);
            sudokuBoard[row][col] = c;
            col++;
        }
        c = fgetc(ifp);
        if (col == 9) {
            row++;
            col = 0;
        }
    }
    printBoard(sudokuBoard);
    
    for (int i = 0; i < length; i++) {
        rowContainsDigits(sudokuBoard, i);
        colContainsDigits(sudokuBoard, i);
    }
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            subGridContainsDigits(sudokuBoard, j, k);
        }
    }
    
    
}

void rowContainsDigits(char board[][length], int row) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
//        printf(" %c ", board[row][i]);
        sum += board[row][i] - '0';
    }
//    printf(" sum: %i    correct: %i \n", sum, correctSize);
    if (sum != correctSize) {
        printf("\nRow %i doesn't have the required values.\n", row);
    }
}

void colContainsDigits(char board[][length], int col) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
//        printf(" %c ", board[i][col]);
        sum += board[i][col] - '0';
    }
//    printf(" sum: %i    correct: %i \n", sum, correctSize);
    if (sum != correctSize) {
        printf("\nColumn %i doesn't have the required values.\n", col);
    }
}

void subGridContainsDigits(char board[][length], int row, int col) {
    int sum = 0;
    int tempRow = row * 3;
    int tempCol = col * 3;
    for (int r = tempRow; r < tempRow + 3; r++) {
        for (int c = tempCol; c < tempCol + 3; c++) {
//            printf(" %c ", board[r][c]);
            sum += board[r][c] - '0';
        }
//        printf("\n");
    }
//    printf(" sum: %i    correct: %i \n", sum, correctSize);
    if (sum != correctSize) {
        printf("\nSubgrid[%i][%i] doesn't have the required values. Sum = %i \n", row, col, sum);
    }
}


void printBoard (char board[][length]) {
    printf("\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%c ", board[i][j]);
            if((j + 1) % 3 == 0) {
                printf("\t");
            }
        }
        if ((i+1) % 3 == 0) {
            printf("\n");
        }
        printf("\n");
    }
}

