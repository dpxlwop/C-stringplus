#include <stdio.h>
#include <string.h> //заменить на s21_string.h
#include <stdarg.h> //для обработки не определенного кол-ва аргументов функции
#include <stdlib.h>
#include <math.h>

#define s21_NULL ((void)*0)     //макрос для NULL

typedef long unsigned  s21_size_t;  //size_t

typedef struct {    //структура для флагов
    int float_accuracy;
    int need_sign;
    int wait_for_accuracy;
    int is_percent;
} s21_format_t;

void s21_sprintf(char *str, const char* format, ...);
void parse_format(char* str, const char *format, va_list* args_ptr);
void int_to_str(int num, char* dest, int need_sign, int count);
void add_to_dest(char* dest, char* str);
void float_to_str(char* dest, double num, int accuracy, int need_sign);