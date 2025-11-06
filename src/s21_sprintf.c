#include "s21_sprintf.h"


int main() {
    char* str = calloc(100, sizeof(char));
    s21_sprintf(str, "hello %u %s %f %%", 1, 2, 3);
    printf("%s\n", str);
    int_to_str(4096, str, 0);
    free(str);

    return 0;
}



void s21_sprintf(char* dest, const char* format, ...) {
    int count = 0;
    int* methods = malloc(sizeof(int));
    parce_format(dest, methods, format, &count);
    printf("arguments: %d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d\n", methods[i]);
    }

}


void parce_format(char* str, int* methods, const char *format, int* count){
    int is_percent = 0;
    for (unsigned char* p = (unsigned char*)format; *p != '\0'; p++) {
        if (is_percent){
            is_percent = 0;
            if (*p == 'd') 
                methods[(*count)] = 1;
            else if (*p == 's') 
                methods[(*count)] = 2;
            else if (*p == 'f') 
                methods[(*count)] = 3;
            else if (*p == 'c') 
                methods[(*count)] = 4;
            else if (*p == 'u') 
                methods[(*count)] = 5;
            else if (*p == '%'){
                char buf[1];
                buf[0] = '%';
                buf[1] = '\0';
                strcat(str, buf);
            } else if (*p == '+')
                methods[(*count)] = 7;
            else if (*p == ' ')
                methods[(*count)] = 8;
            else if (*p == '-')
                methods[(*count)] = 9;
            else if (*p == '.')             //(эт пизда)
                methods[(*count)] = 10;
                /*TODO
                добавить обработку следующего числа и запись его в массив.
                %.XXX записывать X*/
            else if (*p == 'h')
                methods[(*count)] = 11;
            else if (*p == 'l')
                methods[(*count)] = 12;
            else 
                fprintf(stderr, "Error: unknown format specifier\n");
            methods = realloc(methods, sizeof(int) * (*(count) + 1));
            (*count)++;
            if (methods == NULL) {
                fprintf(stderr, "Error: memory allocation failed\n");
                exit(1);
            }
            }
        else if (*p == '%') {
            is_percent = 1;
        }
        else{
            char buf[1];
            buf[0] = *p;
            buf[1] = '\0';
            strcat(str, buf);
            }
    }
}


void int_to_str(int num, char* dest, int need_sign) {
    int is_negative = 0, i = 0, count;
    for (count = 0; num != 0; count++) num/=10;
    char* buf = calloc(count+1, sizeof(char));
    if (num == 0) 
        strcpy(dest, "0");
    if (num < 0){
        num*=-1;
        is_negative = 1;
    }
    while (num >= 10) {
        buf[i++] = num%10;
        num/10;
    }
    if (is_negative) buf[i++] = '-';
    else if (need_sign) buf[i++] = '+';
    printf("%s\n", buf);
    free(buf);
}