#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

int nondet_int();

// Function to generate a nondeterministic integer within the range [1, 32]
// Bit flip - Between 1 to 32 bits
int nondet_int_range_1_32() {
    int value = nondet_int() % 32 + 1;
    __CPROVER_assume(value >= 1 && value <= 32); // Example assumption for positive x
    return value;
}

int simulate_seu(int value, int bit_pos) {
    int mask = 1 << bit_pos;
    __CPROVER_assume(mask >= 1 && mask <= 32);
    return (value ^ mask); //XOR operation for bit flip
}

void simulate_seu_main(int *invest_var) {
    static int count = 0;  // To make sure that SEU happens only once
    if(count == 0) {
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
    else output ++;
    count ++;
  }
  return output;
}

int p_prime_x(int x, int y) {
  int output = 4;
  int count = 0;
  simulate_seu_main(&x); // Before every use of x, introduce SEU
  while (count < 7) {
    if (x > 10) 
      if (y == 1) output = 2; else output = 1;
    else output ++;
    count ++;
  }
  return output;
}

int p_prime_y(int x, int y) {
  int output = 4;
  int count = 0;
  simulate_seu_main(&y); // Before every use of y, introduce SEU
  while (count < 7) {
    if (x > 10) 
      if (y == 1) output = 2; else output = 1;
    else output ++;
    count ++;
  }
  return output;
}

int main() {

    int output, x, y;

    output = p(x, y); // Original program
    int x_output = p_prime_x(x, y); // p'(x): Instrumented program, x is the variable under investigation
    int y_output = p_prime_y(x, y); // p'(y): Instrumented program, y is the variable under investigation

    //Safety Conditions assignment
    int phi = output <= 10;
    int phi_prime_x = x_output <= 10;
    int phi_prime_y = y_output <= 10;

    // Check CRV for x: We need to find and Ix such that (phi XOR phi_prime_x) is true
    __CPROVER_assert(!(phi ^ phi_prime_x), "CRV Result for x => if,SUCCESS then its not a CRV and if FAILURE then its a CRV!");

    // Check CRV for y: We need to find and Iy such that (phi XOR phi_prime_y) is true
    __CPROVER_assert(!(phi ^ phi_prime_y), "CRV Result for y => if,SUCCESS then its not a CRV and if FAILURE then its a CRV!");

    return 0;
}
