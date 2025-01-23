#include "encryption.h"
#include "uart.h"
#include "std_types.h"
#include "fermat.h"
#include "EEA.h"

#define secuirty_level 5
#define CRYPTO_N(p, q) ((uint32_t)p * q)



uint32_t valid_input(char *prompt){
    uint32_t message;
    while (1)
    {
         UART_sendString(prompt);
        message = UART_reseiveHex();
        if (message == 0)
        {
            UART_sendString("\r");
        }
        else{
            return message;
        }
    }
}

uint16_t input_prime(char *prompt) {
    uint16_t num;
    while (1) {
        num = (uint16_t)valid_input(prompt);
        if (is_probable_prime(num, secuirty_level)) {
            UART_sendString("Likely prime\r");
            return num;
        } else {
            UART_sendString("Composite,try again\r");
        }
    }
}

void main() {

    uint16_t p, q;
    uint32_t message, phi, e, d;

    UART_Init(); // Initialize UART

    while (1) {
        // Get the message from the user
        message = valid_input("Message: ");
        // Get the prime numbers from the user            
        p = input_prime("(p): ");
        q = input_prime("(q): ");
        
        // Check if p and q are the same
        if(p == q){
            UART_sendString("\r(p) and (q) must be different\r");
            continue;
        }

        // Calculate phi
        phi = (uint32_t)(p - 1) * (q - 1);

         for (e = 2; e < phi; e++) {
            // find e such that has a modular inverse with phi
            d = modular_inverse(e, phi);
            if (d != 0) {
                break;
            }
        }
        // Display the keys
        UART_sendString("\r[e]: ");
        UART_sendHex(e);
        UART_sendString("\r[d]: ");
        UART_sendHex(d);

        // Encrypt or decrypt the message
        UART_sendString("\r\r1- Encrypt\r2- Decrypt\r> ");

            switch (UART_RxChar()) {
            case '1':
                // CT = PT^e mod n
                message = fast_exponentiation(message, e, CRYPTO_N(p, q));
                UART_sendString("\r[CT]: ");
                UART_sendHex(message);
                break;
            case '2':
                // PT = CT^d mod n
                message = fast_exponentiation(message, d,  CRYPTO_N(p, q));
                UART_sendString("\r[PT]: ");
                UART_sendHex(message);
                break;
            default:
                UART_sendString("\rInvalid");
                break;
        }
        
        // Ask the user if they want to continue
        UART_sendString("\r\rAny key to continue..");
        UART_RxChar();
        UART_sendString("\r");
    }
}
