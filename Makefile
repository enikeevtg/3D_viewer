.PHONY: all lib test gcov gcov_report style gost clean
# UTILITIES
CC = gcc
AR = ar rs
RAN = ranlib
MK = mkdir -p
MAKE = make
OS := $(shell uname)
ifeq ($(OS), Darwin)
#	LEAKS = CK_FORK=no leaks --atExit -- 
	REPORT_OPEN = open
else ifeq ($(OS), Linux)
	LEAKS =
	REPORT_OPEN = xdg-open
endif

# UTILITIES OPTIONS
CF = -Wall -Werror -Wextra
STD = -std=c11 -pedantic
ASAN = -g -fsanitize=address
ifeq ($(OS), Darwin)
	TEST_FLAGS = -lcheck
else ifeq ($(OS), Linux)
	TEST_FLAGS = -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURCE
endif
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

# FILENAMES
TARGET =

MODEL_LOAD_DIR = ./02_model_loading/
MODEL_LOAD_SRC = $(wildcard $(MODEL_LOAD_DIR)*.c)

TESTS_DIR = ./08_tests/
TESTS_SRC = $(wildcard $(TESTS_DIR)*.c)
TEST_EXE =

MODELS_SRC = ./00_models/

man:
	$(CC) $(CF) main.c $(MODEL_LOAD_SRC)
#	$(LEAKS)./a.out $(MODELS_SRC)Energy_rocket.obj > geometry_info.txt
#	$(LEAKS)./a.out $(MODELS_SRC)Leon_kennedy.obj > geometry_info.txt
	$(LEAKS)./a.out $(MODELS_SRC)teddy.obj > geometry_info.txt

# SERVICE
style:
	clang-format --style=google -n $(SRC) $(UNITS_SRC) $(TESTS_SRC)

gost:
	clang-format --style=google -i $(SRC) $(UNITS_SRC) $(TESTS_SRC)

clean:
	@rm -rf *.out
