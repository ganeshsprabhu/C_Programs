#include <stdio.h>

int p(int x, int y) {
    int output = 4;
    int count = 0;

    while (count < 7) {
        if (x > 10) {
            if (y == 1) {
                output = 2;
            } else {
                output = 1;
            }
        } else {
            output++;
        }
        count++;
    }

    // ACSL assertion (this is what Frama-C will look for)
    //@ assert output <= 10;  // This is an assertion to slice
    return output;
}
