##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile
##

SRC	=	pong.c

NAME	=	101pong

OBJ	=	$(SRC:.c=.o)

all:	$(OBJ)
	gcc -o $(NAME) $(OBJ) -lm

clean:
	rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re:	fclean all
