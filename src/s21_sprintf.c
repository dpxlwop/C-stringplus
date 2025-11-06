#include "s21_sprintf.h"


int main() {
    char* str = calloc(150, sizeof(char));
    s21_sprintf(str, "macan %s %c %u %% %d %f %f %.3f", "frontender", 'r', 10, -10, 4.543, -4.543, 982341.12345);
    printf("%s\n", str);
    free(str);
    char* str1 = calloc(150, sizeof(char));
    s21_sprintf(str1, "%+d % d %.4f", 10, -10, 4.543);
    printf("%s\n", str1);
    free(str1);
    return 0;
}

void s21_sprintf(char* dest, const char* format, ...) {
    va_list args;
    va_start(args, format);
    va_list* args_ptr = &args;
    parce_format(dest, format, args_ptr);
    va_end(args);
}

void parce_format(char* str, const char *format, va_list* args_ptr){
    s21_format_t flag_container = {0};  
    flag_container.float_accuracy = 6;      //дефолтная точность 6
    for (unsigned char* p = (unsigned char*)format; *p != '\0'; p++) {
        if (flag_container.is_percent){
            flag_container.is_percent = 0;
            if (*p == 'd'){
                int arg = va_arg(*args_ptr, int), tmp = arg, count;     //берем аргумент
                for (count = 0; tmp != 0; count++) tmp/=10;             //считаем кол-во цифр
                if (count == 0) count+=2;
                char* new_str = malloc(sizeof(char)*count);             
                int_to_str(arg, new_str, flag_container.need_sign, count);
                add_to_dest(str, new_str);
                free(new_str);
                flag_container.need_sign = 0;       //по дефолту сбрасываем флаг
            } else if (*p == 's') {
                add_to_dest(str, va_arg(*args_ptr, char*));
            } else if (*p == '%') {
                add_to_dest(str, "%");
            } else if (*p == 'c') {
                char buf[2]; buf[1] = '\0'; buf[0] = (char)va_arg(*args_ptr, int);
                add_to_dest(str, buf);
            } else if (*p == 'u'){
                int arg = va_arg(*args_ptr, unsigned int), tmp = arg, count;        //тоже самое что и int
                for (count = 0; tmp != 0; count++) tmp/=10;
                char* new_str = malloc(sizeof(char)*count);
                int_to_str(arg, new_str, flag_container.need_sign, count);
                add_to_dest(str, new_str);
                free(new_str);
                flag_container.need_sign = 0;
            } else if (*p == 'f'){
                float_to_str(str, va_arg(*args_ptr, double), flag_container.float_accuracy, flag_container.need_sign);  //по дефолту va_arg возвращает дабл
                flag_container.float_accuracy = 6;
                flag_container.need_sign = 0;
            } else if (*p == '.') {
                flag_container.wait_for_accuracy = 1;
                flag_container.is_percent = 1;
            } else if (flag_container.wait_for_accuracy)
            {
                flag_container.wait_for_accuracy = 0;
                flag_container.is_percent = 1;
                flag_container.float_accuracy = *p - '0';
            }
            else if(*p == '+'){
                flag_container.need_sign = 1;
                flag_container.is_percent = 1;
            }else if (*p == ' '){
                flag_container.need_sign = -1;
                flag_container.is_percent = 1;
            }
        }
        else if (*p == '%') {
            flag_container.is_percent = 1;
        }
        else{
            char buf[2];
            buf[0] = *p;
            buf[1] = '\0';
            strcat(str, buf);
            }
    }
}


void add_to_dest(char* dest, char* str) {
    strcat(dest, str);
}

void int_to_str(int num, char* dest, int need_sign, int count) {
    int is_negative = 0, i = 0;
    if (num == 0) 
        strcpy(dest, "0");
    else{
    if (num < 0){
        num*=-1;
        is_negative = 1;
    }
    char* buf = calloc(count + 1, sizeof(char));
    while (num != 0) {      //идем с конца, заносим в буфер
        buf[i] = '0' + num%10;
        i++;
        num/=10;
    }
    if (is_negative && need_sign >= 0) {        //добавляем знак если число < 0 и это разрешает флаг
        buf[i++] = '-';
        count++;
    }
    else if (need_sign == 1) {                  //принудительно добавляем флаг
        buf[i++] = is_negative ? '-' : '+';
        count++;
    }
    for (int i = 0; i < count; i++){            //копируем чары как цифры в строку
        char tmp[2]; tmp[1] = '\0';
        tmp[0] = buf[count - i -1];
        strcat(dest, tmp);
    }
    free(buf);
    }
}

void float_to_str(char* dest, double num, int accuracy, int need_sign) {
    int is_negative = 0, whole_count;
    if (num < 0) {
        num*=-1;
        is_negative = 1;
    }
    int whole_part = (int)num, tmp = whole_part;        //выделяем целую и дробную часть
    float fractional_part = num - whole_part;

    for (whole_count = 0; tmp != 0; whole_count++) tmp/=10;     //счет цифр в целой части и преобразование в инт
    if (is_negative) whole_part*=-1;
    int_to_str(whole_part, dest, need_sign, whole_count);       //запись в dest на лету*

    int multiplier = 1;                                         //задаем множитель, по точности(дефолт 6)
    for (int i = 0; i < accuracy; i++) {
        multiplier *= 10;
    }
    int fractional_int = (int)((fractional_part * multiplier)); //преобразуем дробную часть в инт(0.453 = 453)
    char frac_str[10] = {0};
    for (int i = accuracy - 1; i >= 0; i--) {                   //выделяем по цифрам и преобразуем в строку
        frac_str[i] = '0' + (fractional_int % 10);
        fractional_int /= 10;
    }
    strcat(dest, ".");                                          //копируем в dest
    strcat(dest, frac_str);

}