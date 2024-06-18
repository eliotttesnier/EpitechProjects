##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

.PHONY: all clean fclean re coverage tests_run

SRC =	lib/mini_printf.c			\
		lib/my_arrcpy.c				\
		lib/my_arrlen.c				\
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
		lib/my_strcpy.c				\
		lib/my_strcut.c				\
		lib/my_strlen.c				\
		lib/str_to_array.c			\
		init_corfile.c				\
		open_asm.c					\
		get_asmfile_in_arr.c		\
		format_arr.c				\
		check_compilation_error.c	\
		check_labels.c				\
		organize_for_compilation.c	\
		setup_header_struct.c		\
		setup_body_struct.c			\
		fill_labeled.c				\
		calc_codingbyte.c			\
		multiple_label.c			\
		little_to_big.c				\
		write_body.c				\
		op.c

MAIN	=	main.c

TEST_SRC	=	tests/test.c

SRC_OBJ	=	$(SRC:.c=.o)

MAIN_OBJ	=	$(MAIN:.c=.o)

TEST_OBJ	=	$(TEST_SRC:.c=.o)

NAME	=	asm

TEST_NAME	=	unit_tests

INCLUDES	=	-I./include

LIBS	=

CFLAGS	=	-Wall -Wextra -Wshadow

CC	:=	gcc -o $(NAME)

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

re: fclean all

coverage: tests_run
	gcovr
	$(MAKE) fclean

tests_run:	$(TEST_OBJ) $(SRC_OBJ)
	gcc -o $(TEST_NAME) $(TEST_OBJ) $(SRC_OBJ) --coverage -lcriterion
	./$(TEST_NAME)
