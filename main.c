#include <stdio.h>      // For standard I/O 
#include <stdlib.h>     // For malloc(), exit()
#include <fcntl.h>      // For open() and file flags
#include <unistd.h>     // For read(), write(), close()
#include <string.h>     // For string operations (strcmp, strlen, snprintf)
#include "cipher.h"     // Header for xor_cipher() and caesar_cipher()

#define BUFSIZE 1024    // Buffer size for reading and writing file chunks

// Function to print usage instructions
void print_usage() {
    const char *msg =
        "Usage: ./file_encryptor <xor|caesar> <encrypt|decrypt> <key> <input_file> [output_file]\n";
    write(STDERR_FILENO, msg, strlen(msg)); // Print usage message to stderr
}

// Main
int main(int argc, char *argv[]) {
    // Validate number of arguments
    if (argc < 5 || argc > 6) {
        print_usage();
        return 1;
    }

    // Parse and assign command-line arguments
    const char *cipher_mode = argv[1];    // Cipher type
    const char *op_mode = argv[2];        // Operation
    int key = atoi(argv[3]);              // Convert key string to int
    const char *input_file = argv[4];     // Input file path
    const char *output_file;              // Output file path

    // If user provides an output file
    if (argc == 6) {
        output_file = argv[5];
    } else {
        // Auto-generate output filename based on operation mode
        static char output_buf[256];
        snprintf(output_buf, sizeof(output_buf), "%s.%s", input_file,
                 strcmp(op_mode, "encrypt") == 0 ? "enc" : "dec");
        output_file = output_buf;
    }

    // Validate key range
    if (key < 0 || key > 255) {
        fprintf(stderr, "Key must be between 0 and 255.\n");
        return 1;
    }

    // Open input file for reading
    int in_fd = open(input_file, O_RDONLY);
    if (in_fd < 0) {
        perror("open input");
        return 1;
    }

    // Open or create output file for writing
    int out_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_fd < 0) {
        perror("open output");
        close(in_fd); // Clean up already opened input file
        return 1;
    }

    // Allocate buffer for reading chunks of the file
    char *buf = malloc(BUFSIZE);
    if (!buf) {
        perror("malloc");
        close(in_fd);
        close(out_fd);
        return 1;
    }

    // Read and process the file in chunks
    ssize_t bytes;
    while ((bytes = read(in_fd, buf, BUFSIZE)) > 0) {
        // Apply the chosen cipher to the buffer
        if (strcmp(cipher_mode, "xor") == 0) {
            xor_cipher(buf, bytes, (unsigned char)key);
        } else if (strcmp(cipher_mode, "caesar") == 0) {
            // Caesar cipher: shift letters, reverse shift if decrypting
            caesar_cipher(buf, bytes, key % 26, strcmp(op_mode, "decrypt") == 0);
        } else {
            // Invalid cipher mode
            fprintf(stderr, "Unsupported cipher: %s\n", cipher_mode);
            free(buf);
            close(in_fd);
            close(out_fd);
            return 1;
        }

        // Write the processed (encrypted/decrypted) buffer to output file
        if (write(out_fd, buf, bytes) != bytes) {
            perror("write");
            free(buf);
            close(in_fd);
            close(out_fd);
            return 1;
        }
    }

    // Cleanup
    free(buf);          // Free dynamically allocated buffer
    close(in_fd);       // Close input file
    close(out_fd);      // Close output file

    return 0;           // Success
}
