#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void count_words(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    char word[256];
    while (fscanf(file, "%255s", word) == 1) {
        count++;
    }

    fclose(file);
    printf("Number of words: %d\n", count);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    const char *filename = argv[1];
    count_words(filename);
    return 0;
}