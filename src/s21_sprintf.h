#include <stdio.h>
#include <string.h> //заменить на s21_string.h
#include <stdarg.h> //для обработки не определенного кол-ва аргументов функции
#include <stdlib.h>
#include <math.h>

#define s21_NULL ((void)*0)     //макрос для NULL

typedef long unsigned  s21_size_t;  //size_t

void s21_sprintf(char *str, const char* format, ...);
void parce_format(char* str, int* methods, const char *format, int* count);
void int_to_str(int num, char* dest, int need_sign);