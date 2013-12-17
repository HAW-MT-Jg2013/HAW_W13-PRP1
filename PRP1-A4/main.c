/*
 * file: main.c
 * project: BScMech1-WiSe13-PRP1
 * version: 1.2 (17.12.2013 18:52)
 *  - 1.0.1 bugfix
 *  - 1.1   added: show number of life cells + quit if population is 0
 *  - 1.1.1 improvement: make use of calloc for safety
 *  - 1.2   improvement: more beautiful code and variable names
 *
 * Created by Jannik Beyerstedt on 10.12.13
 * jannik.beyerstedt.de
 * Copyright: all code under creative commons licence: CC BY-NC-SA 3.0
 *
 *
 * HAW Hamburg - Labor Programmieren 1
 * command line tool: game of life
 */

// FOR WINDOWS:
// change: system("clear"); to system("cls");
// change: usleep(sleepTime*1000); to Sleep(sleepTime);
// include windows.h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <windows.h> // for windows


// RULES
const int born = 3; // dead cell with exactly ... live neighbours will turn alive by reproduction
const int die1 = 2; // live cell with less than ... live neighbours dies, caused by under-population
const int die2 = 3; // live cell with more than ... live neighbours dies, caused by over-population
const int sleepTime = 50 ; // sleep time in milliseconds
const int maxGen = 10000; // maximum number of generations



int **arrayptr;

void getFieldSize(int *rowsPtr, int *colsPtr){
    printf("/n/n CONWAY`S GAME OF LIFE\n\n");
    // "please give me the size of your game (rows columns)"
    printf("Gib die Größe des Spielfeldes an (Reihen Spalten)\n");
    scanf("%d %d", rowsPtr, colsPtr);
    
    arrayptr = calloc(*rowsPtr, sizeof(int *));
    for (int i = 0; i < *rowsPtr; i++) arrayptr[i] = calloc(*colsPtr, sizeof(int));
}

void inputLivings(int *rowsPtr, int *colsPtr){
    int error = 0;
    int rowInput = 0;
    int colInput = 0;
    
    // "give me the row and column of every living cell (row column). Exit with -1\n"
    printf("Gib die Koordinaten der lebenden Zellen ein (Reihe Spalte), Abbruch durch -1\n");
    do { // get positions of the living cells and abort input with "-1"
        scanf("%d", &rowInput);
        if (rowInput > 0 && rowInput <= *rowsPtr) {
            scanf("%d", &colInput);
            if (colInput > 0 && colInput <= *colsPtr) {
                arrayptr[rowInput-1][colInput-1] = 1;
            }else error = 1;
        }else error = 1;
    } while (error == 0);
}



int calcR (int i, int *rowsPtr){return (i+ *rowsPtr)% *rowsPtr;}
int calcC (int i, int *colsPtr){return (i+ *colsPtr)% *colsPtr;}

int sumLivings(int *rowsPtr, int *colsPtr, int actualRow, int actualCol){
    int count = 0;
    // sum all 9 neighbour cells
    for (int dRow = -1; dRow <= 1; dRow++) {
        for (int dCol = -1; dCol <= 1; dCol++) {
            count += arrayptr[calcR(actualRow + dRow, rowsPtr)][calcC(actualCol + dCol, colsPtr)];
        }
    } // end sum
    count -= arrayptr[actualRow][actualCol]; // subtract the cell itself
    return count;
}

int generation(int *rowsPtr, int *colsPtr){
    int population = 0;
    int **array2ptr;
    array2ptr = malloc(*rowsPtr * sizeof(int *));
    for (int i = 0; i < *rowsPtr; i++) array2ptr[i] = malloc(*colsPtr * sizeof(int));
    
    // check every cell
    for (int actionRow = 0; actionRow < *rowsPtr; actionRow++) {
        for (int actionCol = 0; actionCol < *colsPtr; actionCol++) {
            int count = sumLivings(rowsPtr, colsPtr, actionRow, actionCol);
            int cellstate = arrayptr[actionRow][actionCol];
            
            // check the rules
            if (cellstate == 0 && count == born) {
                array2ptr[actionRow][actionCol] = 1; // turn a dead cell alive
                population++;
            }else if (cellstate == 1 && count < die1) {
                array2ptr[actionRow][actionCol] = 0; // turn a living cell dead (under-population)
            }else if (cellstate == 1 && count > die2) {
                array2ptr[actionRow][actionCol] = 0; // turn a living cell dead (over-population)
            }else {
                array2ptr[actionRow][actionCol] = arrayptr[actionRow][actionCol]; // in any other situation the cell keeps it´s state
                population += array2ptr[actionRow][actionCol];
            }// end check rules
        }
    }// end every cell
    
    // free "old" array
    for (int i = 0; i < *rowsPtr; i++) {
        free(arrayptr[i]);}
    free(arrayptr);
    
    arrayptr = array2ptr;
    return population;
}



void output(int *rowsPtr, int *colsPtr, int genNo, int popNo){
    system("clear");
    printf("generation: %7d population: %d\n", genNo, popNo);
    
    // print for every cell
    for (int actionRow = 0; actionRow < *rowsPtr; actionRow++){
        for (int actionCol = 0; actionCol < *colsPtr; actionCol++){
            if (arrayptr[actionRow][actionCol]==1){
                printf("* ");
            }else printf("  ");
        }
        printf("\n"); // line break every line
    }// end every cell
    printf("\n");
}



int main()
{
    int rows = 0;
    int cols = 0;
    
    getFieldSize(&rows, &cols);
    
    inputLivings(&rows, &cols);
    
    output(&rows, &cols, 0, 0); // output initial generation
    
    for (int genNo = 1; genNo < maxGen; genNo++){
        int population = 0;
        population = generation(&rows, &cols);      // calculate new generation
        output(&rows, &cols, genNo, population);    // output new generation
        if (population == 0) {                      // check if there are no life cells
            printf("\n\n----ALL CELLS ARE DEAD----\n");
            break;}
        usleep(sleepTime*1000);
    }
    return 0;
}