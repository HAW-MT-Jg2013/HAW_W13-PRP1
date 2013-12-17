/*
 * file: main.c
 * project: BScMech1-WiSe13-PRP1
 * version: 1.1 (26.11.2013, 14.35)
 *
 * Created by Jannik Beyerstedt on 13.11.13
 * jannik.beyerstedt.de
 * Copyright: all code under creative commons licence: CC BY-NC-SA 3.0
 *
 *
 * HAW Hamburg - Labor Programmieren 1
 *
 * command line tool zum Lösen linearer Gleichungssysteme in Matrix-Scheibweise
 */

#include <stdio.h>
#include <math.h>

#define MYEPS 1.0E-19  // (fabs(x) < MYEPS)
#define MAX 20

int equNo = 0; // number of equitations

float inputA[MAX] [MAX] = {}; // Zeile Spalte
float inputB[MAX] = {};
float solution[MAX] = {};


void ReadMatrix(){
    printf("Gib die Matrix ein:\n");
    for (int rowCount = 0; rowCount < equNo; rowCount++){
        for (int columnCount = 0; columnCount < equNo; columnCount++){
            scanf("%f", &inputA[rowCount][columnCount]);
        }
    }
}

void ReadVector(){
    printf("Gib nun den Vektor B ein:\n");
    for (int i = 0; i < equNo; i++) {
        scanf("%f", &inputB[i]);
    }
}

void DisplayMatrix(){
    for (int rowCount = 0; rowCount < equNo; rowCount++){
        for (int columnCount = 0; columnCount < equNo; columnCount++){
            printf("%4.4f ", inputA[rowCount][columnCount]);}
        printf("\n");
    }
}

void DisplayVector(float vektor[MAX]){ // Vektor als Parameter
    for (int i = 0; i < equNo; i++) {
        printf("%4.4f \n", vektor[i]);
    }
}

int EliminateForward(){
    int errorCode = 0;
    
    // festlegen der Zeile (actionRow) i, die auf Andere addiert wird
    for (int actionRow_i = 0; (actionRow_i +1)< equNo && errorCode == 0; actionRow_i++) {
        
        float pivotElement = inputA[actionRow_i][actionRow_i];
        if (fabs(pivotElement) < MYEPS) { // prüft, ob pivotElement != 0
            errorCode = -1;
            break; // exit FIRST for-loop (jump to return)
        }else;
        
        // addieren der i-ten auf die j-te Zeile (sumRow)
        for (int sumRow_j = (actionRow_i +1); sumRow_j < equNo; sumRow_j++) {
            float factor = inputA[sumRow_j][actionRow_i] / pivotElement * (-1); // Faktor des Summanden festlegen
            
            // Prozess des Addierens der einzelnen Elemente
            for (int columnCount = actionRow_i; columnCount < equNo; columnCount++) {
                inputA[sumRow_j][columnCount] += inputA[actionRow_i][columnCount] * factor;
            }
            
            inputB[sumRow_j] += inputB[actionRow_i] * factor; // äquivalente Addition im Vektor B
        }
    }
    
    return errorCode; // 0 wenn korrekt, -1 wenn Fehler
}

void InsertBackwards(){
        
    for (int i = equNo-1; i >= 0; i--) { // Term für xi aus der Aufgabenstellung für i = n-1 (hier: n=equNo-1, da Zählung ab 0, nicht ab 1)
        float sum = 0;
            for (int j = i+1; j <= equNo-1; j++) { // Summenfunktion berechnen
                sum += inputA[i][j] * solution[j];
            }
        float pivotElement = inputA[i][i];
        
        solution[i] = (inputB[i]-sum) / pivotElement;
    }
}


int main()
{
    int option = 0;
    int error = 0;
    
    printf("Gib mir ein lineares Gleichungssystem (LGS), das ich dir loesen kann\n");
    printf("Gib das LGS in Matrixtrixschreibweise an\n  Matrix A * Vektor X = Vektor B\n\n");
    
    printf("wie viele Gleichungen hat Dein LGS?\n");
    scanf("%d", &equNo);
    
    do {
        ReadMatrix();
        printf("Es wurde die folgende Matrix eingegeben:\n");
        DisplayMatrix();
        printf("  OK (0) , neu eingeben (1) ?  ");
        scanf("%d", &option);
    } while (option == 1);
    
    do {
        ReadVector();
        printf("Es wurde die folgender Vektor eingegeben:\n");
        DisplayVector(inputB);
        printf("  OK (0) , neu eingeben (1) ?  ");
        scanf("%d", &option);
    } while (option == 1);
    
    
    // SOLVING THE LGS
    error = EliminateForward();
    switch (error) {
        case -1:
            printf("Ups, da ging wohl was schief. Es kam beim Lösen der Matrix zu einer Division durch 0\n");
            break;
        default:
            printf("Die Matrix wurde erfolgreich in die Dreiecksform umgewandelt.\n");
            InsertBackwards();
            printf("Der Lösungsvektor ist:\n");
            DisplayVector(solution);
            break;}

    return 0;
}