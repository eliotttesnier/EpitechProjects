##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

.PHONY: all clean fclean re coverage tests_run code_line

SRC =	lib/mini_printf.c			\
		lib/my_arrdup.c				\
		lib/my_arrlen.c				\
		lib/free_arr.c				\
		lib/my_getnbr.c				\
		lib/my_int_to_str.c			\
		lib/my_nbrlen.c				\
		lib/my_perror.c				\
		lib/my_putchar.c			\
		lib/my_putnbr.c				\
		lib/my_putstr.c				\
		lib/my_root.c				\
		lib/my_strcat.c				\
		lib/my_strcmp.c				\
		lib/my_strncmp.c			\
		lib/my_strdup.c				\
		lib/my_strcut.c				\
		lib/my_strlen.c				\
		lib/str_to_array.c			\
		lib/my_pushback_to_arr.c	\
		src/amazed.c				\
		src/error_cases/nb_error.c	\
		src/error_cases/rooms_error.c	\
		src/rm_command.c				\
		src/error_cases/words_number.c	\
		src/error_cases/tunnels_error.c	\
		src/error_cases/remove_com.c	\
		src/error_cases/id_coords.c		\
		src/error_cases/unknown_tunnel.c\
		src/format_arr.c				\
		src/fill_mapstat.c				\
		src/del_in_array.c				\
		src/fill_pars.c					\

MAIN	=	main.c

TEST_SRC	=	tests/test.c

SRC_OBJ	=	$(SRC:.c=.o)

MAIN_OBJ	=	$(MAIN:.c=.o)

TEST_OBJ	=	$(TEST_SRC:.c=.o)

NAME	=	amazed

TEST_NAME	=	unit_tests

INCLUDES	=	-I./include

LIBS	=

CFLAGS	=	-Wall -Wextra -Wshadow -Werror

CC	:=	gcc -o $(NAME) $(INCLUDES)

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
