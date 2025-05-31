#ifndef CIPHER_H
#define CIPHER_H

#include <unistd.h>

// XOR cipher
void xor_cipher(char *buf, ssize_t len, unsigned char key);

// Caesar cipher
void caesar_cipher(char *buf, ssize_t len, int shift, int decrypt);

#endif
