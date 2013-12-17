//
//  main.c
//  PRP1-A1c
//
//  Created by Jannik Beyerstedt on 30.10.13.
//
//


#include <stdio.h>
#include <math.h>

int main(void) {
    
    unsigned long long int input = 0;
    unsigned long long int divisor = 0;
    unsigned long long int modulus = 0;
    int output = 0;
    
    int i = 0;
    int digit = 0;
    
    int digit_count = 0;
    
    /* input */
    printf("Hallo, ich berechne Dir die Quersumme einer beliebigen natürlichen Zahl mit max. 19 Stellen \nZahl eingeben: ");
    scanf("%llu", &input);
    
    /* conversion */
    while (i < 20) {
        i++;
        
        divisor = pow(10, i);
        modulus = input % divisor;
        digit = modulus / (divisor / 10) ;
        
        output =  output + digit;
        
        digit_count ++;
        if (input == modulus) {
            i = 100;
        }
    }
    
    /* output */
    printf("Quersumme ist %d\n", output);
    printf("Deine Zahl hatte %d Stellen\n", digit_count);
    
    return 0;
}

