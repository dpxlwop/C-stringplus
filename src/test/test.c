#include <check.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include "../s21_sprintf.h"

#define MAX_STR_LEN 1000

extern void s21_sprintf(char*, const char*, ...);

START_TEST(test_char)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%c", 'A');
    sprintf(std_result, "%c", 'A');

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_d_negative_number)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%d", -12345);
    sprintf(std_result, "%d", -12345);

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_d_explicit_sign)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%+d", 12345);
    sprintf(std_result, "%+d", 12345);

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_d_no_sign)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "% d", 12345);
    sprintf(std_result, "% d", 12345);

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_hd_short_type)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    short hval = 32767;
    s21_sprintf(result, "%hd", hval);
    sprintf(std_result, "%hd", hval);

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_ld_long_type)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    long lval = 2147483647L;
    s21_sprintf(result, "%ld", lval);
    sprintf(std_result, "%ld", lval);

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_f_float_point)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%f", 123.456);
    sprintf(std_result, "%f", 123.456);

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_f_precision)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%.2f", 123.456);
    sprintf(std_result, "%.2f", 123.456);

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_s_string_output)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%s", "Hello World!");
    sprintf(std_result, "%s", "Hello World!");

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_u_unsigned_integer)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%u", 4294967295U);
    sprintf(std_result, "%u", 4294967295U);

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_lu_large_unsigned_value)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    unsigned long ulval = 18446744073709551615UL;
    s21_sprintf(result, "%lu", ulval);
    sprintf(std_result, "%lu", ulval);

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_left_alignment)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%-10d", 12345);
    sprintf(std_result, "%-10d", 12345);

    ck_assert_str_eq(result, std_result);
}
END_TEST

// Новые тесты для покрытия недостающих участков кода

START_TEST(test_percent_character)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%%");
    sprintf(std_result, "%%");

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_zero_value)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%d", 0);
    sprintf(std_result, "%d", 0);

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_very_large_negative)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%d", INT_MIN);
    sprintf(std_result, "%d", INT_MIN);

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_unsigned_zero)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%u", 0U);
    sprintf(std_result, "%u", 0U);

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_float_zero)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%f", 0.0);
    sprintf(std_result, "%f", 0.0);

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_float_negative)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%f", -123.456);
    sprintf(std_result, "%f", -123.456);

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_string2)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%s", "hello");
    sprintf(std_result, "%s", "hello");

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_multiple_formats)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%d %s %f", 42, "test", 3.14);
    sprintf(std_result, "%d %s %f", 42, "test", 3.14);

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_char_with_width)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%-5c", 'A');
    sprintf(std_result, "%-5c", 'A');

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_very_long_left_alignment)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%-100d", 123);
    sprintf(std_result, "%-100d", 123);

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_long_long)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%lld", 9223372036854775807LL);
    sprintf(std_result, "%lld", 9223372036854775807LL);

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_ullong)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%llu", 18446744073709551615ULL);
    sprintf(std_result, "%llu", 18446744073709551615ULL);

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_long_unsigned_zero)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%lu", 0UL);
    sprintf(std_result, "%lu", 0UL);

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_long_long_min)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%lld", LLONG_MIN);
    sprintf(std_result, "%lld", LLONG_MIN);

    ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_multinum_accuracy_float)
{
    char result[MAX_STR_LEN];
    char std_result[MAX_STR_LEN];

    s21_sprintf(result, "%.12f", -123.456);
    sprintf(std_result, "%.12f", -123.456);

    ck_assert_str_eq(result, std_result);
}
END_TEST


Suite *suite_s21_sprintf(void)
{
    Suite *s = suite_create("s21_sprintf");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_char);
    tcase_add_test(tc_core, test_d_negative_number);
    tcase_add_test(tc_core, test_d_explicit_sign);
    tcase_add_test(tc_core, test_d_no_sign);
    tcase_add_test(tc_core, test_hd_short_type);
    tcase_add_test(tc_core, test_ld_long_type);
    tcase_add_test(tc_core, test_f_float_point);
    tcase_add_test(tc_core, test_f_precision);
    tcase_add_test(tc_core, test_s_string_output);
    tcase_add_test(tc_core, test_u_unsigned_integer);
    tcase_add_test(tc_core, test_lu_large_unsigned_value);
    tcase_add_test(tc_core, test_left_alignment);
    tcase_add_test(tc_core, test_percent_character);
    tcase_add_test(tc_core, test_zero_value);
    tcase_add_test(tc_core, test_very_large_negative);
    tcase_add_test(tc_core, test_unsigned_zero);
    tcase_add_test(tc_core, test_float_zero);
    tcase_add_test(tc_core, test_float_negative);
    tcase_add_test(tc_core, test_string2);
    tcase_add_test(tc_core, test_multiple_formats);
    tcase_add_test(tc_core, test_char_with_width);
    tcase_add_test(tc_core, test_very_long_left_alignment);
    tcase_add_test(tc_core, test_long_long);
    tcase_add_test(tc_core, test_ullong);
    tcase_add_test(tc_core, test_long_unsigned_zero);
    tcase_add_test(tc_core, test_long_long_min);
    tcase_add_test(tc_core, test_multinum_accuracy_float);

    suite_add_tcase(s, tc_core);
    return s;
}

int main(void)
{
    int failed_count = 0;
    Suite *s = suite_s21_sprintf();  
    SRunner *sr = srunner_create(s); 

    srunner_run_all(sr, CK_VERBOSE);

    failed_count = srunner_ntests_failed(sr);

    srunner_free(sr);

    return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}