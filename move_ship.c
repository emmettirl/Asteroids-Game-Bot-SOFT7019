#include "asteroids.h"


int findShipRow(int field[][FIELD_WIDTH]);
int checkForCollision(int field[][FIELD_WIDTH], int currentColumn, int shipRow);
int checkForOutOfBounds(int shipRow);
int* findValidMoves(int field[][FIELD_WIDTH], int shipRow, int offsetTracker, int currentColumn);
int findValidPath(int field[][FIELD_WIDTH],int  *validPathFound, int shipRow, int offsetTracker, int currentColumn, int *longestPathLength, int *longestPathMove, int currentMove);

//this program calculates the next move for the ship.
//it does this by finding the ship's row, then checking for valid moves
//it then determines the best move to make based on the valid moves, by attempting to stay near the centre of the field.
//it also tries to find a path which reaches the end of the frame, and ensure the selected move is part of that path.
//if no valid path is found, it will select the longest path found.

struct ship_action move_ship(int field[][FIELD_WIDTH], void *ship_state){
    // Your code should go here

    int nextMove = 0;

    int offsetTracker = 0; //track how far the ship has moved up or down when checking for a valid path
    int longestPathLength = 0;
    int longestPathMove = 0;

    int validPathFound = 0;

    int shipRow = findShipRow(field); //Find the ship's row
    int currentColumn = 1; //track the current column the ship is in

    //find valid next moves
    int *validMoves = findValidMoves(field, shipRow, offsetTracker, currentColumn);

    int counter = 0;
    int maxIterations = 1000;
    while (counter <= maxIterations) {
        counter++;

        if (counter == maxIterations) {
            nextMove = longestPathMove;
            break;
        }

        //determine next move from valid options, attempts to stay near centre of the field where possible
        if (validMoves[1] == 1) {
            nextMove = 0;
            if (findValidPath(field, &validPathFound, shipRow, offsetTracker, currentColumn, &longestPathLength, &longestPathMove, nextMove)){
                break;
            } else {
                validMoves[1] = 0;
                continue;
            }

        } else if (shipRow > 10) {
            if (validMoves[0] == 1) {
                nextMove = -1;
                if (findValidPath(field, &validPathFound, shipRow, offsetTracker, currentColumn, &longestPathLength, &longestPathMove, nextMove)){
                    break;
                } else {
                    validMoves[0] = 0;
                    continue;
                }
            } else {
                nextMove = 1;
                if (findValidPath(field, &validPathFound, shipRow, offsetTracker, currentColumn, &longestPathLength, &longestPathMove, nextMove)){
                    break;
                } else {
                    validMoves[0] = 0;
                    continue;
                }
            }
        } else {
            if (validMoves[2] == 1) {
                nextMove = 1;
                if (findValidPath(field, &validPathFound, shipRow, offsetTracker, currentColumn, &longestPathLength, &longestPathMove, nextMove)){
                    break;
                } else {
                    validMoves[2] = 0;
                    continue;
                }
            } else {
                nextMove = -1;
                if (findValidPath(field, &validPathFound, shipRow, offsetTracker, currentColumn, &longestPathLength, &longestPathMove, nextMove)){
                    break;
                } else {
                    validMoves[2] = 0;
                    continue;
                }
            }
        }


    }


    free(validMoves);

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
    return -1;
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

int* findValidMoves(int field[][FIELD_WIDTH], int shipRow, int offsetTracker, int currentColumn) {
    int *validMoves = (int *) malloc(3 * sizeof(int));
        for (int i = -1; i <= 1; i++) {
        if (checkForOutOfBounds(shipRow + i) != 1 && checkForCollision(field, currentColumn, shipRow + i) != 1) {
            validMoves[i + 1] = 1;
        }
    }
    return validMoves;
}

int findValidPath(int field[][FIELD_WIDTH], int *validPathFound, int shipRow, int offsetTracker, int currentColumn, int *longestPathLength, int *longestPathMove, int currentMove) {



    //check for successfully reaching the end of the field
    if (currentColumn + 1 == FIELD_WIDTH) {
        *validPathFound = 1;
        return 1;
    }
    if (*validPathFound == 1) {
        return 1;
    }

    //find valid moves for current column
    int *validMoves = findValidMoves(field, shipRow + offsetTracker, offsetTracker, currentColumn);


    currentColumn++;


        for (int j = -1; j <= 1; j++) {
            if (validMoves[j + 1] == 1) {
                findValidPath(field, validPathFound, shipRow, offsetTracker + j, currentColumn, longestPathLength, longestPathMove, currentMove);
            } else if (j == 1) {
                if (*longestPathLength < currentColumn) {
                    *longestPathLength = currentColumn;
                    *longestPathMove = currentMove;
            }
            }

    }


    if (*validPathFound == 1) {
        return 1;
    } else {
        return 0;
    }

}