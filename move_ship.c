#include "asteroids.h"


int findShipRow(int field[][FIELD_WIDTH]);
int checkForCollision(int field[][FIELD_WIDTH], int currentColumn, int shipRow);
int checkForOutOfBounds(int shipRow);


struct ship_action move_ship(int field[][FIELD_WIDTH], void *ship_state){
    // Your code should go here

    int nextMove = 0;

    int longestPathLength = 0;
    int longestPathMove = 0;

    int validPathFound = 0;

    int shipRow = findShipRow(field); //Find the ship's row
    int offsetTracker = 0; //track how far the ship has moved up or down when checking for a valid path


    //iterate through each move option to determine first move
    for (int i = -1; i <= 1; i++) {
        offsetTracker = i;


        //check if the move is valid (not out of bounds)
        if (checkForOutOfBounds(shipRow + offsetTracker)) {
            continue;
        };



        //loop to iterate through field width and find a valid path
        for (int j = 0; j < FIELD_WIDTH; j++) {

            //check if the move is valid (not hitting an asteroid)
            if (checkForCollision(field, j, shipRow + offsetTracker)) {
                break;
            }

            if (j + 1 == FIELD_WIDTH) {
                validPathFound = 1;

            if (j > longestPathLength) {
            longestPathLength = j;
            longestPathMove = nextMove;
                }
            }
        }

        if (validPathFound) {
            nextMove = i;
            break;
        }

    }
    //struct creation and return
    struct ship_action turn = {nextMove, ship_state};
    return turn;
}

int findShipRow(int field[][FIELD_WIDTH]) {
    // Find the ship's row, using both rows and columns to protect from collisions preventing detection.
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < SHIP_WIDTH; j++) {
            if (field[i][j] == SHIP_VAL) {
                return i;
            }
        }
    }
}

int checkForCollision(int field[][FIELD_WIDTH], int currentColumn, int shipRow) {
    for (int i = 0; i < SHIP_WIDTH; i++) {
        if (field[shipRow][currentColumn + i] != 0 && field[shipRow][currentColumn+ i] != 2) {
            return 1;
        }
    }
    return 0;
}

int checkForOutOfBounds(int shipRow) {
    if (shipRow < 0 || shipRow >= FIELD_HEIGHT) {
        return 1;
    }
    return 0;
}