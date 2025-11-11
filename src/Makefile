CFLAGS = -Wall -Werror -Wextra -std=c11 -D_GNU_SOURCE \
         -fprofile-arcs -ftest-coverage

LDFLAGS = -lgcov

GCOV_REPORT_DIR = cov_report

all: test

test: clean
	gcc $(CFLAGS) s21_sprintf.c test/test.c -o test_s21_sprintf -lcheck $(LDFLAGS)
	./test_s21_sprintf
	mkdir -p $(GCOV_REPORT_DIR)
	lcov --capture --directory . --base-directory . --output-file $(GCOV_REPORT_DIR)/coverage.info --rc branch_coverage=1
	lcov --remove $(GCOV_REPORT_DIR)/coverage.info 'test/*' --output-file $(GCOV_REPORT_DIR)/coverage.info --rc branch_coverage=1
	genhtml $(GCOV_REPORT_DIR)/coverage.info --output-directory $(GCOV_REPORT_DIR) --rc branch_coverage=1
	open $(GCOV_REPORT_DIR)/index.html || xdg-open $(GCOV_REPORT_DIR)/index.html
	rm -f test_s21_sprintf

clean:
	rm -f test_s21_sprintf s21_sprintf
	find . -name "*.gcda" -delete
	find . -name "*.gcno" -delete
	find . -name "*.gcov" -delete
	rm -rf $(GCOV_REPORT_DIR)

rebuild: clean all

build: clean
	gcc -Wall -Wextra -Werror -std=c11 s21_sprintf.c -o s21_sprintf

.PHONY: all clean rebuild test