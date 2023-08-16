.PHONY: all lib test gcov gcov_report style gost clean
# UTILITIES
CC = gcc
AR = ar rs
RAN = ranlib
MK = mkdir -p
MAKE = make
RM = rm -rf
OS := $(shell uname)
ifeq ($(OS), Darwin)
	LEAKS = CK_FORK=no leaks --atExit -- 
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
APP = 3D_viewer_v1.app

SRC_DIR = ./src/

MODELS_DIR = ./models/

UI_DIR = $(SRC_DIR)01_ui/

MODEL_LOAD_DIR = $(SRC_DIR)02_model_loading/
MODEL_LOAD_SRC = $(wildcard $(MODEL_LOAD_DIR)*.c)

TESTS_DIR = $(SRC_DIR)08_tests/
TESTS_SRC = $(wildcard $(TESTS_DIR)*.c)
TEST_EXE =

BUILD_DIR = ./build/

# BUILD
all: clean install launch

# APP
install:
	$(MK) $(BUILD_DIR)
	cd $(BUILD_DIR) && qmake ../$(UI_DIR)3D_viewer_v1.pro && make -j6 && make clean && rm -rf .qmake.stash Makefile

launch:
	open $(BUILD_DIR)$(APP)

uninstall:
	$(RM) $(BUILD_DIR)*

app_leaks:
	$(LEAKS) $(BUILD_DIR)$(APP)/Contents/MacOS/3D_viewer_v1

#TESTS
man:
	$(CC) $(CF) main.c $(MODEL_LOAD_SRC)
#	$(LEAKS)./a.out $(MODELS_SRC)Energy_rocket.obj > geometry_info.txt
#	$(LEAKS)./a.out $(MODELS_SRC)Leon_kennedy.obj > geometry_info.txt
	$(LEAKS)./a.out $(MODELS_DIR)teddy.obj > geometry_info.txt

# SERVICE
style:
	clang-format --style=google -n $(SRC_DIR)*.h $(MODEL_LOAD_DIR)* $(UI_DIR)*.h $(UI_DIR)*.cpp $(TESTS_SRC)

gost:
	clang-format --style=google -i $(SRC_DIR)*.h $(MODEL_LOAD_DIR)* $(UI_DIR)*.h $(UI_DIR)*.cpp $(TESTS_SRC)

clean:
	@rm -rf *.out
