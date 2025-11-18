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


char *s21_strchr(const char *str, int c) { // TODO убрать ptr_str, избыточно
    if (str == S21_NULL) return S21_NULL;

    char *ptr_str = (char *)str;
    do {
        if (*ptr_str == c) {
            return ptr_str;
        }
    } while (*(ptr_str++) != '\0');

    return S21_NULL;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    if (str1 == S21_NULL && str2 == S21_NULL) return 0; // TODO под вопросом
    if (str1 == S21_NULL) return -1;
    if (str2 == S21_NULL) return 1;

    while (n-- > 0) {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        
        if (*str1 == '\0') {
            break;
        }

        str1++;
        str2++;
    }   
    
    return 0;
}   

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    if (dest == S21_NULL || src == S21_NULL) return dest; // TODO под вопросом

    char *temp_dest = dest;
    while (n-- > 0) {
        if ((*temp_dest++ = *src++) == '\0'){
            while (n-- > 0) {
                *temp_dest = '\0'; 
            }
            break;
        }
    }

    return dest;
}   

s21_size_t s21_strcspn(const char *str1, const char *str2) {
    if (str1 == S21_NULL || str2 == S21_NULL) return 0; // TODO под вопросом

    s21_size_t result = 0;

    do {
        char *temp_str2 = (char*)str2;
        do {
            if (*str1 == *temp_str2) {
                return result;
            }
        } while (*temp_str2++ != '\0');
        result++;
    } while (*str1++ != '\0');

    return result;
}


#if defined(__APPLE__) || defined(__MACH__)
    #include <errno.h>
    #define ERROR_MESSAGES { \
        [0] = "Undefined error: 0", \
        [EPERM] = "Operation not permitted", \
        [ENOENT] = "No such file or directory", \
        [ESRCH] = "No such process", \
        [EINTR] = "Interrupted system call", \
        [EIO] = "Input/output error", \
    }
    #define MAX_ERROR_NUM 107

#elif defined(__linux__)
    #include <errno.h>
    #define ERROR_MESSAGES { \
        [0] = "Success", \
        [EPERM] = "Operation not permitted", \
        [ENOENT] = "No such file or directory", \
        [ESRCH] = "No such process", \
        [EINTR] = "Interrupted system call", \
        [EIO] = "Input/output error", \
    }
    #define MAX_ERROR_NUM 133

#elif defined(_WIN32) || defined(_WIN64)
    #include <winerror.h>
    #define ERROR_MESSAGES { \
        [ERROR_SUCCESS] = "The operation completed successfully", \
        [ERROR_INVALID_FUNCTION] = "Incorrect function", \
        [ERROR_FILE_NOT_FOUND] = "The system cannot find the file specified", \
        [ERROR_PATH_NOT_FOUND] = "The system cannot find the path specified", \
        [ERROR_ACCESS_DENIED] = "Access is denied", \
        [ERROR_INVALID_HANDLE] = "The handle is invalid", \
    }
    #define MAX_ERROR_NUM 15999
#else
    #error "Unsupported operating system"
#endif

char *s21_strerror(int errnum) {
    char *error_messages[] = ERROR_MESSAGES;

    return errnum > MAX_ERROR_NUM ? "unknow code error" : error_messages[errnum];
}

char *s21_strpbrk(const char *str1, const char *str2) {
    if (str1 == S21_NULL || str2 == S21_NULL) return NULL; // TODO под вопросом

    do {
        char *temp_str2 = (char*)str2;
        do {
            if (*str1 == *temp_str2) {
                return (char*) str1;
            }
        } while (*temp_str2++ != '\0');
    } while (*str1++ != '\0');

    return NULL;
}

char *s21_strrchr(const char *str, int c) { // TODO переделать, чтобы справа налево был цикл
    if (str == NULL) return NULL;

    char *found_c = NULL;
    do {
        if (*str == (char)c) {
            found_c = (char*)str;
        }
    } while (*str++ != '\0');

    return found_c;
}

char *s21_strstr(const char *haystack, const char *needle) {
    if (haystack == NULL) return NULL;

    do {
        const char *temp_haystack = haystack;
        const char *temp_needle = needle;
        
        while (*temp_needle != '\0' && *temp_haystack == *temp_needle) {
            temp_haystack++;
            temp_needle++;
        }
        
        if (*temp_needle == '\0') return (char *)haystack;
    } while (*haystack++ != '\0');

    return NULL;
}

char *s21_strtok(char *str, const char *delim) {
    static char *str_ptr = NULL;
    if (str != NULL) str_ptr = (char *)str;
    if (str_ptr == NULL || *str_ptr == '\0') return NULL;

    while (*str_ptr != '\0') {
        int is_delim = 0;
        for (const char *d = delim; *d != '\0'; d++) {
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
        for (const char *d = delim; *d != '\0'; d++) {
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