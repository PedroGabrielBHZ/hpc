#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void copy_file(const char *source, const char *destination) {
    FILE *src = fopen(source, "rb");
    if (src == NULL) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    FILE *dest = fopen(destination, "wb");
    if (dest == NULL) {
        perror("Error opening destination file");
        fclose(src);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        if (fwrite(buffer, 1, bytes, dest) != bytes) {
            perror("Error writing to destination file");
            fclose(src);    
            fclose(dest);
            exit(EXIT_FAILURE);
        }
    }

    fclose(src);
    fclose(dest);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source file> <destination file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    copy_file(argv[1], argv[2]);
    return 0;
}