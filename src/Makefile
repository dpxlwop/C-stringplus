CFLAGS = -Wall -Werror -Wextra -std=c11 -D_GNU_SOURCE

all: run

run: s21_sprintf
	./s21_sprintf

s21_sprintf: clean
	gcc $(CFLAGS) s21_sprintf.c -o s21_sprintf


clean:
	rm -f s21_sprintf

rebuild: clean all

.PHONY: all clean rebuild s21_sprintf