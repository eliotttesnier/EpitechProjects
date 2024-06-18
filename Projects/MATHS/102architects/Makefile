##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile
##

SRC	=	architect.c	\
		calculs.c	\
		error_cases.c

NAME	=	102architect

OBJ	=	$(SRC:.c=.o)

all:	$(OBJ)
	gcc -o $(NAME) $(OBJ) -lm

clean:
	rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re:	fclean all
