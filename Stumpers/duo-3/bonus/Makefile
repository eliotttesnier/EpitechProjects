##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC =	src/error_cases.c	\
	src/get_word.c		\
	src/find_word.c		\
	src/too_many_words.c	\

MAIN =	src/main.c

TEST_SRC =	tests/test.c

SRC_OBJ = $(SRC:.c=.o)

MAIN_OBJ =	$(MAIN:.c=.o)

TEST_OBJ = $(TEST_SRC:.c=.o)

NAME = hangman

TEST_NAME = unit_tests

INCLUDES = -I ./include/

LIBS =

CFLAGS = -Wall -Wextra -Wshadow -Werror -g $(INCLUDES)

CC := gcc -o $(NAME)

.PHONY: all clean fclean re coverage tests_run

all: $(NAME)

$(NAME): $(SRC_OBJ)	$(MAIN_OBJ)
	$(CC) $(MAIN_OBJ) $(SRC_OBJ) $(CFLAGS)

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

tests_run:
	gcc -o $(TEST_NAME) $(TEST_SRC) $(SRC) --coverage -lcriterion
	./$(TEST_NAME)
