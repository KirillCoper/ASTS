/*******************************************************************************
* Copyright (C) 2020 TUSUR, FB
* File              : Nasishenie_po_ur.c
* Compiler          : Microsoft Visual Studio 2019
* Version           : 14.0.5
* Created File      : 8.03.2020
* Last modified     : 17.03.2020
*
* Support mail      : kirill.grigoryev.1998@gmail.ru
*
* Description       : Realisation of saturation at two levels
*                   :
*******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#define H2 3.4159 // второй уровень
#define H1 0 // первый уровень
#define N 10 // уровни сигнала
float H2_H1_filter(float S_input, float H2_porog, float H1_porog) {
                if(S_input <= H1_porog) S_input = H1_porog; // проверка условий соответствия уровням
                        else if(S_input >= H2_porog) S_input = H2_porog;
                        else S_input = S_input;
                        return S_input;
}
int main(void) {
        float S[N] = {1, 2, 3, 4, 5, 4, 3, 2, 9, -20}; // массив, состоящий из значений уровня сигнала
                for(int8_t i = 0; N >i ; i++){
                        S[i] = H2_H1_filter(S[i], H2, H1); // Проход по каждому значению массива
                                printf ("%f\n", S[i]);
                }
        return 0;
}