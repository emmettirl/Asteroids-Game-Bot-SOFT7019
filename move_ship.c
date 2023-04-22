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
        longestPathLength = 1;

        //check if the current move is not valid (out of bounds and not hitting an asteroid)
        //if it is not, move on to next loop
        if (checkForOutOfBounds(shipRow + offsetTracker) != 1 && checkForCollision(field, 1, shipRow + offsetTracker) != 1){
            nextMove = i;
            break;
        }

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
    }

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
                printf("Ship found at row %d.\n", i);
                return i;
            }
        }
    }
    printf ("Error: Ship not found.\n");
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