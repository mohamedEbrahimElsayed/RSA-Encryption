#include "fermat.h"  // Include the header file


// Function to perform the Fermat primality test (0 -> composite, 1 -> likely prime)
uint8_t is_probable_prime(const uint16_t p,uint8_t security_level) {
    uint16_t a;
    if (p < 4) return (p == 2 || p == 3); // Handle small primes

    if (p % 2 == 0) return 0; // Even numbers are not prime

    while (security_level--)
    {
        // Select random a in range [2, p-2]
        a = 2 + (rand() % (p - 3)); // rand() % (p-3) generates numbers in the range 0 to p-4.

        // Fermat test using updated mod_exp
        if (fast_exponentiation(a, p - 1, p) != 1) {
            return 0; // Composite
        }
    }
    return 1; // Likely prime
}
