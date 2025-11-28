#include <check.h>
#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "../s21_string.h"
#define MAX_STR_LEN 1000

#define S21_NULL ((void *)0)
typedef unsigned long s21_size_t;

START_TEST(test_char) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%c", 'A');
  sprintf(std_result, "%c", 'A');

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_d_negative_number) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%d", -12345);
  sprintf(std_result, "%d", -12345);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_d_explicit_sign) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%+d", 12345);
  sprintf(std_result, "%+d", 12345);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_d_no_sign) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "% d", 12345);
  sprintf(std_result, "% d", 12345);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_hd_short_type) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  short hval = 32767;
  s21_sprintf(result, "%hd", hval);
  sprintf(std_result, "%hd", hval);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_ld_long_type) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  long lval = 2147483647L;
  s21_sprintf(result, "%ld", lval);
  sprintf(std_result, "%ld", lval);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_f_float_point) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%f", 123.456);
  sprintf(std_result, "%f", 123.456);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_f_precision) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%.2f", 123.456);
  sprintf(std_result, "%.2f", 123.456);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_f_multinumber_precision) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%.12f", 123.456);
  sprintf(std_result, "%.12f", 123.456);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_s_string_output) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%s", "Hello World!");
  sprintf(std_result, "%s", "Hello World!");

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_u_unsigned_integer) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%u", 4294967295U);
  sprintf(std_result, "%u", 4294967295U);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_lu_large_unsigned_value) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  unsigned long ulval = 18446744073709551615UL;
  s21_sprintf(result, "%lu", ulval);
  sprintf(std_result, "%lu", ulval);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_left_alignment) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%-10d", 12345);
  sprintf(std_result, "%-10d", 12345);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_percent_character) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%%");
  sprintf(std_result, "%%");

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_zero_value) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%d", 0);
  sprintf(std_result, "%d", 0);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_very_large_negative) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%d", INT_MIN);
  sprintf(std_result, "%d", INT_MIN);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_unsigned_zero) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%u", 0U);
  sprintf(std_result, "%u", 0U);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_float_zero) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%f", 0.0);
  sprintf(std_result, "%f", 0.0);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_float_negative) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%f", -123.456);
  sprintf(std_result, "%f", -123.456);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_string2) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%s", "hello");
  sprintf(std_result, "%s", "hello");

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_multiple_formats) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%d %s %f", 42, "test", 3.14);
  sprintf(std_result, "%d %s %f", 42, "test", 3.14);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_char_with_width) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%-5c", 'A');
  sprintf(std_result, "%-5c", 'A');

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_very_long_left_alignment) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%-100d", 123);
  sprintf(std_result, "%-100d", 123);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_long_long) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%lld", 9223372036854775807LL);
  sprintf(std_result, "%lld", 9223372036854775807LL);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_ullong) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%llu", 18446744073709551615ULL);
  sprintf(std_result, "%llu", 18446744073709551615ULL);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_long_unsigned_zero) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%lu", 0UL);
  sprintf(std_result, "%lu", 0UL);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_long_long_min) {
  char result[MAX_STR_LEN];
  char std_result[MAX_STR_LEN];

  s21_sprintf(result, "%lld", LLONG_MIN);
  sprintf(std_result, "%lld", LLONG_MIN);

  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_memchr_basic) {
  const char str[] = "Hello World!";
  char *result = s21_memchr(str, 'W', sizeof(str));
  char *std_result = memchr(str, 'W', sizeof(str));

  ck_assert_ptr_eq(result, std_result);
}
END_TEST

START_TEST(test_memchr_not_found) {
  const char str[] = "Hello World!";
  char *result = s21_memchr(str, 'x', sizeof(str));
  char *std_result = memchr(str, 'x', sizeof(str));

  ck_assert_ptr_eq(result, std_result);
}
END_TEST

START_TEST(test_memchr_zero_length) {
  const char str[] = "Hello World!";
  char *result = s21_memchr(str, 'H', 0);
  char *std_result = memchr(str, 'H', 0);

  ck_assert_ptr_eq(result, std_result);
}
END_TEST

