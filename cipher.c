#include "cipher.h"

// XOR cipher function
void xor_cipher(char *buf, ssize_t len, unsigned char key) {
    for (ssize_t i = 0; i < len; i++) {
        buf[i] ^= key;
    }
}

// Caesar cipher function
void caesar_cipher(char *buf, ssize_t len, int shift, int decrypt) {
    if (decrypt) shift = 26 - shift;

    for (ssize_t i = 0; i < len; i++) {
        char c = buf[i];
        if (c >= 'A' && c <= 'Z') {
            buf[i] = 'A' + (c - 'A' + shift) % 26;
        } else if (c >= 'a' && c <= 'z') {
            buf[i] = 'a' + (c - 'a' + shift) % 26;
        }
    }
}
