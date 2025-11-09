#include "s21_sprintf.h"

/*TODO
1. Добавить обработку выравнивания в parse_format, запись в переменную
2. Изменить add_to_dest для выравнивания
3. Добавить в функции зависимые от add_to_dest передачу выравнивания
4. Исправить leaks
5. Из parse_format вынести обработку %d, %u в отдельные функции, что бы сократить функцию <50 строк!
*/

int main() {
    char str[150], str1[150], str2[150], str3[150];
    s21_sprintf(str, "macan %s %c %u %% %d %f %f %.3f", "frontender", 'r', 10, -10, 4.543, -4.543, 982341.12345);
    s21_sprintf(str1, "%+d %d %.4f", 10, -10, 4.543);
    
    sprintf(str2, "macan %s %c %u %% %d %f %f %.3f", "frontender", 'r', 10, -10, 4.543, -4.543, 982341.12345);
    sprintf(str3, "%+d %d %.4f", 10, -10, 4.543);

    printf("\n===S21_SPRINTF OUTPUT===\n%s\n%s\n\n===SYSTEM SPRINTF OUTPUT===\n%s\n%s", str,str1,str2,str3);

    short min_short = SHRT_MIN, max_short = SHRT_MAX;
    unsigned short max_unsigned_short = USHRT_MAX;
    int min_int = INT_MIN, max_int = INT_MAX;
    unsigned int max_unsigned_int = UINT_MAX;
    long min_long = LONG_MIN, max_long = LONG_MAX;
    unsigned long max_unsigned_long = ULONG_MAX;

    char c1[500], c2[500];
    s21_sprintf(c1, "short: %hd %hd\nunsigned short: %hu\nint: %d %d\nunsigned int: %u\nlong: %ld %ld\nunsigned long: %lu",min_short,max_short,max_unsigned_short, min_int, max_int, max_unsigned_int, min_long, max_long, max_unsigned_long);
    sprintf(c2, "short: %hd %hd\nunsigned short: %hu\nint: %d %d\nunsigned int: %u\nlong: %ld %ld\nunsigned long: %lu",min_short,max_short,max_unsigned_short, min_int, max_int, max_unsigned_int, min_long, max_long, max_unsigned_long);
    printf("\n\n===S21 DIFF DATA TYPE OUTPUT===\n%s\n\n===SYSTEM DIFF DATA TYPE OUTPUT===\n%s\n", c1, c2);
    return 0;
}

void s21_sprintf(char* dest, const char* format, ...) {
    dest[0] = '\0';
    va_list args;
    va_start(args, format);
    va_list* args_ptr = &args;
    parse_format(dest, format, args_ptr);
    va_end(args);
}

int parse_format(char* str, const char *format, va_list* args_ptr){
    s21_format_t flag_container = {0};  
    flag_container.float_accuracy = 6;      //дефолтная точность 6
    for (unsigned char* p = (unsigned char*)format; *p != '\0'; p++) {
        if (flag_container.is_percent){
            flag_container.is_percent = 0;
            if (*p == 'd'){
                long long val;
                if (flag_container.is_long)
                    val = va_arg(*args_ptr, long long);
                else if (flag_container.is_short){
                    int tmp = va_arg(*args_ptr, int); 
                    val = (short)tmp;
                } else
                    val = va_arg(*args_ptr, int);
                char* buffer = malloc(sizeof(char*) * 50);      //20-21 цифра максимум, взял с запасом
                if (!buffer){
                    fprintf(stderr, "Error allocating memory");
                    return 1;
                }
                add_to_dest(str, int_to_str(val, flag_container.need_sign, buffer));
                free(buffer);
                flag_container.need_sign = 0;
                flag_container.is_short = 0;
                flag_container.is_long = 0;
            } else if (*p == 's'){
                add_to_dest(str, va_arg(*args_ptr, char*));
            } else if (*p == '%'){
                add_to_dest(str, "%");
            } else if (*p == 'c'){
                char buf[2]; buf[1] = '\0'; buf[0] = (char)va_arg(*args_ptr, int);
                add_to_dest(str, buf);
            } else if (*p == 'u'){
                char* buffer = malloc(sizeof(char*) * 30);      //20-21 цифра максимум, взял с запасом
                if (!buffer){
                    fprintf(stderr, "Error allocating memory");
                    return 1;
                }
                if (flag_container.is_long)
                    add_to_dest(str, unsigned_long_to_str(va_arg(*args_ptr, unsigned long long), flag_container.need_sign, buffer));
                else
                    add_to_dest(str, int_to_str(va_arg(*args_ptr, unsigned int), flag_container.need_sign, buffer));
                free(buffer);
                flag_container.need_sign = 0;
                flag_container.is_short = 0;
                flag_container.is_long = 0;
            } else if (*p == 'f'){
                float_to_str(str, va_arg(*args_ptr, double), flag_container.float_accuracy, flag_container.need_sign);  //по дефолту va_arg возвращает дабл
                flag_container.float_accuracy = 6;
                flag_container.need_sign = 0;
            } else if (*p == '.'){
                flag_container.wait_for_accuracy = 1;
                flag_container.is_percent = 1;
            } else if (flag_container.wait_for_accuracy){
                flag_container.wait_for_accuracy = 0;
                flag_container.is_percent = 1;
                flag_container.float_accuracy = *p - '0';
            } else if(*p == '+'){
                flag_container.need_sign = 1;
                flag_container.is_percent = 1;
            }else if (*p == ' '){
                flag_container.need_sign = -1;
                flag_container.is_percent = 1;
            } else if (*p == 'l'){
                flag_container.is_long = 1;
                flag_container.is_percent = 1;
            } else if (*p == 'h'){
                flag_container.is_percent = 1;
                flag_container.is_short = 1;
            }
        }
        else if (*p == '%') {
            flag_container.is_percent = 1;
        }
        else {
            char buf[1];
            buf[0] = *p;
            buf[1] = '\0';
            strcat(str, buf);
            }
    }
    return 0;
}


