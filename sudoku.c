// Eli Simmonds
// Homework 3
// Sudoku.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <pthread.h>

#define length 9
#define correctSize 45

void printBoard(char board[][length]);
void rowContainsDigits(char board[][length]);
void colContainsDigits(char board[][length]);
void subGridContainsDigits(char board[][length], int row, int col);

typedef struct {
    int row, col;
    char ( * sudokuBoard)[length];
} param;

int main (int argc, char * argv[]) {
    char sudokuBoard[length][length];
    
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
    
    pthread_t rows, cols, subGrid;

    pthread_create(&rows, NULL, rowContainsDigits, (void *) sudokuBoard);
    pthread_create(&cols, NULL, colContainsDigits, (void *) sudokuBoard);
    pthread_create(&subGrid, NULL, subGridContainsDigits, (void *) sudokuBoard);

//    void * returnRows;
//    void * returnCols;
    
    pthread_join(rows, NULL);
    pthread_join(cols, NULL);
    
    
}

void rowContainsDigits(char board[][length]) {
    // checks each row for correct numbers
    for (int j = 0; j < length; j++) {
        int sum = 0;
        for (int i = 0; i < length; i++) {
            sum += board[j][i] - '0';
        }
        if (sum != correctSize) {
            printf("\nRow %i doesn't have the required values.\n", j);
        }
    }
}

void colContainsDigits(char board[][length]) {
    // checks each column for the correct values
    for (int j = 0; j < length; j++) {
        int sum = 0;
        for (int i = 0; i < length; i++) {
            sum += board[i][j] - '0';
        }
        if (sum != correctSize) {
            printf("\nColumn %i doesn't have the required values.\n", j);
        }
    }
}

void subGridContainsDigits(char board[][length], int row, int col) {
    /*
     Checks each subgrid referred to as the following:
      0  1  2
      ________
    0|  |  |  |
     |--|--|--|
    1|  |  |  |
     |--|--|--|
    2|  |  |  |
      --------
     */
    int sum = 0;
    int tempRow = row * 3;
    int tempCol = col * 3;
    for (int r = tempRow; r < tempRow + 3; r++) {
        for (int c = tempCol; c < tempCol + 3; c++) {
            sum += board[r][c] - '0';
        }
    }
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

