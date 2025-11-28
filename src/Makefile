CFLAGS = -Wall -Werror -Wextra -std=c11 \
         -fprofile-arcs -ftest-coverage

LDFLAGS = -lgcov

GCOV_REPORT_DIR = cov_report

all: s21_string.a gcov_report

s21_string.a: clean
	gcc -c s21_sprintf.c s21_string.c
	ar rcs s21_string.a s21_sprintf.o s21_string.o
	rm *.o

test: clean
	gcc $(CFLAGS) s21_sprintf.c s21_string.c test/test.c -o test_s21_string -lcheck $(LDFLAGS)
	./test_s21_string
	mkdir -p $(GCOV_REPORT_DIR)
	lcov --capture --directory . --base-directory . --output-file $(GCOV_REPORT_DIR)/coverage.info --rc branch_coverage=1
	lcov --remove $(GCOV_REPORT_DIR)/coverage.info 'test/*' --output-file $(GCOV_REPORT_DIR)/coverage.info --rc branch_coverage=1

gcov_report: test
	genhtml $(GCOV_REPORT_DIR)/coverage.info --output-directory $(GCOV_REPORT_DIR) --rc branch_coverage=1
	open $(GCOV_REPORT_DIR)/index.html || xdg-open $(GCOV_REPORT_DIR)/index.html
	rm -f test_s21_string

clean:
	rm -f test_s21_string 
	find . -name "*.gcda" -delete
	find . -name "*.gcno" -delete
	find . -name "*.gcov" -delete
	rm -rf $(GCOV_REPORT_DIR) s21_sprintf.dSYM *.a *.o

rebuild: clean all

.PHONY: all clean rebuild test gcov_report s21_string.a