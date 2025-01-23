#include "encryption.h"

#define DOUBLE_MOD(a, mod) do { \
    (a) = (a) < (mod - a) ? ((a) << 1) : ((a) << 1) - (mod); \
} while(0)

#define ADD_MOD(result, a, mod) do { \
    (result) = ((result) >= (mod) - (a)) ? ((result) - (mod) + (a)) : ((result) + (a)); \
} while(0)



// Function to perform modular inverse using the Extended Euclidean Algorithm
uint32_t multiply_mod(uint32_t a, uint32_t b, uint32_t mod) {
   uint32_t result = 0;  // Initialize the result to 0

    // Perform the multiplication and modulo operation
    while (b > 0) {
        // If the least significant bit of b is set, add a to the result
        if (b & 1) ADD_MOD(result, a, mod);
        // Multiply a by 2, taking modulo if necessary
        DOUBLE_MOD(a, mod);
        // Divide b by 2
        b >>= 1;
    }
    return result % mod;  // Final modulo operation to ensure result is within bounds
}


// Function to perform fast exponentiation
uint32_t fast_exponentiation(uint32_t base, uint32_t exp, const uint32_t mod) {
    // square and multiply 
    uint32_t result = 1;
    while (exp > 0) {
        if (exp & 1) result = multiply_mod(result, base, mod); // If exp is odd, multiply result with base
        base = multiply_mod(base, base, mod); // Square the base
        exp >>= 1; // Divide the exponent by 2
    }
    return result;
}









