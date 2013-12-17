//
//  main.c
//  PRP1-A2a
//
//  Created by Jannik Beyerstedt on 30.10.13.
//
//
/*
 * Schreiben Sie ein Programm, das eine Folge von reellen Zahlen vom Typ float einliest.
 * Das Ende der Zahlenfolge wird erkannt durch das erste Zeichen, welches keine Zahl (also z.B. ein Buchstabe) ist.
 * Es sollen maximal 20 Zahlen eingelesen werden.
 * Das Programm soll dann fu ̈r die eingelesenen Zahlen folgende Gro ̈ßen berechnen:
 * 1. Die Anzahl der eingelesenen Zahlen,
 * 2. die Summe der eingelesenen Zahlen,
 * 3. das Maximum der eingelesenen Zahlen,
 * 4. das Minimum der eingelesenen Zahlen,
 * 5. den Mittelwert der eingelesenen Zahlen,
 */



#include <stdio.h>
#define MAXINPUT 20

float sum(float values[], int numbers){
    float returnValue = 0;
    int i = 0;
    do {
        returnValue += values[i];
        i++;
    } while (i < numbers);
    return returnValue;
}

float maximum(float values[], int numbers){
    float returnValue = values[0];
    int i = 0;
    do {
        if (returnValue < values[i]) {
            returnValue = values[i];
        }
        i++;
    } while (i < numbers);
    return returnValue;
}

float minimum(float values[], int numbers){
    float returnValue = maximum(values, numbers);
    int i = 0;
    returnValue = values[i];
    do {
        if (returnValue > values[i]) {
            returnValue = values[i];
        }
        i++;
    } while (i < numbers);
    return returnValue;
}

float average(float values[], int numbers){
    float returnValue = 0;
    
    returnValue = sum(values, numbers)/ numbers;
    return returnValue;
}



int main(void) {
    
    float input[MAXINPUT] = {};
    int index = 0;
    int check = 0;
    int numberCount = 0;
    int option = 0;
    float output = 0;
    
    printf("Bitte geben Sie maximal 20 Zahlen ein, je mit Enter bestätigen, Ende mit 'E'\n");
    
    do {
        check = scanf("%f", &input[index]);
        index++;
        numberCount++;
        if (check == 0) {
            numberCount--; // not count the escape character
            getchar(); // because fflush does not work in UNIX
        }
    } while (check == 1 && index < MAXINPUT);
    
    printf("Es wurden %d Zahlen eingegeben\n", numberCount);
    
    do {
        
        printf("Was möchten Sie berechnen?\n Summe      (1)\n Maximum    (2)\n Minimum    (3)\n Mittelwert (4)\n alles      (5)\n Ende       (0)\n");
        scanf("%d", &option);
        
        switch (option) {
            case 0: break;
            case 1:
                output = sum(input, numberCount);
                printf("Die Summe ist: %f\n", output);
                break;
            case 2:
                output = maximum(input, numberCount);
                printf("Das Maximum ist: %f\n", output);
                break;
            case 3:
                output = minimum(input, numberCount);
                printf("Das Minimum ist: %f\n", output);
                break;
            case 4:
                output = average(input, numberCount);
                printf("Der Durchschnitt ist: %f\n", output);
                break;
            case 5:
                output = sum(input, numberCount);
                printf("Die Summe ist:        %f\n", output);
                output = maximum(input, numberCount);
                printf("Das Maximum ist:      %f\n", output);
                output = minimum(input, numberCount);
                printf("Das Minimum ist:      %f\n", output);
                output = average(input, numberCount);
                printf("Der Druchschnitt ist: %f\n", output);
                break;
            default:
                break;
        }
    }
    while (option != 0);
    
    return 0;
}