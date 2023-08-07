CC = gcc
LEAKS =# leaks -atExit -- 

CF = -Wall -Werror -Wextra

SRC_DIR = ./src/

man:
	$(CC) $(CF) $(SRC_DIR)main.c
	$(LEAKS)./a.out 17257_Booster_rocket_for_space_shuttle_v1_NEW.obj
