// Eli Simmonds & Ryan Graves
// Homework 3
// Sudoku.c

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>

#define length 9


void printBoard(char * board);
void *rowContainsDigits(char * board);
void *colContainsDigits(char * board);
void *subGridContainsDigits(char * board);

char * sudokuBoard;

int main (int argc, char * argv[]) {
    sudokuBoard = (char *)malloc(length * length * sizeof(char));

    FILE *ifp;
    char *mode = "r";
    ifp = fopen(argv[1], mode);
    if (ifp == NULL) {
        fprintf(stderr, "Can't open input input file!\n");
        exit(1);
    }
    char c = fgetc(ifp);
    int row = 0;
    int col = 0;
    while (c != EOF) {
        if (!isspace(c)) {
            *(sudokuBoard + row*length + col) = c;
            col++;
        }
        c = fgetc(ifp);
        if (isspace(c)) {
            c = fgetc(ifp);
        }
        if (col == 9) {
            row++;
            col = 0;
        }
    }
    printBoard(sudokuBoard);


    pthread_t rows[9];
    pthread_t cols[9];
    pthread_t subGrid[9];

    void * rowresult[length];
    void * colresult[length];
    void * subresult[length];

    for (int i = 0; i < length; i++) { // create threads
        pthread_create(&rows[i], NULL, rowContainsDigits, (void *) (sudokuBoard + i * length));
        pthread_create(&cols[i], NULL, colContainsDigits, (void *) (sudokuBoard + i));
        pthread_create(&subGrid[i], NULL, subGridContainsDigits,
                       (void *) (sudokuBoard + ((i / 3) * (3 * length)) + (i % 3) * 3 ));
    }
    
    for (int i = 0; i < length; i++) { // wait and join threads
        pthread_join(rows[i], &rowresult[i]);
        pthread_join(cols[i], &colresult[i]);
        pthread_join(subGrid[i], &subresult[i]);
    }


    int error = 0;

    for  (int i = 0; i < 9; i ++) {
        if ((int) rowresult[i] == 0) {
            printf("Row %d doesn't have the required values.\n", i + 1);
            error = 1;
        }
        if ((int) colresult[i] == 0) {
            printf("Column %d doesn't have the required values.\n", i + 1);
            error = 1;
        }
        if ((int) subresult[i] == 0) {
            char * location;
            switch (i) {
                case 0:
                    location = "top left";
                    break;
                case 1:
                    location = "top center";
                    break;
                case 2:
                    location = "top right";
                    break;
                case 3:
                    location = "left middle";
                    break;
                case 4:
                    location = "center";
                    break;
                case 5:
                    location = "right middle";
                    break;
                case 6:
                    location = "bottom left";
                    break;
                case 7:
                    location = "bottom center";
                    break;
                case 8:
                    location = "bottom right";
                    break;
            }
            printf("The %s subgrid doesn't have the required values.\n", location);
            error = 1;
        }
    }

    if (error == 0)
        printf("The input is a valid Sudoku.\n");
    else
        printf("The input is not a valid Sudoku.\n");

}

void *rowContainsDigits(char * board) {
    // checks A row for correct numbers
    int *inRow = (int *)malloc(length * sizeof(int));
    for (int i = 0; i < length; i++)
        *(inRow + i) = 0;
    for (int j = 0; j < length; j++) {
        if (*(inRow + *(board + j) - 1) == 1) {
            return (void *) 0;
        }
        if (*(inRow + *(board + j) - 1) == 0) {
            *(inRow + *(board + j) - 1) = 1;
        }
    }
    return (void *) 1; // correct board
}

void *colContainsDigits(char * board) {
    // checks A column for correct numbers
    int *inCol = (int *)malloc(length * sizeof(int));
    for (int i = 0; i < length; i++)
        *(inCol + i) = 0;
    for (int j = 0; j < length; j++) {
        if (*(inCol + *(board + j * length) - 1) == 1) {
            return (void *) 0;  // found bad val
        }
        if (*(inCol + *(board + j * length) - 1) == 0)
            *(inCol + *(board + j * length) - 1) = 1;
    }
    return (void *) 1; // correct board
}

void *subGridContainsDigits(char * board) {
    // checks A subgrid for the correct numbers
    int *inSubG = (int *)malloc(length * sizeof(int));
    for (int i = 0; i < length; i++)
        *(inSubG + i) = 0;
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            if (*(inSubG + *(board + j * length + k) - 1) == 1) {
                return (void *) 0;  // found bad val
            }
            if (*(inSubG + *(board + j * length + k) - 1) == 0)
                *(inSubG + *(board + j * length + k) - 1) = 1;
        }
    }
    return (void *) 1;

}


void printBoard (char * board) {
    // prints a formatted sudoku board
    printf("\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%c ", *(board + i*length + j));
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

