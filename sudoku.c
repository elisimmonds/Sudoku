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
    
//    rowContainsDigits(sudokuBoard);
//    colContainsDigits(sudokuBoard);
    
    pthread_t rows, cols;

    pthread_create(&rows, NULL, rowContainsDigits, (void *) sudokuBoard);
//    pthread_create(&cols, NULL, colContainsDigits, (void *) colStruct);

    void * returnRows;
    void * returnCols;
    
    pthread_join(rows, returnRows);
//    pthread_join(cols, returnCols);
    
    
    
//    if ((int) returnRows == 1 && (int) returnCols == 1) {
//    printf("rows return %i \n", (int) returnRows);
//    if ((int) returnRows == 1) {
//    if ((int) returnCols == 1) {
//        printf("Sudoku is valid\n");
//    } else {
//        printf("Sudoku is invalid\n");
//    }
    

}

void rowContainsDigits(char board[][length]) {
//    char board[length][length] = param->sudokuBoard;
//    param * board = param;
    for (int j = 0; j < length; j++) {
        int sum = 0;
        for (int i = 0; i < length; i++) {
            sum += board[j][i] - '0';
        }
        if (sum != correctSize) {
            printf("\nRow %i doesn't have the required values.\n", j);
//            return (void *) 0;
        }
    }
//    return (void *) 1;
}

void colContainsDigits(char board[][length]) {
    for (int j = 0; j < length; j++) {
        int sum = 0;
        for (int i = 0; i < length; i++) {
            //        printf(" %c ", board[i][col]);
            sum += board[i][j] - '0';
        }
        //    printf(" sum: %i    correct: %i \n", sum, correctSize);
        if (sum != correctSize) {
            printf("\nColumn %i doesn't have the required values.\n", j);
        }
    }
}

void subGridContainsDigits(char board[][length], int row, int col) {
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

