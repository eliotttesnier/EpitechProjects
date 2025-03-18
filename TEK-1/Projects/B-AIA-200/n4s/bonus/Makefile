##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

.PHONY: all clean fclean re coverage tests_run code_line

SRC =	str_to_array.c	\
		commands.c		\
		output.c

MAIN	=	main.c

TEST_SRC	=	tests/test.c

SRC_OBJ	=	$(SRC:.c=.o)

MAIN_OBJ	=	$(MAIN:.c=.o)

TEST_OBJ	=	$(TEST_SRC:.c=.o)

NAME	=	ai

TEST_NAME	=	unit_tests

INCLUDES	=	-I./include

LIBS	= -l csfml-graphics -l csfml-window -l csfml-system -l csfml-audio

CFLAGS	=	-Wall -Wextra -Wshadow -Werror

CC	:=	gcc -o $(NAME) $(INCLUDES)

all: $(NAME)

$(NAME): $(SRC_OBJ)	$(MAIN_OBJ)
	$(CC) $(MAIN_OBJ) $(SRC_OBJ) $(CFLAGS) $(LIBS)

clean:
		rm -f $(MAIN_OBJ)
		rm -f $(SRC_OBJ)
		rm -f $(TEST_OBJ)

fclean: clean
		rm -f $(NAME)
		rm -f $(TEST_NAME)
		rm -rf *.gcno
		rm -rf *.gcda

re: fclean all

coverage: tests_run
	gcovr
	$(MAKE) fclean

tests_run:
	gcc -o $(TEST_NAME) $(TEST_SRC) $(SRC) $(INCLUDES) --coverage -lcriterion
	./$(TEST_NAME)

code_line :
	find $(SRC) $(MAIN) -name '*.c' | xargs wc -l
