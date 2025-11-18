#include "s21_string.h"

// коммент для запуска тестов, раскоментить что бы запускать вручную
// int main() {
//    char str[100], str1[100];
//    s21_sprintf(str, "%d %u %+.18lf", 0, 2, 7.49);
//    sprintf(str1, "%d %u %+.18f", 0, 2, 7.49);
//    printf("%s\n%s\n", str, str1);
//   return 0;
//  }

void s21_sprintf(char* dest, const char* format, ...) {
  dest[0] = '\0';
  va_list args;
  va_start(args, format);
  va_list* args_ptr = &args;
  parse_format(dest, format, args_ptr);
  va_end(args);
}

int handle_d(char* str, s21_format_t* flag_container, va_list* args_ptr) {
  int is_memory_bad = 0;
  long long val;
  if (flag_container->is_long) {
    val = va_arg(*args_ptr, long long);
  } else if (flag_container->is_short) {
    int tmp = va_arg(*args_ptr, int);
    val = (short)tmp;
  } else {
    val = va_arg(*args_ptr, int);
  }
  char* buffer = malloc(sizeof(char) * 50);
  if (!buffer) {
    fprintf(stderr, "Error allocating memory");
    is_memory_bad = 1;
  } else {
    add_to_dest(str, int_to_str(val, flag_container->need_sign, buffer),
                flag_container->left_alignment);
  }
  free(buffer);
  drop_flags(flag_container);
  return is_memory_bad;
}

int handle_u(char* str, s21_format_t* flag_container, va_list* args_ptr) {
  int is_memory_bad = 0;
  char* buffer =
      malloc(sizeof(char) * 30);  // 20-21 цифра максимум, взял с запасом
  if (!buffer) {
    fprintf(stderr, "Error allocating memory");
    is_memory_bad = 1;
  } else {
    if (flag_container->is_long)
      add_to_dest(
          str,
          unsigned_long_to_str(va_arg(*args_ptr, unsigned long long), buffer),
          flag_container->left_alignment);
    else
      add_to_dest(str,
                  int_to_str(va_arg(*args_ptr, unsigned int),
                             flag_container->need_sign, buffer),
                  flag_container->left_alignment);
  }
  free(buffer);
  drop_flags(flag_container);
  return is_memory_bad;
}

int handle_simple_specials(char* str, char flag, s21_format_t* flag_container,
                           va_list* args_ptr) {
  switch (flag) {
    case 's':
      add_to_dest(str, va_arg(*args_ptr, char*),
                  flag_container->left_alignment);
      break;
    case '%':
      add_to_dest(str, "%", flag_container->left_alignment);
      break;
    case 'c':
      char buf[2];
      buf[1] = '\0';
      buf[0] = (char)va_arg(*args_ptr, int);
      add_to_dest(str, buf, flag_container->left_alignment);
      break;
  }
  drop_flags(flag_container);
  return 0;
}

int parse_format(char* str, const char* format, va_list* args_ptr) {
  s21_format_t f = {0};
  f.float_accuracy = 6;  // дефолтная точность 6
  for (unsigned char* p = (unsigned char*)format; *p != '\0'; p++) {
    if (f.is_percent) {
      f.is_percent = 0;
      if (*p == 'd')
        handle_d(str, &f, args_ptr);
      else if (*p == 'u')
        handle_u(str, &f, args_ptr);
      else if (*p == 'f')
        float_to_str(str, va_arg(*args_ptr, double), f.float_accuracy,
                     f.need_sign, f.left_alignment);
      else if (strchr("s%c", *p))
        handle_simple_specials(str, *p, &f, args_ptr);
      else if (*p == '.') {
        f.wait_for_accuracy = 1;
        f.is_percent = 1;
      } else if (f.wait_for_accuracy && isdigit(*p)) {
        add_muilti_digit_num(&f, p, 0);
      } else if (*p == '+') {
        f.need_sign = 1;
        f.is_percent = 1;
      } else if (*p == ' ') {
        f.need_sign = -1;
        f.is_percent = 1;
      } else if (*p == 'l') {
        f.is_long = 1;
        f.is_percent = 1;
      } else if (*p == 'h') {
        f.is_percent = 1;
        f.is_short = 1;
      } else if (*p == '-') {
        f.wait_for_left_alignment = 1;
        f.is_percent = 1;
      } else if (f.wait_for_left_alignment && isdigit(*p)) {
        add_muilti_digit_num(&f, p, 1);
      }
    } else if (*p == '%')
      f.is_percent = 1;
    else {
      char buf[2];
      buf[0] = *p;
      buf[1] = '\0';
      strcat(str, buf);
    }
  }
  return 0;
}

