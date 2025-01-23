#ifndef FERMAT_H  // Include guard to prevent multiple inclusion
#define FERMAT_H
#include <stdlib.h>  // For rand() function
#include "encryption.h"
#include "std_types.h"
// Function prototypes
unsigned int mod_exp(unsigned int base, unsigned int exp, unsigned int mod);
unsigned char is_probable_prime(unsigned int p, unsigned char security_level);

#endif  // FERMAT_H
