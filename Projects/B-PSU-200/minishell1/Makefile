##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC =	src/lib/str_to_array.c			\
		src/lib/str_to_array_space.c	\
		src/lib/my_strlen.c				\
		src/lib/nb_elements_array.c		\
		src/lib/my_strcmp.c				\
		src/lib/my_strccmp.c			\
		src/lib/my_strcat.c       	  	\
		src/lib/print_outpout.c   		\
		src/lib/my_getnbr.c 			\
		src/func/exit.c					\
		src/func/cd.c					\
		src/func/env.c					\
		src/func/setenv.c				\
		src/func/unsetenv.c				\
		src/error_cases.c				\
		src/process.c					\
		src/minishell.c

MAIN =	main.c

TEST_SRC =	tests/test.c

SRC_OBJ = $(SRC:.c=.o)

MAIN_OBJ =	$(MAIN:.c=.o)

TEST_OBJ = $(TEST_SRC:.c=.o)

NAME = mysh

TEST_NAME = unit_tests

INCLUDES = -I ./includes

LIBS =

CFLAGS = -Wextra -Wshadow -Werror

CC := gcc -o $(NAME)

.PHONY: all clean fclean re coverage tests_run

all: $(NAME)

$(NAME): $(SRC_OBJ)	$(MAIN_OBJ)
	$(CC) $(MAIN_OBJ) $(SRC_OBJ) $(CFLAGS) $(INCLUDES)

clean:
		rm -f $(MAIN_OBJ)
		rm -f $(SRC_OBJ)
		rm -f $(TEST_OBJ)

fclean: clean
		rm -f $(NAME)
		rm -f $(TEST_NAME)
		rm -rf *.gcda
		rm -rf *.gcda

re: fclean all

coverage: tests_run
	gcovr
	$(MAKE) fclean

tests_run:	$(TEST_OBJ) $(SRC_OBJ) all
	gcc -o $(TEST_NAME) $(TEST_OBJ) $(SRC_OBJ) --coverage -lcriterion
	./$(TEST_NAME)
