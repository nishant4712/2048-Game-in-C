#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define SIZE 4

void initializeGrid(int grid[SIZE][SIZE]);
void printGrid(int grid[SIZE][SIZE]);
void addRandomNumber(int grid[SIZE][SIZE]);
void rotateGrid(int grid[SIZE][SIZE]);
int moveLeft(int grid[SIZE][SIZE]);
int mergeLeft(int row[SIZE]);
int canMove(int grid[SIZE][SIZE]);
int checkWin(int grid[SIZE][SIZE]);

int main() {
    int grid[SIZE][SIZE];
    char command;
    int moved;

    srand(time(NULL));
    initializeGrid(grid);
    addRandomNumber(grid);

    while (1) {
        system("cls");
        printGrid(grid);

        if (checkWin(grid)) {
            printf("You win!\n");
            break;
        }

        printf("Use WASD to move (Q to quit): ");
        command = _getch();

        if (command == 'q' || command == 'Q') {
            printf("Quitting...\n");
            break;
        }

        int oldGrid[SIZE][SIZE];
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                oldGrid[i][j] = grid[i][j];
            }
        }

        switch (command) {
            case 'a':
                moved = moveLeft(grid);
                break;
            case 'd':
                rotateGrid(grid);
                rotateGrid(grid);
                moved = moveLeft(grid);
                rotateGrid(grid);
                rotateGrid(grid);
                break;
            case 'w':
                rotateGrid(grid);
                rotateGrid(grid);
                moved = moveLeft(grid);
                rotateGrid(grid);
                rotateGrid(grid);
                break;
            case 's':
                rotateGrid(grid);
                moved = moveLeft(grid);
                rotateGrid(grid);
                rotateGrid(grid);
                rotateGrid(grid);
                break;
            default:
                printf("Invalid command.\n");
                continue;
        }

        if (moved) {
            addRandomNumber(grid);
            if (!canMove(grid)) {
                printf("Game Over!\n");
                break;
            }
        }
    }

    return 0;
}

void initializeGrid(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = 0;
        }
    }
}

void printGrid(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0) {
                printf(". ");
            } else {
                printf("%d ", grid[i][j]);
            }
        }
        printf("\n");
    }
}

void addRandomNumber(int grid[SIZE][SIZE]) {
    int emptyCells[SIZE * SIZE][2];
    int emptyCount = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0) {
                emptyCells[emptyCount][0] = i;
                emptyCells[emptyCount][1] = j;
                emptyCount++;
            }
        }
    }

    if (emptyCount == 0) return;

    int index = rand() % emptyCount;
    int row = emptyCells[index][0];
    int col = emptyCells[index][1];
    grid[row][col] = (rand() % 10 == 0) ? 4 : 2;
}

void rotateGrid(int grid[SIZE][SIZE]) {
    int temp;
    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = i; j < SIZE - i - 1; j++) {
            temp = grid[i][j];
            grid[i][j] = grid[SIZE - j - 1][i];
            grid[SIZE - j - 1][i] = grid[SIZE - i - 1][SIZE - j - 1];
            grid[SIZE - i - 1][SIZE - j - 1] = grid[j][SIZE - i - 1];
            grid[j][SIZE - i - 1] = temp;
        }
    }
}

int moveLeft(int grid[SIZE][SIZE]) {
    int moved = 0;

    for (int i = 0; i < SIZE; i++) {
        moved |= mergeLeft(grid[i]);
    }
    
    return moved;
}

int mergeLeft(int row[SIZE]) {
    int moved = 0;
    int temp[SIZE] = {0};
    int index = 0;

    for (int i = 0; i < SIZE; i++) {
        if (row[i] != 0) {
            if (index > 0 && temp[index - 1] == row[i]) {
                temp[index - 1] *= 2;
                moved = 1;
            } else {
                temp[index++] = row[i];
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        if (row[i] != temp[i]) {
            moved = 1;
            row[i] = temp[i];
        }
    }

    return moved;
}

int canMove(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0) return 1;
            if (i < SIZE - 1 && grid[i][j] == grid[i + 1][j]) return 1;
            if (j < SIZE - 1 && grid[i][j] == grid[i][j + 1]) return 1;
        }
    }
    return 0;
}

int checkWin(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] >= 2048) return 1;
        }
    }
    return 0;
}