START_TEST(test_memchr_null_byte) {
  const char str[] = "Hello";
  char *result = s21_memchr(str, '\0', sizeof(str));
  char *std_result = memchr(str, '\0', sizeof(str));

  ck_assert_ptr_eq(result, std_result);
}
END_TEST

START_TEST(test_memcmp_equal) {
  const char str1[] = "Hello";
  const char str2[] = "Hello";

  int result = s21_memcmp(str1, str2, 5);
  int std_result = memcmp(str1, str2, 5);

  ck_assert_int_eq(result == 0, std_result == 0);
}
END_TEST

START_TEST(test_memcmp_not_equal) {
  const char str1[] = "Hello";
  const char str2[] = "Hellp";

  int result = s21_memcmp(str1, str2, 5);
  int std_result = memcmp(str1, str2, 5);

  ck_assert_int_eq(result < 0, std_result < 0);
}
END_TEST

START_TEST(test_memcmp_zero_length) {
  const char str1[] = "Hello";
  const char str2[] = "World";

  int result = s21_memcmp(str1, str2, 0);
  int std_result = memcmp(str1, str2, 0);

  ck_assert_int_eq(result, std_result);
}
END_TEST

START_TEST(test_memcpy_basic) {
  char dest1[20];
  char dest2[20];
  const char src[] = "Hello World!";

  s21_memcpy(dest1, src, 13);
  memcpy(dest2, src, 13);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memcpy_partial) {
  char dest1[20];
  char dest2[20];
  const char src[] = "Hello World!";

  s21_memcpy(dest1, src, 5);
  memcpy(dest2, src, 5);
  dest1[5] = '\0';
  dest2[5] = '\0';

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memcpy_zero_length) {
  char dest1[20] = "Original";
  char dest2[20] = "Original";
  const char src[] = "New Data";

  s21_memcpy(dest1, src, 0);
  memcpy(dest2, src, 0);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memset_basic) {
  char str1[20] = "Hello World!";
  char str2[20] = "Hello World!";

  s21_memset(str1, 'x', 5);
  memset(str2, 'x', 5);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_memset_zero) {
  char str1[20] = "Hello World!";
  char str2[20] = "Hello World!";

  s21_memset(str1, 0, 5);
  memset(str2, 0, 5);

  ck_assert_mem_eq(str1, str2, 20);
}
END_TEST

START_TEST(test_memset_zero_length) {
  char str1[20] = "Hello World!";
  char str2[20] = "Hello World!";

  s21_size_t zero_length = 0;
  s21_memset(str1, 'x', zero_length);
  memset(str2, 'x', zero_length);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_strlen_basic) {
  const char str[] = "Hello World!";

  s21_size_t result = s21_strlen(str);
  s21_size_t std_result = strlen(str);

  ck_assert_int_eq(result, std_result);
}
END_TEST

START_TEST(test_strlen_empty) {
  const char str[] = "";

  s21_size_t result = s21_strlen(str);
  s21_size_t std_result = strlen(str);

  ck_assert_int_eq(result, std_result);
}
END_TEST

START_TEST(test_strlen_long) {
  const char str[] = "This is a very long string for testing purposes";

  s21_size_t result = s21_strlen(str);
  s21_size_t std_result = strlen(str);

  ck_assert_int_eq(result, std_result);
}
END_TEST

START_TEST(test_strncat_basic) {
  char dest1[50] = "Hello";
  char dest2[50] = "Hello";
  const char src[] = " World!";

  s21_strncat(dest1, src, 7);
  strncat(dest2, src, 7);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncat_partial) {
  char dest1[50] = "Hello";
  char dest2[50] = "Hello";
  const char src[] = " World!";

  s21_strncat(dest1, src, 3);
  strncat(dest2, src, 3);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncat_zero_length) {
  char dest1[50] = "Hello";
  char dest2[50] = "Hello";
  const char src[] = " World!";

  s21_strncat(dest1, src, 0);
  strncat(dest2, src, 0);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strchr_basic) {
  const char str[] = "Hello World!";

  char *result = s21_strchr(str, 'W');
  char *std_result = strchr(str, 'W');

  ck_assert_ptr_eq(result, std_result);
}
END_TEST

