##
## EPITECH PROJECT, 2023
## makfile
## File description:
## is a makefile
##

SRC	=	fozzbazz.c

MAIN = main.c

OBJ	=	$(SRC:.c=.o)

NAME	=	fozzbazz

all:	$(NAME)

$(NAME):	$(OBJ)
		gcc -o $(NAME) $(MAIN) $(OBJ) -Wall -Wextra -Werror

clean:
		rm -rf $(OBJ)

fclean:
		rm -rf $(NAME)
		rm -rf $(OBJ)
		rm -f unit_tests
		rm -rf *.gcda
		rm -rf *.gcno

re:		fclean all
