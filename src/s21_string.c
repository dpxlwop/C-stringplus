#include "s21_string.h"
#include <string.h>

void *s21_memchr(const void *str, int c, s21_size_t n) {
    unsigned char *ptr = (unsigned char *) str;
    void *res = S21_NULL;
    for (s21_size_t i = 0; i < n; i++) {
        if (ptr[i] == (unsigned char)c) {
            res = (void*) (ptr + i);
        }
    }
    return res;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    unsigned char *ptr1 = (unsigned char *) str1;
    unsigned char *ptr2 = (unsigned char *) str2;
    for (s21_size_t i = 0; i < n; i++) {
        if (ptr1[i] != ptr2[i]) {
            return ptr1[i] - ptr2[i];
        }
    }
    return 0;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    unsigned char *to = (unsigned char *) dest;
    unsigned char *from = (unsigned char *) src;
    for (s21_size_t i = 0; i < n; i++) {
        to[i] = from[i];
    }
    return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
    unsigned char *ptr = (unsigned char *) str;
    for (s21_size_t i = 0; i < n; i++) {
        ptr[i] = (unsigned char)c;
    }
    return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    unsigned char *to = (unsigned char *) dest;
    unsigned char *from = (unsigned char *) src;
    s21_size_t len = s21_strlen(dest);
    s21_size_t j = 0;
    for (s21_size_t i = len; j < n && from[j] != '\0'; i++) {
        to[i] = from[j];
        j++; 
    }
    to[len + j] = '\0';
    return dest;
}

s21_size_t s21_strlen(const char *str) {
    s21_size_t len = 0;
    if (str != S21_NULL) {
        while (str[len] != '\0') {
            len++;
        }
    }
    return len;
}