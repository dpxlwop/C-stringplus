#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include "s21_sprintf.h"
#define MAX_STR_LEN 1000


void test_equal(const char* expected, const char* actual, const char* message) {
    if (strcmp(expected, actual) == 0) {
        printf("PASS: %s\n", message);
    } else {
        printf("FAIL: %s\nExpected: \"%s\"\nActual: \"%s\"\n", message, expected, actual);
    }
}

void run_tests() {
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%c", 'A');
    sprintf(std_result, "%c", 'A');         
    test_equal(std_result, result, "Test %c character");

    s21_sprintf(result, "%d", -12345);
    sprintf(std_result, "%d", -12345); 
    test_equal(std_result, result, "Test %d negative number");

    s21_sprintf(result, "%+d", 12345);
    sprintf(std_result, "%+d", 12345);      
    test_equal(std_result, result, "Test %+d positive number with explicit sign");

    s21_sprintf(result, "%.3d", 12345);
    sprintf(std_result, "%.3d", 12345);       
    test_equal(std_result, result, "Test %.Xd no effect on integers");

    s21_sprintf(result, "% d", 12345);
    sprintf(std_result, "% d", 12345);        
    test_equal(std_result, result, "Test % d without explicit sign");

    short hval = 32767;
    s21_sprintf(result, "%hd", hval);
    sprintf(std_result, "%hd", hval);          
    test_equal(std_result, result, "Test %hd for short type");

    long lval = 2147483647L;
    s21_sprintf(result, "%ld", lval);
    sprintf(std_result, "%ld", lval);          
    test_equal(std_result, result, "Test %ld for long type");

    s21_sprintf(result, "%f", 123.456);
    sprintf(std_result, "%f", 123.456);       
    test_equal(std_result, result, "Test %f floating point number");

    s21_sprintf(result, "%.2f", 123.456);
    sprintf(std_result, "%.2f", 123.456);     
    test_equal(std_result, result, "Test %.2f floating point precision");

    s21_sprintf(result, "%s", "Hello World!");
    sprintf(std_result, "%s", "Hello World!"); 
    test_equal(std_result, result, "Test %s string output");

    s21_sprintf(result, "%u", 4294967295U);
    sprintf(std_result, "%u", 4294967295U);  
    test_equal(std_result, result, "Test %u unsigned integer");

    unsigned long ulval = 18446744073709551615UL;
    s21_sprintf(result, "%lu", ulval);
    sprintf(std_result, "%lu", ulval);        
    test_equal(std_result, result, "Test %lu large unsigned value");

    s21_sprintf(result, "%-10d", 12345);
    sprintf(std_result, "%-10d", 12345);   
    test_equal(std_result, result, "Test %-10d left alignment");
}

int main() {
    run_tests();
    return 0;
}