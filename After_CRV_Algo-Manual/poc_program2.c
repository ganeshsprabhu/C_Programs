#include <assert.h>
#include <stdbool.h>

int nondet_int();
void __CPROVER_printf(const char *format, ...);

int nondet_int_range_1_32() {
    int value = nondet_int() % 32 + 1;
    __CPROVER_assume(value >= 1 && value <= 32);
    return value;
}

int simulate_seu(int value, int bit_pos) {
    int mask = 1 << bit_pos;
    return (value ^ mask); // XOR operation for bit flip
}

// Ensures that an SEU is introduced only once for the variable under investigation
void simulate_seu_main(int *invest_var) {
    static int count = 0;  // To make sure that SEU happens only once
    if (count == 0) {
        int bit_pos = nondet_int_range_1_32();
        *invest_var = simulate_seu(*invest_var, bit_pos);
        count++;
    }
}

int p(int x, int y) {
    int output = 4;
    int count = 0;
    while (count < 7) {
        if (x > 10) 
            if (y == 1) output = 2; else output = 1;
        else output++;
        count++;
    }
    return output;
}

int p_prime_x(int x, int y) {
    simulate_seu_main(&x); // Apply SEU to x
    return p(x, y); // Reuse the original function
}

int p_prime_y(int x, int y) {
    simulate_seu_main(&y); // Apply SEU to y
    return p(x, y); // Reuse the original function
}

void analyze_crv(int x, int y) {
    // Original program output
    int output = p(x, y);

    // Instrumented outputs
    int x_output = p_prime_x(x, y);
    int y_output = p_prime_y(x, y);

    // Safety conditions
    int phi = output <= 10;
    int phi_prime_x = x_output <= 10;
    int phi_prime_y = y_output <= 10;

    // Assertions for CBMC
    __CPROVER_assert(!(phi ^ phi_prime_x), "Violation due to x");
    __CPROVER_assert(!(phi ^ phi_prime_y), "Violation due to y");

    // Debugging values using assertions and printing
    __CPROVER_printf("X Value: %d\n", x);
    __CPROVER_printf("Y Value: %d\n", y);
}

int main() {
    int x = nondet_int();
    int y = nondet_int();

    __CPROVER_assume(x >= 0 && x <= 100);
    __CPROVER_assume(y >= 0 && y <= 100);

    // Call the analysis function
    analyze_crv(x, y);

    return 0;
}