void add_to_dest(char* dest, char* str) {
    strcat(dest, str);
}

char* unsigned_long_to_str(unsigned long long num, int need_sign, char* buffer){
    
    int i = 0;
    if (num == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
    }
    char temp[20];
    int len = 0;
    while (num > 0) {       //идем с конца, заносим в буфер
        temp[len++] = '0' + (num % 10);
        num /= 10;
    }
    if (need_sign == 1)
        buffer[i++] = '+';
    for (int j = len - 1; j >= 0; j--)        //копируем чары как цифры в строку
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
    while (num > 0) {       //идем с конца, заносим в буфер
        temp[len++] = '0' + (num % 10);
        num /= 10;
    }
    if (is_negative && need_sign >= 0)    //добавляем знак если число < 0 и это разрешает флаг
        buffer[i++] = '-';
    else if (need_sign == 1 && !is_negative)
        buffer[i++] = '+';
    for (int j = len - 1; j >= 0; j--)        //копируем чары как цифры в строку
        buffer[i++] = temp[j];
    buffer[i] = '\0';
    if (is_minimal_negative_long) strcpy(buffer, "-9223372036854775808");
    return buffer;
}

int float_to_str(char* dest, double num, int accuracy, int need_sign) {
    int is_negative = 0;
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    int whole_part = (int)num;
    double fractional_part = num - whole_part;
    char* buffer = malloc(sizeof(char*) * 30);      //20-21 цифра максимум, взял с запасом
    if (!buffer){
        fprintf(stderr, "Error allocating memory");
        return 1;
    }
    char* whole_str = int_to_str(whole_part, need_sign, buffer);        //преобразуем целую часть в инт
    if (is_negative && need_sign >= 0) {
        char* tmp = malloc(strlen(whole_str) + 2);
        tmp[0] = '-';
        strcpy(tmp + 1, whole_str);
        free(whole_str);        //освобождение whole_str, который указывает на buffer => освобождаем buffer
        whole_str = tmp;
    }
    strcat(dest, whole_str);
    free(whole_str);            //освобождаем whole_str как tmp
    int multiplier = 1; //задаем множитель, по точности(дефолт 6)
    for (int i = 0; i < accuracy; i++) multiplier *= 10;

    int fractional_int = (int)((fractional_part * multiplier) + 0.5);//преобразуем дробную часть в инт(0.453 = 453)
                                                            //округление float вверх
    char frac_str[15] = {0};
    for (int i = accuracy - 1; i >= 0; i--) {           //выделяем по цифрам и преобразуем в строку
        frac_str[i] = '0' + (fractional_int % 10);
        fractional_int /= 10;
    }
    strcat(dest, ".");                                   //копируем в dest
    strcat(dest, frac_str);
    return 0;
}