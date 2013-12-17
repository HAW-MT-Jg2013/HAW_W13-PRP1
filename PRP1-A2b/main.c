//
//  main.c
//  PRP1-A2b
//
//  Created by Jannik Beyerstedt on 30.10.13.
//
//

/*
 * Schreiben Sie ein Programm, das die kartesischen Koordinaten x und y eines Punktes in der Ebene einliest
 * und sie in Polarkoordinaten r und φ (0 < φ <= 360) umrechnet.
 * Die beno ̈tigten Funktionen finden Sie in der Bibliothek math.h.
 * Umgekehrt soll das Programm auch die Eingabe von Polarkoordinaten gestatten
 * und diese in kartesische Koordinaten umrechnen. Die Formeln dafu ̈r sind:
 * x = r cos(φ)    y = r sin(φ)
 * Der Winkel φ soll dabei jeweils im Gradmaß (0 < φ <= 360) ausgegeben (bzw. eingelesen) werden.
 */

#include <stdio.h>
#include <math.h>


int main(void)
{
    int option = 0;
    
    float const PI = 3.141592654;
    
    float xValue = 0.0;
    float yValue = 0.0;
    float rValue = 0.0;
    float angle = 0.0;
    float angleRad = 0.0;
    
    printf("Wähle zwischen den zwei Modi: \n (1) Umrechnung kartesiche Koordinaten in Polarkoordinaten \n (2) Umrechnung Polarkoordinaten in kartesische Koordinaten \n");
    scanf("%d", &option);
    
    switch (option) {
        case 1:
            printf("x-Koordinate eingeben: ");
            scanf("%f", &xValue);
            printf("y-Koordinate eingeben: ");
            scanf("%f", &yValue);
            
            rValue = sqrtf(xValue*xValue + yValue*yValue);
            angleRad = atan2(yValue, xValue);
            angle = angleRad * 360 / (2*PI);
            
            
            if (angle < 0.0){
                angle = angle + 360.0;
            }
            
            printf("r = %f, Winkel = %f\n", rValue, angle);
            
            break;
        case 2:
            printf("Zeiger-Länge r angeben: ");
            scanf("%f", &rValue);
            printf("Winkel in Grad angeben: ");
            scanf("%f", &angle);
            
            angleRad = angle / 360 * (2*PI);
            
            
            xValue = rValue * cosf(angleRad);
            yValue = rValue * sinf(angleRad);
            
            printf("x = %f, y = %f\n", xValue, yValue);
            
            break;
            
        default:
            break;
    }
    
    
    return 0;
}

