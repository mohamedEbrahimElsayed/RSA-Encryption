#include "uart.h"

void UART_Init() {
    // Set SM0=0, SM1=1 for mode 1 (8-bit UART with variable baud rate)
    // Set BRG value for baud rate 2400
    TMOD = 0x20; // Timer 1, mode 2, 8-bit reload
    TH1 = 0xFD;   // Load TH1 to generate baud rate 2400
    SCON = 0x50; // Mode 1, Receive enable
    TR1 = 1;     // Start Timer 1
}

// Function to transmit a character over UART
void UART_TxChar(const char ch) {
    SBUF = ch;       // Load character into SBUF
    while(TI == 0);  // Wait until transmit is complete
    TI = 0;          // Clear transmit interrupt flag
}

// Function to receive a character over UART
const char UART_RxChar() {
    while(RI == 0);  // Wait until receive is complete
    RI = 0;          // Clear receive interrupt flag
    return SBUF;     // Return received character
}

void UART_sendString(const char* str) {
    uint8_t i;
    for (i = 0; str[i] != '\0'; i++) {
        UART_TxChar(str[i]);
    }
}

void UART_sendHex(uint32_t num) {
    uint32_t divisor = 1;
    while (num / divisor > 0xF) 
    divisor *= 0x10; // Find the highest power of 10 <= num

    for (; divisor != 0; divisor /= 0x10) {
        uint8_t digit = (num / divisor) % 0x10;
        if (digit < 10) {
            UART_TxChar(digit + '0');
        } else {
            UART_TxChar(digit - 10 + 'A');
        }
    }
}

uint32_t UART_reseiveHex(){
    uint8_t count = 1;
    uint32_t num = 0;
    char c;
    while ((c = UART_RxChar()) != '\r' && c != '\n') {
        c = toupper(c);
        if (c >= '0' && c <= '9') {
            num = num * 0x10 + (c - '0');
        } else if (c >= 'A' && c <= 'F') {
            num = num * 0x10 + (c - 'A' + 10);
        } else {
            return 0;
        }
        if(count == 8)
        {
            UART_sendString("\n\r");
            return num;
        }
        count ++;
    }
    return num;
}

