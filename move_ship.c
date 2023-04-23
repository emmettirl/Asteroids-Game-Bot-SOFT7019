/*
Title: move_ship.c
Purpose: A script which calculates the next move for the ship.
Author: Emmett Fitzharris
Date: 23/04/2023
Project: Assignment 2 - COMP7019
Student ID: R00222357
 */

#include "asteroids.h"

int findShipRow(int field[][FIELD_WIDTH]);
int checkForCollision(int field[][FIELD_WIDTH], int currentColumn, int shipRow);
int checkForOutOfBounds(int shipRow);
int* findValidMoves(int field[][FIELD_WIDTH], int shipRow, int currentColumn);
int findValidPath(int field[][FIELD_WIDTH],int  *validPathFound, int shipRow, int offsetTracker, int currentColumn, int *longestPathLength, int *longestPathMove, int currentMove);

struct ship_action move_ship(int field[][FIELD_WIDTH], void *ship_state){
    // Your code should go here

    //create variable which are needed to manage the script
    int nextMove = 0;
    int offsetTracker = 0; //track how far the ship has moved up or down when checking for a valid path
    int longestPathLength = 0;
    int longestPathMove = 0;
    int validPathFound = 0;
    int shipRow = findShipRow(field); //Find the ship's row
    int currentColumn = 1; //track the current column the ship is in

    //find valid next moves
    int *validMoves = findValidMoves(field, shipRow, currentColumn);

    int counter = 0;
    int maxIterations = 10; //prevent infinite loop
    while (counter <= maxIterations) {
        counter++;

        if (counter == maxIterations) {
            nextMove = longestPathMove;
            break;
        }

        //determine next move from valid options, attempts to stay near centre of the field where possible.
        if (validMoves[1] == 1) { // if staying still is valid, then do so
            nextMove = 0;

            //check if a valid path to the end of the field exists, if it does then break out of the loop
            if (findValidPath(field, &validPathFound, shipRow, offsetTracker, currentColumn, &longestPathLength, &longestPathMove, nextMove)){
                break;
            } else {
                //if no valid path exists, then remove this option from the valid moves list
                validMoves[1] = 0;
                continue;
            }

        } else if (shipRow > 10) { //if ship is below the centre of the field
            //repeat above functionality for the other valid moves
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
        } else {  //if ship is at the centre of the field or above
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
    //free memory used for valid move array
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
    //check if ship will collide with an asteroid
    for (int i = 0; i < SHIP_WIDTH; i++) {
        if (field[shipRow][currentColumn + i] != 0 && field[shipRow][currentColumn+ i] != 2) {
            return 1;
        }
    }
    return 0;
}


int checkForOutOfBounds(int shipRow) {
    //check if ship is out of bounds
    if (shipRow < 0 || shipRow >= FIELD_HEIGHT) {
        return 1;
    }
    return 0;
}


int* findValidMoves(int field[][FIELD_WIDTH], int shipRow, int currentColumn) {
    //find valid moves for current column
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
    if (currentColumn == FIELD_WIDTH) {
        *validPathFound = 1;
        return 1;
    }
    //check if a valid path has already been found, if so exit the function
    if (*validPathFound == 1) {
        return 1;
    }

    currentColumn++;
    //find valid moves for current column
    int *validMoves = findValidMoves(field, shipRow + offsetTracker, currentColumn);

        for (int j = -1; j <= 1; j++) {
            if (validMoves[j + 1] == 1) {
                int result = findValidPath(field, validPathFound, shipRow, offsetTracker + j, currentColumn, longestPathLength, longestPathMove, currentMove);
                if (result == 1) {
                    free(validMoves);
                    return 1;
                }
            } else if (j == 1) {
                //if no valid moves found, then check if the current path is the longest, if so then update the longest path variables
                if (*longestPathLength < currentColumn) {
                    *longestPathLength = currentColumn;
                    *longestPathMove = currentMove;
                }
            }
    }

    //if valid path not found, then return 0
    if (*validPathFound == 1) {
        return 1;
    } else {
        return 0;
    }

}