void add_muilti_digit_num(s21_format_t* flag_container, unsigned char* p,
                          int is_left_alignment) {
  if (is_left_alignment) {
    if (flag_container->left_alignment == 0)
      flag_container->left_alignment = *p - '0';
    else
      flag_container->left_alignment =
          flag_container->left_alignment * 10 + (*p - '0');
    flag_container->is_percent = 1;
  } else {
    if (flag_container->float_accuracy == 6)
      flag_container->float_accuracy = *p - '0';
    else
      flag_container->float_accuracy =
          flag_container->float_accuracy * 10 + (*p - '0');
    flag_container->is_percent = 1;
  }
}

void drop_flags(s21_format_t* flag_container) {  // дропаем флаги в контейнере
                                                 // до дефолтных значений
  flag_container->need_sign = 0;
  flag_container->wait_for_left_alignment = 0;
  flag_container->left_alignment = 0;
  flag_container->float_accuracy = 6;
  flag_container->is_short = 0;
  flag_container->is_long = 0;
}

void add_to_dest(char* dest, char* str, int left_alignment) {
  strcat(dest, str);
  if (left_alignment != 0) {
    for (int i = strlen(str); i < left_alignment; i++) {
      char buf[2];
      buf[0] = ' ';
      buf[1] = '\0';
      strcat(dest, buf);
    }
  }
}

char* unsigned_long_to_str(unsigned long long num, char* buffer) {
  int i = 0;
  if (num == 0) {
    buffer[0] = '0';
    buffer[1] = '\0';
    i = 1;
  }
  char temp[20];
  int len = 0;
  while (num > 0) {  // идем с конца, заносим в буфер
    temp[len++] = '0' + (num % 10);
    num /= 10;
  }
  for (int j = len - 1; j >= 0; j--)  // копируем чары как цифры в строку
    buffer[i++] = temp[j];
  buffer[i] = '\0';
  return buffer;
}

char* int_to_str(long long num, int need_sign, char* buffer) {
  int is_minimal_negative_long = 0;
  int i = 0;
  int is_negative = 0;
  if (num == 0) {
    buffer[0] = '0';
    buffer[1] = '\0';
    i = 1;
  }
  if (num == LLONG_MIN) {
    is_minimal_negative_long = 1;
  }
  if (num < 0) {
    is_negative = 1;
    num = -num;
  }
  char temp[20];
  int len = 0;
  while (num > 0) {  // идем с конца, заносим в буфер
    temp[len++] = '0' + (num % 10);
    num /= 10;
  }
  if (is_negative &&
      need_sign >= 0)  // добавляем знак если число < 0 и это разрешает флаг
    buffer[i++] = '-';
  else if (need_sign == 1 && !is_negative)
    buffer[i++] = '+';
  else if (need_sign == -1 && !is_negative)
    buffer[i++] = ' ';
  for (int j = len - 1; j >= 0; j--)  // копируем чары как цифры в строку
    buffer[i++] = temp[j];
  buffer[i] = '\0';
  if (is_minimal_negative_long) strcpy(buffer, "-9223372036854775808");
  return buffer;
}

int float_to_str(char* dest, double num, int accuracy, int need_sign,
                 int left_alignment) {
  int is_negative = 0, is_memory_bad = 0;
  if (num < 0) {
    is_negative = 1;
    num = -num;
  }

  int whole_part = (int)num;
  double fractional_part = num - whole_part;
  char* buffer =
      calloc(50, sizeof(char));  // 20-21 цифра максимум, взял с запасом
  if (!buffer) {
    fprintf(stderr, "Error allocating memory");
    is_memory_bad = 1;
  } else {
    if (is_negative) whole_part = -whole_part;
    char* whole_str = int_to_str(whole_part, need_sign,
                                 buffer);  // преобразуем целую часть в инт

    long multiplier = 1;  // задаем множитель, по точности(дефолт 6) для больших
                          // точностей используем long long
    for (int i = 0; i < accuracy; i++) multiplier *= 10;
    char* strfloat = calloc(strlen(whole_str) + accuracy + 2, sizeof(char));
    strfloat[0] = '\0';
    strcat(strfloat, whole_str);
    free(buffer);  // освобождаем buffer
    long fractional_int = (long)((fractional_part * multiplier) +
                                 0.5);  // преобразуем дробную часть в инт(0.453
                                        // = 453) округление float вверх
    char* frac_str = malloc(sizeof(char) * accuracy + 2);
    for (int i = accuracy - 1; i >= 0;
         i--) {  // выделяем по цифрам и преобразуем в строку
      frac_str[i] = '0' + (fractional_int % 10);
      fractional_int /= 10;
    }
    frac_str[accuracy] = '\0';
    strcat(strfloat, ".");  // копируем в dest
    strcat(strfloat, frac_str);
    add_to_dest(dest, strfloat, left_alignment);
    free(frac_str);
    free(strfloat);
  }
  return is_memory_bad;
}
