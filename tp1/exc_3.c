#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch >= 32 && ch <= 255) {
            printf("%c [%d]\n", ch, ch);
        } else {
            printf("[%d]\n", ch);
        }
    }

    fclose(file);
    return 0;
}