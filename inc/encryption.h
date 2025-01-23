#ifndef __ENCRYPTION_H_
#define __ENCRYPTION_H_

#include "std_types.h"
#include "EEA.h"
#include "uart.h"

uint32_t fast_exponentiation(uint32_t base, uint32_t exp, uint32_t mod);
// uint16_t mod_inverse(uint16_t a, uint16_t mod);
uint32_t rsa_decrypt_crt(uint32_t ct, uint32_t d, uint16_t p, uint16_t q) ;
#endif