##
## EPITECH PROJECT, 2023
## makefile
## File description:
## 103cipher
##

SRC	=	103cipher.c	\
		encrypt.c	\
		display.c	\
		decrypt.c

NAME	=	103cipher

OBJ	=	$(SRC:.c=.o)

all:	$(OBJ)
	gcc -o $(NAME) $(OBJ) -lm

clean:
	rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re:	fclean all
