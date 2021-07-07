//
// Created by thgir on 05/07/2021.
//

#include "../header/nyanpasu_lib.h"
#include <ctype.h>

void *safe_malloc(size_t n) {
    void *p = malloc(n);
    if (p == NULL) {
        fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", n);
        exit(1);
    }
    return p;
}

#ifdef _WIN32
/* Windows only function */
FILE *open_file(const char *fileName, const char *mode) {
    int err;
    FILE *toOpen = NULL;
    if ((err = fopen_s(&toOpen, fileName, mode))) {
        fprintf(stderr, "cannot open file '%s': %s\n", fileName, strerror(err));
        exit(1);
    } else {
        return toOpen;
    }
}
#endif

#ifndef _WIN32
/* Function compatible with any OS, but do not return the precise error in case of failure */
FILE *open_file(const char *fileName, const char *mode) {
    FILE *toOpen = NULL;
    toOpen = fopen(fileName, mode);
    if (toOpen == NULL) {
        fprintf(stderr, "cannot open file");
        exit(1);
    } else {
        return toOpen;
    }
}
#endif

void input_word(char **word) {
    if (*word != NULL)
        free(*word);
    char temp[40];
    fgets(temp, 40, stdin);
    temp[strlen(temp) - 1] = '\0';
    *word = safe_malloc(sizeof(char) * strlen(temp) + 1);
    strcpy(*word, temp);
}

void clear_buffer(void) {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int power_of_two(int power) {
    return 0b1 << power;
}

void swap(void *a, void *b, size_t len) {
    unsigned char *p = a, *q = b, tmp;
    for (size_t i = 0; i != len; ++i) {
        tmp = p[i];
        p[i] = q[i];
        q[i] = tmp;
    }
}