START_TEST(test_strchr_not_found) {
  const char str[] = "Hello World!";

  char *result = s21_strchr(str, 'x');
  char *std_result = strchr(str, 'x');

  ck_assert_ptr_eq(result, std_result);
}
END_TEST

START_TEST(test_strchr_null_byte) {
  const char str[] = "Hello";

  char *result = s21_strchr(str, '\0');
  char *std_result = strchr(str, '\0');

  ck_assert_ptr_eq(result, std_result);
}
END_TEST

START_TEST(test_strncmp_equal) {
  const char str1[] = "Hello";
  const char str2[] = "Hello";

  int result = s21_strncmp(str1, str2, 5);
  int std_result = strncmp(str1, str2, 5);

  ck_assert_int_eq(result, std_result);
}
END_TEST

START_TEST(test_strncmp_not_equal) {
  const char str1[] = "Hello";
  const char str2[] = "Hellp";

  int result = s21_strncmp(str1, str2, 5);
  int std_result = strncmp(str1, str2, 5);

  ck_assert_int_eq(result < 0, std_result < 0);
}
END_TEST

START_TEST(test_strncmp_partial) {
  const char str1[] = "Hello";
  const char str2[] = "Hellp";

  int result = s21_strncmp(str1, str2, 4);
  int std_result = strncmp(str1, str2, 4);

  ck_assert_int_eq(result, std_result);
}
END_TEST

START_TEST(test_strncpy_basic) {
  char dest1[20];
  char dest2[20];
  const char src[] = "Hello World!";

  s21_strncpy(dest1, src, 13);
  strncpy(dest2, src, 13);
  dest1[13] = '\0';
  dest2[13] = '\0';

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncpy_partial) {
  char dest1[20];
  char dest2[20];
  const char src[] = "Hello World!";

  s21_strncpy(dest1, src, 5);
  strncpy(dest2, src, 5);
  dest1[5] = '\0';
  dest2[5] = '\0';

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncpy_zero_padding) {
  char dest1[20] = "AAAAAAAAAAAAAAA";
  char dest2[20] = "AAAAAAAAAAAAAAA";
  const char src[] = "Hello";

  s21_strncpy(dest1, src, 10);
  strncpy(dest2, src, 10);

  ck_assert_mem_eq(dest1, dest2, 20);
}
END_TEST

START_TEST(test_strcspn_basic) {
  const char str1[] = "Hello World!";
  const char str2[] = " !";

  s21_size_t result = s21_strcspn(str1, str2);
  s21_size_t std_result = strcspn(str1, str2);

  ck_assert_int_eq(result, std_result);
}
END_TEST

START_TEST(test_strcspn_no_match) {
  const char str1[] = "Hello";
  const char str2[] = "xyz";

  s21_size_t result = s21_strcspn(str1, str2);
  s21_size_t std_result = strcspn(str1, str2);

  ck_assert_int_eq(result, std_result);
}
END_TEST

START_TEST(test_strcspn_empty_reject) {
  const char str1[] = "Hello World!";
  const char str2[] = "";

  s21_size_t result = s21_strcspn(str1, str2);
  s21_size_t std_result = strcspn(str1, str2);

  ck_assert_int_eq(result, std_result);
}
END_TEST

START_TEST(test_strpbrk_basic) {
  const char str1[] = "Hello World!";
  const char str2[] = " !";

  char *result = s21_strpbrk(str1, str2);
  char *std_result = strpbrk(str1, str2);

  ck_assert_ptr_eq(result, std_result);
}
END_TEST

START_TEST(test_strpbrk_not_found) {
  const char str1[] = "Hello";
  const char str2[] = "xyz";

  char *result = s21_strpbrk(str1, str2);
  const char *std_result = strpbrk(str1, str2);

  ck_assert_ptr_eq(result, std_result);
}
END_TEST

