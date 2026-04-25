//
// Created by Dumbledore on 4/24/2026.
//
#include "logic.h"

#include <iostream>

bool Luhn_algorithm(const char *numbers) {
    int total = 0;

    for (int i = 0; i < 16; i++) {
        int d = numbers[i] - '0';
        if (i % 2 == 0) {
            d *= 2;
            if (d > 9) d -= 9;
        }

        total += d;
    }

    return total % 10 == 0;
}
