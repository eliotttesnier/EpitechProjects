##
## EPITECH PROJECT, 2023
## makfile
## File description:
## is a makefile
##

SRC	=	mini_print/mini_printf.c	\
		mini_print/my_putchar.c	\
		mini_print/my_putnbr.c	\
		mini_print/my_putstr.c	\
		mini_print/my_strcpy.c  \
		mini_print/my_strlen.c  \
		mini_print/my_nbrlen.c	\
		mini_print/my_root.c	\
		secured_lib/hash_func.c	\
		secured_lib/create_hashtable.c	\
		secured_lib/delete_hashtable.c	\
		secured_lib/data_del_hashtable.c	\
		secured_lib/dump_hashtable.c	\
		secured_lib/insert_hashtable.c	\
		secured_lib/search_hashtable.c

MAIN = main.c

TEST = tests/test.c

OBJ	=	$(SRC:.c=.o)

NAME	=	libhashtable.a

all:	$(NAME)

$(NAME):	$(OBJ)
		ar rc $(NAME) $(OBJ)

clean:
		rm -rf $(OBJ)

fclean:
		rm -rf $(NAME)
		rm -rf $(OBJ)
		rm -f unit_tests
		rm -rf *.gcda
		rm -rf *.gcno

re:		fclean all

coverage: tests_run
	 --exclude myprintf
	rm -f unit_tests
	rm -rf *.gcda
	rm -rf *.gcno

tests_run:
	gcc -o unit_tests $(TEST) $(SRC) --coverage -lcriterion
	./unit_tests