START_TEST(test_strrchr_basic) {
  const char str[] = "Hello World!";

  char *result = s21_strrchr(str, 'l');
  char *std_result = strrchr(str, 'l');

  ck_assert_ptr_eq(result, std_result);
}
END_TEST

START_TEST(test_strrchr_not_found) {
  const char str[] = "Hello World!";

  char *result = s21_strrchr(str, 'x');
  char *std_result = strrchr(str, 'x');

  ck_assert_ptr_eq(result, std_result);
}
END_TEST

START_TEST(test_strrchr_null_byte) {
  const char str[] = "Hello";

  char *result = s21_strrchr(str, '\0');
  char *std_result = strrchr(str, '\0');

  ck_assert_ptr_eq(result, std_result);
}
END_TEST

START_TEST(test_strstr_basic) {
  const char haystack[] = "Hello World!";
  const char needle[] = "World";

  char *result = s21_strstr(haystack, needle);
  char *std_result = strstr(haystack, needle);

  ck_assert_ptr_eq(result, std_result);
}
END_TEST

START_TEST(test_strstr_not_found) {
  const char haystack[] = "Hello World!";
  const char needle[] = "xyz";

  char *result = s21_strstr(haystack, needle);
  char *std_result = strstr(haystack, needle);

  ck_assert_ptr_eq(result, std_result);
}
END_TEST

START_TEST(test_strstr_empty_needle) {
  const char haystack[] = "Hello World!";
  const char needle[] = "";

  char *result = s21_strstr(haystack, needle);
  char *std_result = strstr(haystack, needle);

  ck_assert_ptr_eq(result, std_result);
}
END_TEST

START_TEST(test_strtok_basic) {
  char str1[] = "Hello,World,Test";
  char str2[] = "Hello,World,Test";
  const char delim[] = ",";

  char *result1 = s21_strtok(str1, delim);
  char *result2 = strtok(str2, delim);
  ck_assert_str_eq(result1, result2);

  result1 = s21_strtok(S21_NULL, delim);
  result2 = strtok(S21_NULL, delim);
  ck_assert_str_eq(result1, result2);

  result1 = s21_strtok(S21_NULL, delim);
  result2 = strtok(S21_NULL, delim);
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strtok_multiple_delims) {
  char str1[] = "Hello, World;Test";
  char str2[] = "Hello, World;Test";
  const char delim[] = ", ;";

  char *result1 = s21_strtok(str1, delim);
  char *result2 = strtok(str2, delim);
  ck_assert_str_eq(result1, result2);

  result1 = s21_strtok(S21_NULL, delim);
  result2 = strtok(S21_NULL, delim);
  ck_assert_str_eq(result1, result2);
}
END_TEST

START_TEST(test_strtok_no_delims) {
  char str1[] = "HelloWorld";
  char str2[] = "HelloWorld";
  const char delim[] = ",";

  char *result1 = s21_strtok(str1, delim);
  char *result2 = strtok(str2, delim);
  ck_assert_str_eq(result1, result2);

  result1 = s21_strtok(S21_NULL, delim);
  result2 = strtok(S21_NULL, delim);
  ck_assert_ptr_eq(result1, result2);
}
END_TEST

START_TEST(test_strerror_known) {
  char *result = s21_strerror(ENOENT);
  char *std_result = strerror(ENOENT);
  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_strerror_zero) {
  char *result = s21_strerror(0);
  char *std_result = strerror(0);
  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_strerror_invalid_large) {
  char *result = s21_strerror(999);
  char *std_result = strerror(999);
  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_strerror_edge_negative) {
  char *result = s21_strerror(-1);
  char *std_result = strerror(-1);
  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_strerror_boundary_min) {
  char *result = s21_strerror(1);
  char *std_result = strerror(1);
  ck_assert_str_eq(result, std_result);
}
END_TEST

START_TEST(test_strerror_common_codes) {
  for (int i = 0; i <= 5; i++) {
    char *result = s21_strerror(i);
    char *std_result = strerror(i);
    ck_assert_str_eq(result, std_result);
  }
}
END_TEST

