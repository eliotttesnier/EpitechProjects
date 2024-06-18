##
## EPITECH PROJECT, 2023
## makfile
## File description:
## is a makefile
##

SRC	=	myprintf/lib_printf/call/call_binary_down.c	\
		myprintf/lib_printf/call/call_binary_up.c	\
		myprintf/lib_printf/call/call_hexa_down.c	\
		myprintf/lib_printf/call/call_hexa_up.c	\
		myprintf/lib_printf/call/call_octal.c	\
		myprintf/lib_printf/call/call_put_adress.c	\
		myprintf/lib_printf/call/call_put_base.c	\
		myprintf/lib_printf/call/call_putchar.c	\
		myprintf/lib_printf/call/call_put_dot.c	\
		myprintf/lib_printf/call/call_put_float.c	\
		myprintf/lib_printf/call/call_put_g.c	\
		myprintf/lib_printf/call/call_put_in_var.c	\
		myprintf/lib_printf/call/call_put_nbr.c	\
		myprintf/lib_printf/call/call_putstr.c	\
		myprintf/lib_printf/call/call_put_unsigned.c	\
		myprintf/lib_printf/call/call_put_scientif.c	\
		myprintf/lib_printf/len/my_len_binary.c	\
		myprintf/lib_printf/len/my_len_float.c	\
		myprintf/lib_printf/len/my_len_hexa.c	\
		myprintf/lib_printf/len/my_len_nbr.c	\
		myprintf/lib_printf/len/my_len_octal.c	\
		myprintf/lib_printf/len/my_len_scientific.c	\
		myprintf/lib_printf/len/my_len_str.c	\
		myprintf/lib_printf/len/my_len_unsigned.c	\
		myprintf/lib_printf/my/my_compute_power_rec.c	\
		myprintf/lib_printf/my/my_getnbr.c	\
		myprintf/lib_printf/my/my_g_float.c	\
		myprintf/lib_printf/my/my_put_binary.c	\
		myprintf/lib_printf/my/my_putchar.c	\
		myprintf/lib_printf/my/my_put_float.c	\
		myprintf/lib_printf/my/my_put_g.c	\
		myprintf/lib_printf/my/my_put_hexa.c	\
		myprintf/lib_printf/my/my_put_nbr.c	\
		myprintf/lib_printf/my/my_put_octal.c	\
		myprintf/lib_printf/my/my_put_scientific.c	\
		myprintf/lib_printf/my/my_putstr.c	\
		myprintf/lib_printf/my/my_put_unsigned.c	\
		myprintf/lib_printf/my/my_strlen.c	\
		myprintf/my_printf.c	\
		my_strcpy.c	\
		organized.c	\
		add.c	\
		del.c	\
		disp.c	\
		sort.c	\
		swap.c	\
		sort/id.c	\
		sort/type.c	\
		sort/name.c	\
		sort/multiple_comp.c

MAIN =	main.c

TEST =	tests/add_test.c	\
		tests/del_test.c	\
		tests/disp_test.c	\
		tests/sort_test.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	organized

all:	$(NAME)

$(NAME):	$(OBJ)
		gcc -o $(NAME) $(MAIN) $(OBJ) libshell/libshell.a \
		-Wall -Wextra -Werror

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)
		rm -f unit_tests
		rm -rf *.gcda
		rm -rf *.gcno

re:		fclean all

unit_tests:	fclean all
	gcc -o unit_tests $(TEST) $(SRC) libshell/libshell.a \
	--coverage -lcriterion

coverage: tests_run
	gcovr --exclude myprintf --exclude organized.c
	rm -f unit_tests
	rm -rf *.gcda
	rm -rf *.gcno

tests_run:	unit_tests
	clear
	./unit_tests
