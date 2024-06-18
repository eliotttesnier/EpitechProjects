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
		inputs/up.c	\
		inputs/down.c	\
		inputs/right.c	\
		inputs/left.c	\
		my_sokoban.c	\
		get_map.c	\
		get_ocases.c	\
		find_player.c	\
		actualise_o.c	\
		check_stuck.c	\
		readme.c	\
		error_cases.c	\
		check_term_size.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_sokoban

all:	$(NAME)

$(NAME):	$(OBJ) $(MAIN_OBJ)
		gcc -o $(NAME) $(OBJ) -lncurses

clean:
		rm -rf $(OBJ) $(MAIN_OBJ)

fclean:
		rm -rf $(NAME)
		rm -rf $(OBJ) $(MAIN_OBJ)

re:		fclean all