Suite *suite_s21_sprintf(void) {
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
  tcase_add_test(tc_core, test_f_multinumber_precision);
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

  suite_add_tcase(s, tc_core);
  return s;
}

Suite *suite_s21_string(void) {
  Suite *s = suite_create("s21_string");
  TCase *tc_string = tcase_create("String");

  tcase_add_test(tc_string, test_memchr_basic);
  tcase_add_test(tc_string, test_memchr_not_found);
  tcase_add_test(tc_string, test_memchr_zero_length);
  tcase_add_test(tc_string, test_memchr_null_byte);

  tcase_add_test(tc_string, test_memcmp_equal);
  tcase_add_test(tc_string, test_memcmp_not_equal);
  tcase_add_test(tc_string, test_memcmp_zero_length);

  tcase_add_test(tc_string, test_memcpy_basic);
  tcase_add_test(tc_string, test_memcpy_partial);
  tcase_add_test(tc_string, test_memcpy_zero_length);

  tcase_add_test(tc_string, test_memset_basic);
  tcase_add_test(tc_string, test_memset_zero);
  tcase_add_test(tc_string, test_memset_zero_length);

  tcase_add_test(tc_string, test_strlen_basic);
  tcase_add_test(tc_string, test_strlen_empty);
  tcase_add_test(tc_string, test_strlen_long);

  tcase_add_test(tc_string, test_strncat_basic);
  tcase_add_test(tc_string, test_strncat_partial);
  tcase_add_test(tc_string, test_strncat_zero_length);

  tcase_add_test(tc_string, test_strchr_basic);
  tcase_add_test(tc_string, test_strchr_not_found);
  tcase_add_test(tc_string, test_strchr_null_byte);

  tcase_add_test(tc_string, test_strncmp_equal);
  tcase_add_test(tc_string, test_strncmp_not_equal);
  tcase_add_test(tc_string, test_strncmp_partial);

  tcase_add_test(tc_string, test_strncpy_basic);
  tcase_add_test(tc_string, test_strncpy_partial);
  tcase_add_test(tc_string, test_strncpy_zero_padding);

  tcase_add_test(tc_string, test_strcspn_basic);
  tcase_add_test(tc_string, test_strcspn_no_match);
  tcase_add_test(tc_string, test_strcspn_empty_reject);

  tcase_add_test(tc_string, test_strerror_known);
  tcase_add_test(tc_string, test_strerror_zero);
  tcase_add_test(tc_string, test_strerror_invalid_large);
  tcase_add_test(tc_string, test_strerror_edge_negative);
  tcase_add_test(tc_string, test_strerror_boundary_min);
  tcase_add_test(tc_string, test_strerror_common_codes);

  tcase_add_test(tc_string, test_strpbrk_basic);
  tcase_add_test(tc_string, test_strpbrk_not_found);

  tcase_add_test(tc_string, test_strrchr_basic);
  tcase_add_test(tc_string, test_strrchr_not_found);
  tcase_add_test(tc_string, test_strrchr_null_byte);

  tcase_add_test(tc_string, test_strstr_basic);
  tcase_add_test(tc_string, test_strstr_not_found);
  tcase_add_test(tc_string, test_strstr_empty_needle);

  tcase_add_test(tc_string, test_strtok_basic);
  tcase_add_test(tc_string, test_strtok_multiple_delims);
  tcase_add_test(tc_string, test_strtok_no_delims);

  suite_add_tcase(s, tc_string);
  return s;
}

int main(void) {
  int failed_count = 0;
  Suite *s_sprintf = suite_s21_sprintf();
  Suite *s_string = suite_s21_string();
  SRunner *sr = srunner_create(s_sprintf);

  srunner_add_suite(sr, s_string);

  srunner_run_all(sr, CK_VERBOSE);

  failed_count = srunner_ntests_failed(sr);

  srunner_free(sr);

  return (failed_count == 0) ? 0 : 1;
}