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

int main() {
    printf("***ТЕСТЫ***\n");
    
    printf("strlen\n");
    printf("%ld\n", s21_strlen("He\0llo"));
    printf("%ld\n", strlen("He\0llo"));

    printf("\nmemset\n");
    char test1[10] = "hellooo";
    char test2[10] = "hellooo";
    printf("тест мой\n");
    s21_memset(test1, '_', 5);
    printf("%s\n", test1);
    printf("тест не мой\n");
    memset(test2, '_', 5);
    printf("%s\n", test2);

    printf("\nmemchr\n");
    char str1[] = "hello world";
    char str2[] = "hello world";
    printf("тест мой: ");
    void *result1 = s21_memchr(str1, 'o', 11);
    if (result1 != S21_NULL) {
        printf("найден символ 'o' по адресу %p\n", result1);
    } else {
        printf("символ не найден\n");
    }
    printf("тест не мой: ");
    void *result2 = memchr(str2, 'o', 11);
    if (result2 != NULL) {
        printf("найден символ 'o' по адресу %p\n", result2);
    } else {
        printf("символ не найден\n");
    }

    printf("\nmemcmp\n");
    char str3[] = "hello world";
    char str4[] = "hell world";
    printf("тест мой: ");
    int res1 = s21_memcmp(str3, str4, 11);
    printf("%d\n", res1);
    printf("тест не мой: ");
    int res2 = memcmp(str3, str4, 11);
    printf("%d\n", res2);

    printf("\nmemcpy\n");
    char memcpy_src1[] = "hello world";
    char memcpy_dest1[20] = "................";
    char memcpy_src2[] = "hello world";
    char memcpy_dest2[20] = "................";

    printf("тест мой: ");
    s21_memcpy(memcpy_dest1, memcpy_src1, 11);
    printf("src: %s, dest: %s\n", memcpy_src1, memcpy_dest1);

    printf("тест не мой: ");
    memcpy(memcpy_dest2, memcpy_src2, 11);
    printf("src: %s, dest: %s\n", memcpy_src2, memcpy_dest2);

    printf("\nДополнительный тест с перекрытием:\n");
    char data1[20] = "abcdefghij";
    char data2[20] = "abcdefghij";

    printf("тест мой: ");
    s21_memcpy(data1 + 2, data1, 5);
    printf("%s\n", data1);

    printf("тест не мой: ");
    memcpy(data2 + 2, data2, 5);
    printf("%s\n", data2);

    printf("\nstrncat\n");
    char strncat_dest1[20] = "hello";
    char strncat_src1[] = " world";
    char strncat_dest2[20] = "hello"; 
    char strncat_src2[] = " world";

    printf("тест мой: ");
    s21_strncat(strncat_dest1, strncat_src1, 6);
    printf("dest: '%s'\n", strncat_dest1);

    printf("тест не мой: ");
    strncat(strncat_dest2, strncat_src2, 6);
    printf("dest: '%s'\n", strncat_dest2);

    char strncat_dest3[20] = "test";
    char strncat_src3[] = "12345";
    char strncat_dest4[20] = "test";
    char strncat_src4[] = "12345";

    printf("тест мой (n=3): ");
    s21_strncat(strncat_dest3, strncat_src3, 3);
    printf("dest: '%s'\n", strncat_dest3);

    printf("тест не мой (n=3): ");
    strncat(strncat_dest4, strncat_src4, 3);
    printf("dest: '%s'\n", strncat_dest4);

    char strncat_dest5[20] = "hello";
    char strncat_src5[] = "";
    char strncat_dest6[20] = "hello";
    char strncat_src6[] = "";

    printf("тест мой (пустая src): ");
    s21_strncat(strncat_dest5, strncat_src5, 3);
    printf("dest: '%s'\n", strncat_dest5);

    printf("тест не мой (пустая src): ");
    strncat(strncat_dest6, strncat_src6, 3);
    printf("dest: '%s'\n", strncat_dest6);

    char strncat_dest7[20] = "hello";
    char strncat_src7[] = " world";
    char strncat_dest8[20] = "hello";
    char strncat_src8[] = " world";

    printf("тест мой (n=0): ");
    s21_strncat(strncat_dest7, strncat_src7, 0);
    printf("dest: '%s'\n", strncat_dest7);

    printf("тест не мой (n=0): ");
    strncat(strncat_dest8, strncat_src8, 0);
    printf("dest: '%s'\n", strncat_dest8);

    return 0;
}