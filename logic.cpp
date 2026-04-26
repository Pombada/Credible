//
// Created by Dumbledore on 4/24/2026.
//
#include "logic.h"

#include <iostream>

bool Luhn_algorithm(const char *numbers) {
    int total = 0;
    bool second = false;
    for (int i = strlen(numbers)-1; i>=0; i--) {
        int d = numbers[i] - '0';
        if (second) {
            d *= 2;
            if (d > 9) d -= 9;
            second= false;
        }else {
            second = true;
        }
        total += d;
    }

    return total % 10 == 0;
}
