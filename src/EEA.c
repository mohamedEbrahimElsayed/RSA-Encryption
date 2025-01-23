#include "EEA.h"

uint32_t modular_inverse(uint32_t a, uint32_t b) {
    uint32_t old_r = a, r = b;
    int32_t old_s = 1, s = 0;  // Use int32_t to handle negative values
    uint32_t quotient, temp;

    while (r != 0) {
        quotient = old_r / r;

        // Update r
        temp = r;
        r = old_r - quotient * r;
        old_r = temp;

        // Update s
        temp = s;
        s = old_s - quotient * s;
        old_s = temp;
    }

    // If GCD is not 1, there's no modular inverse
    if (old_r != 1) {
        return 0;  // Return 0 as the inverse does not exist
    }

    // Ensure old_s is positive and within the modulo of b
    if (old_s < 0) {
        old_s += b;
    }
    return (uint32_t)old_s;  // Return the modular inverse
}



