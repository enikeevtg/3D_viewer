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

SRC_DIR = ./src/
SRC = $(wildcard $(SRC_DIR)*.c)
OBJ_DIR = ./obj/
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

UNITS_DIR = ./units/
UNITS_SRC = $(wildcard $(UNITS_DIR)*.c)

TESTS_DIR = ./tests/
TESTS_SRC = $(wildcard $(TESTS_DIR)*.c)
TEST_EXE =


man:
	$(CC) $(CF) $(SRC)
	$(LEAKS)./a.out 17257_Booster_rocket_for_space_shuttle_v1_NEW.obj

# SERVICE
style:
	clang-format --style=google -n e_matrix.h $(SRC) $(UNITS_SRC) $(TESTS_SRC)

gost:
	clang-format --style=google -i e_matrix.h $(SRC) $(UNITS_SRC) $(TESTS_SRC)
