##
## EPITECH PROJECT, 2024
## NAVY
## File description:
## Makefile
##

SRC	=	mini_printf_lib/mini_printf.c	\
		mini_printf_lib/my_getnbr.c		\
		mini_printf_lib/my_nbrlen.c		\
		mini_printf_lib/my_power.c		\
		mini_printf_lib/my_putchar.c	\
		mini_printf_lib/my_putnbr.c		\
		mini_printf_lib/my_putstr.c		\
		mini_printf_lib/my_root.c		\
		mini_printf_lib/my_strcpy.c		\
		mini_printf_lib/my_strlen.c		\
		error_cases/hub_error.c			\
		error_cases/argv_error.c		\
		error_cases/check_file.c		\
		navy_lib/display.c				\
		navy_lib/sig_handler.c			\
		navy_lib/connect_process.c		\
		navy_lib/check_impact.c			\
		navy_lib/check_input.c			\
		navy_lib/send_coords.c			\
		navy_lib/check_win.c			\
		navy_lib/create_maps.c

MAIN	=	navy_lib/navy.c

TEST	=	tests/test.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_navy

all:	$(NAME)

$(NAME):	$(OBJ)
		gcc -o $(NAME) $(OBJ) $(MAIN)

unit_tests:	fclean	all
	gcc -o unit_tests $(TEST) $(SRC)	\
	--coverage -lcriterion

tests_run:	unit_tests
	clear
	./unit_tests

coverage:	tests_run
	gcovr

clean:
		rm -rf $(OBJ)

fclean:	clean
		rm -rf $(NAME)
		rm -rf unit_tests
		rm -rf *.gcda
		rm -rf *.gcno

re:	fclean	all
