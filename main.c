#include <stdio.h>
#include <string.h>

#define S21_NULL ((void *)0)

typedef unsigned long s21_size_t;

char *s21_strtok(char *str, const char *delimiters) {
    static char *str_ptr = NULL;
    if (str != NULL) str_ptr = (char *)str;
    if (str_ptr == NULL || *str_ptr == '\0') return NULL;

    while (*str_ptr != '\0') {
        int is_delim = 0;
        for (const char *d = delimiters; *d != '\0'; d++) {
            if (*str_ptr == *d) {
                is_delim = 1;
                break;
            }
        }
        if (!is_delim) break;
        str_ptr++;
    }

    if (*str_ptr == '\0') {
        str_ptr = NULL;
        return NULL;
    }

    char *start_str_ptr = str_ptr;

    while (*str_ptr != '\0') {
        int is_delim = 0;
        for (const char *d = delimiters; *d != '\0'; d++) {
            if (*str_ptr == *d) {
                is_delim = 1;
                break;
            }
        }
        if (is_delim) break;
        str_ptr++;
    }

    if (*str_ptr != '\0') {
        *str_ptr = '\0';
        str_ptr++;
    } else {
        str_ptr = NULL;
    }

    return start_str_ptr;
}


int main() {
    char str[] = "Hello, world! Im God, whats your name?";
    char delim[] = ",";
    
    // char *result = s21_strtok(str, substr);
    // printf("result  my: %s\n", result);
    char *result2 = s21_strtok(str, delim);
    printf("result def: %s\n", result2);
    do {
        result2 = strtok(NULL, delim);
        printf("result def: %s\n", result2);
    } while (result2 != NULL);


    printf("\nstr - '%s'", str);
    printf("\ndelim - '%s'\n", delim);

    return 0;
}