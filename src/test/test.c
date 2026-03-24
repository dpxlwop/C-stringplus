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

START_TEST(test_null_string) {
  char result[MAX_STR_LEN];

  s21_sprintf(result, "%s", S21_NULL);

  ck_assert_str_eq(result, "(null)");
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

START_TEST(test_to_upper_basic) {
  char str[] = "Hello World!";
  char *result = s21_to_upper(str);
  ck_assert_ptr_eq(result, str);
  ck_assert_str_eq(str, "HELLO WORLD!");
}
END_TEST

START_TEST(test_to_upper_null) {
  char *result = s21_to_upper(S21_NULL);
  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

START_TEST(test_to_upper_no_change) {
  char str[] = "HELLO 123!";
  s21_to_upper(str);
  ck_assert_str_eq(str, "HELLO 123!");
}
END_TEST

START_TEST(test_to_lower_basic) {
  char str[] = "Hello World!";
  char *result = s21_to_lower(str);
  ck_assert_ptr_eq(result, str);
  ck_assert_str_eq(str, "hello world!");
}
END_TEST

START_TEST(test_to_lower_null) {
  char *result = s21_to_lower(S21_NULL);
  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

START_TEST(test_to_lower_no_change) {
  char str[] = "hello 123!";
  s21_to_lower(str);
  ck_assert_str_eq(str, "hello 123!");
}
END_TEST

START_TEST(test_insert_basic) {
  char *result = s21_insert("Hello!", " World", 5);
  ck_assert_str_eq(result, "Hello World!");
  free(result);
}
END_TEST

START_TEST(test_insert_begin) {
  char *result = s21_insert("World!", "Hello ", 0);
  ck_assert_str_eq(result, "Hello World!");
  free(result);
}
END_TEST

START_TEST(test_insert_end) {
  char *result = s21_insert("Hello", " World!", 5);
  ck_assert_str_eq(result, "Hello World!");
  free(result);
}
END_TEST

START_TEST(test_insert_null_src) {
  char *result = s21_insert(S21_NULL, "test", 0);
  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

START_TEST(test_insert_null_str) {
  char *result = s21_insert("test", S21_NULL, 0);
  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

START_TEST(test_insert_invalid_index) {
  char *result = s21_insert("test", "x", 10);
  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

START_TEST(test_insert_empty_strings) {
  char *result = s21_insert("", "", 0);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_basic) {
  char *result = s21_trim("###Hello World!!!", "#!");
  ck_assert_str_eq(result, "Hello World");
  free(result);
}
END_TEST

START_TEST(test_trim_null_src) {
  char *result = s21_trim(NULL, "abc");
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_trim_null_trim_chars) {
  char *result = s21_trim("hello", NULL);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_trim_empty_src) {
  char *result = s21_trim("", "abc");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_empty_trim_chars) {
  char *result = s21_trim("hello", "");
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_all_removed) {
  char *result = s21_trim("123", "123");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_internal_chars_unchanged) {
  char *result = s21_trim("123he1llo321", "123");
  ck_assert_str_eq(result, "he1llo");
  free(result);
}
END_TEST

START_TEST(test_trim_no_match) {
  char *result = s21_trim("hello", "xyz");
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_only_prefix) {
  char *result = s21_trim("123hello", "123");
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_only_suffix) {
  char *result = s21_trim("hello123", "123");
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_whitespace_like) {
  char *result = s21_trim(" \t\n hello \t\n ", " \t\n");
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_single_char) {
  char *result = s21_trim("aaahelloaaa", "a");
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_memchr_null_str) {
  ck_assert_ptr_eq(s21_memchr(NULL, 'x', 0), NULL);
}
END_TEST

START_TEST(test_memchr_zero_n) {
  char str[] = "hello";
  void *std = memchr(str, 'x', 0);
  void *s21 = s21_memchr(str, 'x', 0);
  ck_assert_ptr_eq(s21, std);
}
END_TEST

START_TEST(test_memcmp_zero_n) {
  int std = memcmp("abc", "def", 0);
  int s21 = s21_memcmp("abc", "def", 0);
  ck_assert_int_eq(s21, std);
}
END_TEST

START_TEST(test_memcpy_zero_n) {
  char src[] = "hello", dest1[10], dest2[10];
  void *std = memcpy(dest1, src, 0);
  void *s21 = s21_memcpy(dest2, src, 0);
  ck_assert_ptr_eq(s21, dest2);
  ck_assert_ptr_eq(std, dest1);
}
END_TEST

START_TEST(test_memset_zero_n) {
  char buf1[10] = {0}, buf2[10] = {0};
  memset(buf1, 'x', 0);
  s21_memset(buf2, 'x', 0);
  ck_assert_mem_eq(buf1, buf2, 10);
}
END_TEST

START_TEST(test_strncat_zero_n) {
  char d1[20] = "hello", d2[20] = "hello";
  strncat(d1, "world", 0);
  s21_strncat(d2, "world", 0);
  ck_assert_str_eq(d1, d2);
}
END_TEST

START_TEST(test_strncmp_zero_n) {
  int std = strncmp("abc", "def", 0);
  int s21 = s21_strncmp("abc", "def", 0);
  ck_assert_int_eq(s21, std);
}
END_TEST

START_TEST(test_strncpy_zero_n) {
  char d1[20] = "AAAAAAAAAAAAAAA";
  char d2[20] = "AAAAAAAAAAAAAAA";
  strncpy(d1, "hello", 0);
  s21_strncpy(d2, "hello", 0);
  ck_assert_mem_eq(d1, d2, 20);
}
END_TEST

START_TEST(test_strpbrk_no_match) {
  const char *std = strpbrk("hello", "xyz");
  const char *s21 = s21_strpbrk("hello", "xyz");
  ck_assert_ptr_eq((void *)s21, (void *)std);
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
  tcase_add_test(tc_core, test_null_string);

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

  tcase_add_test(tc_string, test_to_upper_basic);
  tcase_add_test(tc_string, test_to_upper_null);
  tcase_add_test(tc_string, test_to_upper_no_change);

  tcase_add_test(tc_string, test_to_lower_basic);
  tcase_add_test(tc_string, test_to_lower_null);
  tcase_add_test(tc_string, test_to_lower_no_change);

  tcase_add_test(tc_string, test_insert_basic);
  tcase_add_test(tc_string, test_insert_begin);
  tcase_add_test(tc_string, test_insert_end);
  tcase_add_test(tc_string, test_insert_null_src);
  tcase_add_test(tc_string, test_insert_null_str);
  tcase_add_test(tc_string, test_insert_invalid_index);
  tcase_add_test(tc_string, test_insert_empty_strings);

  tcase_add_test(tc_string, test_trim_basic);
  tcase_add_test(tc_string, test_trim_null_src);
  tcase_add_test(tc_string, test_trim_null_trim_chars);
  tcase_add_test(tc_string, test_trim_empty_src);
  tcase_add_test(tc_string, test_trim_empty_trim_chars);
  tcase_add_test(tc_string, test_trim_all_removed);
  tcase_add_test(tc_string, test_trim_internal_chars_unchanged);
  tcase_add_test(tc_string, test_trim_no_match);
  tcase_add_test(tc_string, test_trim_only_prefix);
  tcase_add_test(tc_string, test_trim_only_suffix);
  tcase_add_test(tc_string, test_trim_whitespace_like);
  tcase_add_test(tc_string, test_trim_single_char);

  tcase_add_test(tc_string, test_memchr_null_str);
  tcase_add_test(tc_string, test_memchr_zero_n);
  tcase_add_test(tc_string, test_memcmp_zero_n);
  tcase_add_test(tc_string, test_memcpy_zero_n);
  tcase_add_test(tc_string, test_memset_zero_n);
  tcase_add_test(tc_string, test_strncat_zero_n);
  tcase_add_test(tc_string, test_strncmp_zero_n);
  tcase_add_test(tc_string, test_strncpy_zero_n);
  tcase_add_test(tc_string, test_strpbrk_no_match);

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