The objective of this project is to implement the RSA public-key cryptosystem 
using an 8051 microcontroller. The implementation includes both encryption and 
decryption processes. Communication between the 8051 microcontroller and a 
laptop will be established using a serial interface, facilitated by a terminal 
application such as HyperTerminal. Prime numbers p and q, essential for key 
generation, will be input from the PC and verified for primality using the Fermat 
Primality Test at a security level of 5. The microcontroller will calculate public 
and private keys, encrypt the plaintext received from the terminal, and send the 
resulting ciphertext back to the PC. 
