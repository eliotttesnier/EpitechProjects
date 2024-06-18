##
## EPITECH PROJECT, 2023
## makfile
## File description:
## is a makefile
##

SRC	=	filling_structs/filling_ducks.c	\
		filling_structs/filling_var.c	\
		filling_structs/fill_text.c	\
		filling_structs/filling_sounds.c	\
		filling_structs/fill_menu.c	\
		main.c	\
		event.c	\
		sounds/sounds.c	\
		sounds/sounds2.c	\
		animations.c	\
		moving_ducks.c	\
		checks/check_shots.c	\
		checks/check_on_button.c	\
		anim_button.c	\
		readme.c	\
		actualise_texts.c	\
		destroy.c	\
		mylib/my_len_nbr.c	\
		mylib/my_compute_power_rec.c	\
		mylib/my_strlen.c	\
		mylib/my_getnbr.c	\
		saves.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_hunter

all:	$(NAME)

$(NAME):	$(OBJ)
		gcc -o $(NAME) $(OBJ) -l csfml-graphics -l csfml-window \
		-l csfml-system -l csfml-audio

clean:
		rm -rf $(OBJ)

fclean:
		rm -rf $(NAME)
		rm -rf $(OBJ)

re:		fclean all
