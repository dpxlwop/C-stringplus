#include <ctype.h>   //для проверки isdigit
#include <limits.h>  //либа для получения минимальных и максимальных значений в типов данных в системе
#include <stdarg.h>  //для обработки не определенного кол-ва аргументов функции
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //заменить на s21_string.h

typedef long unsigned s21_size_t;  // size_t

typedef struct {  // структура для флагов
  int float_accuracy;
  int need_sign;
  int wait_for_accuracy;
  int is_percent;
  int is_long;
  int is_short;
  int wait_for_left_alignment;
  int left_alignment;
} s21_format_t;

void s21_sprintf(char* str, const char* format, ...);
int parse_format(char* str, const char* format, va_list* args_ptr);
char* int_to_str(long long num, int need_sign, char* buffer);
void add_to_dest(char* dest, char* str, int left_alignment);
int float_to_str(char* dest, double num, int accuracy, int need_sign,
                 int left_alignment);
char* unsigned_long_to_str(unsigned long long, char* buffer);
void drop_flags(s21_format_t* flag_container);
int handle_d(char* str, s21_format_t* flag_container, va_list* args_ptr);
int handle_u(char* str, s21_format_t* flag_container, va_list* args_ptr);
int handle_simple_specials(char* str, char flag, s21_format_t* flag_container,
                           va_list* args_ptr);
void add_muilti_digit_num(s21_format_t* flag_container, unsigned char* p,
                          int is_left_alignment);