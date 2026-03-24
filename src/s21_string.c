#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  void *res = S21_NULL;
  for (s21_size_t i = 0; i < n; i++) {
    if (ptr[i] == (unsigned char)c) {
      res = (void *)(ptr + i);
      i = n + 1;
    }
  }
  return res;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  unsigned char *ptr1 = (unsigned char *)str1;
  unsigned char *ptr2 = (unsigned char *)str2;
  int res = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (ptr1[i] != ptr2[i]) {
      res = (int)ptr1[i] - (int)ptr2[i];
      i = n + 1;
    }
  }
  return res;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *to = (unsigned char *)dest;
  unsigned char *from = (unsigned char *)src;
  for (s21_size_t i = 0; i < n; i++) {
    to[i] = from[i];
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    ptr[i] = (unsigned char)c;
  }
  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  unsigned char *to = (unsigned char *)dest;
  unsigned char *from = (unsigned char *)src;
  s21_size_t len = s21_strlen(dest);
  s21_size_t j = 0;
  for (s21_size_t i = len; j < n && from[j] != '\0'; i++) {
    to[i] = from[j];
    j++;
  }
  to[len + j] = '\0';
  return dest;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  if (str != S21_NULL) {
    while (str[len] != '\0') {
      len++;
    }
  }
  return len;
}

char *s21_strchr(const char *str, int c) {
  int match = 0;

  do {
    if (*str == (char)c) {
      match = 1;
    }
  } while (!match && *str++ != '\0');

  return match ? (char *)str : S21_NULL;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  for (; n > 1 && *str1 != '\0' && *str1 == *str2; --n, ++str1, ++str2);

  return (n == 0) ? 0 : *str1 - *str2;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *temp_dest = dest;

  for (; n > 0 && *src != '\0'; n--, temp_dest++, src++) {
    *temp_dest = *src;
  }
  while (n-- > 0) {
    *temp_dest++ = '\0';
  }

  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t count = 0;
  int match = 0;

  for (; *str1 != '\0' && !match; ++str1) {
    for (const char *temp_str2 = str2; *temp_str2 != '\0' && !match;
         ++temp_str2) {
      if (*str1 == *temp_str2) {
        match = 1;
      }
    }
    if (!match) {
      ++count;
    }
  }

  return count;
}

#include "strerror_messages.h"

char *s21_strerror(int errnum) {
  static char buf[100];
  static const char *error_messages[] = ERROR_MESSAGES;

  s21_sprintf(buf, "Unknown error: %d", errnum);
  int max_size = (sizeof(error_messages) / sizeof(error_messages[0]) - 1);

  return (errnum < 0 || errnum > max_size || error_messages[errnum] == S21_NULL)
             ? buf
             : (char *)error_messages[errnum];
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;

  for (; *str1 != '\0' && !result; ++str1) {
    for (const char *temp_str2 = str2; *temp_str2 != '\0' && !result;
         ++temp_str2) {
      if (*str1 == *temp_str2) {
        result = (char *)str1;
      }
    }
  }

  return result;
}

char *s21_strrchr(const char *str, int c) {
  char *found_c = S21_NULL;
  do {
    if (*str == (char)c) {
      found_c = (char *)str;
    }
  } while (*str++ != '\0');

  return found_c;
}

char *s21_strstr(const char *haystack, const char *needle) {
  int needle_end = 0;

  do {
    const char *temp_haystack = haystack;
    const char *temp_needle = needle;

    while (*temp_needle != '\0' && *temp_haystack == *temp_needle) {
      temp_haystack++;
      temp_needle++;
    }

    if (*temp_needle == '\0') needle_end = 1;
  } while (!needle_end && *haystack++ != '\0');

  return needle_end ? (char *)haystack : S21_NULL;
}

static int is_delim(char ch, const char *delim) {
  int result = 0;

  while (*delim != '\0' && !result) {
    if (ch == *delim) {
      result = 1;
    }
    ++delim;
  }

  return result;
}

static void find_token_start(char **str, const char *delim) {
  while (**str != '\0' && is_delim(**str, delim)) {
    (*str)++;
  }
}

static void find_token_end(char **str, const char *delim) {
  while (**str != '\0' && !is_delim(**str, delim)) {
    (*str)++;
  }
}

char *s21_strtok(char *str, const char *delim) {
  static char *str_ptr = S21_NULL;
  if (str != S21_NULL) str_ptr = (char *)str;

  char *token_str_ptr = S21_NULL;

  if (str_ptr != S21_NULL && *str_ptr != '\0') {
    find_token_start(&str_ptr, delim);

    if (*str_ptr != '\0') {
      token_str_ptr = str_ptr;

      find_token_end(&str_ptr, delim);

      if (*str_ptr != '\0') {
        *str_ptr = '\0';
        str_ptr++;
      } else {
        str_ptr = S21_NULL;
      }
    }
  }

  return token_str_ptr;
}

char *s21_strcat(char *dest, const char *src) {
  char *temp_dest = dest;
  while (*temp_dest != '\0') temp_dest++;
  while ((*temp_dest++ = *src++) != '\0');
  return dest;
}

void *s21_to_upper(const char *str) {
  if (str == S21_NULL) return S21_NULL;
  char *temp_str = (char *)str;
  for (unsigned char *ptr = (unsigned char *)temp_str; *ptr != '\0'; ptr++) {
    if (*ptr >= 'a' && *ptr <= 'z') *ptr -= 'a' - 'A';
  }
  return temp_str;
}

void *s21_to_lower(const char *str) {
  if (str == S21_NULL) return S21_NULL;
  char *temp_str = (char *)str;
  for (unsigned char *ptr = (unsigned char *)temp_str; *ptr != '\0'; ptr++) {
    if (*ptr >= 'A' && *ptr <= 'Z') *ptr += 'a' - 'A';
  }
  return temp_str;
}

void *s21_insert(const char *src, const char *str, size_t start_index) {
  if (src == S21_NULL || str == S21_NULL || start_index > s21_strlen(src))
    return S21_NULL;
  char *result = malloc(s21_strlen(src) + s21_strlen(str) + 1);
  if (result == S21_NULL) return S21_NULL;
  s21_memcpy(result, src, start_index);
  s21_memcpy(result + start_index, str, s21_strlen(str));
  s21_memcpy(result + start_index + s21_strlen(str), src + start_index,
             s21_strlen(src) - start_index);
  return result;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == S21_NULL || trim_chars == S21_NULL) return S21_NULL;
  size_t len = s21_strlen(src), start = 0, end = len;
  while (start < len && s21_strchr(trim_chars, src[start])) start++;
  while (end > start && s21_strchr(trim_chars, src[end - 1])) end--;

  char *result = malloc(end - start + 1);
  if (!result) return S21_NULL;

  s21_memcpy(result, src + start, end - start);
  result[end - start] = '\0';
  return result;
}