#include "asteroids.h"


int findShipRow(int field[][FIELD_WIDTH]);
int checkForCollision(int field[][FIELD_WIDTH], int currentColumn, int shipRow);
int checkForOutOfBounds(int shipRow);
int* findValidMoves(int field[][FIELD_WIDTH], int shipRow, int offsetTracker, int currentColumn);



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

    //determine next move from valid options, attempts to stay near centre of the field where possible
    if (validMoves[1] == 1) {
        nextMove = 0;
    } else if (shipRow > 10)
    {
        if (validMoves[0] == 1) {
            nextMove = -1;
        } else {
            nextMove = 1;
        }
    } else {
        if (validMoves[2] == 1) {
            nextMove = 1;
        } else {
            nextMove = -1;
        }
    }

    offsetTracker += nextMove;
    longestPathLength ++;
    longestPathMove = nextMove;




//        int noValidPathFound = 0;
//
//        //loop to iterate through field width and find a valid path to end of field
//        for (int j = 0; j <= FIELD_WIDTH; j++) {
//
//            if (noValidPathFound == 1){
//                break;
//            };
//
//            //if loop at end of field, break out of loop as valid path has been found
//            if (j + 1 == FIELD_WIDTH) {
//                validPathFound = 1;
//                printf("Valid path found!\n");
//                break;
//            }

//            //simulate next move
//            for (int k = -1; k <= 1; k++) {
//
//                //check if the simulated move is not valid (out of bounds and not hitting an asteroid)
//                //if it is not, move on to next loop
//                if (checkForOutOfBounds(shipRow + offsetTracker) == 1 || checkForCollision(field, j, shipRow + offsetTracker) == 1){
//                    if (k < 1){
//                        continue;
//                    }
//                }else {
//                    //if the simulated move is valid, break out of the loop and update offset tracker
//                    offsetTracker += k;
//                    break;
//                }
//
//                //if the simulated move is the last move, and it is not valid, break out of the loop.
//                //Update the longest path move to reflect the current next move if the longest path length is less than the current path length
//                if (j > longestPathLength) {
//                    longestPathLength = j;
//                    longestPathMove = nextMove;
//                    noValidPathFound = 1;
//                }
//                else {
//                    noValidPathFound = 1;
//                }
//            }
//        }
//
//        //if a valid path is found, break out of the loop
//        if (validPathFound == 1) {
//            nextMove = i;
//            break;
//        }

//    //if no valid path is found, use the longest path move
//    if (validPathFound == 0) {
//        nextMove = longestPathMove;
//        printf("using longest path move\n");
//    }

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

int* findValidMoves(int field[][FIELD_WIDTH], int shipRow, int offsetTracker, int currentColumn) {
    int *validMoves = (int *) malloc(3 * sizeof(int));
        for (int i = -1; i <= 1; i++) {
        if (checkForOutOfBounds(shipRow + i) != 1 && checkForCollision(field, currentColumn, shipRow + i) != 1) {
            validMoves[i + 1] = 1;
        }
    }
    return validMoves;
}
