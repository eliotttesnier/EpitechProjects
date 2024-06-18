##
## EPITECH PROJECT, 2024
## my_paint
## File description:
## Makefile
##

.PHONY: all clean fclean re coverage code_line

SRC =	lib/my_strcat.c				\
		lib/my_nbrlen.c				\
		lib/my_int_to_str.c			\
		lib/my_strlen.c				\
		lib/my_strcmp.c				\
		lib/my_strcut.c				\
		jingle.c					\
		create_button.c				\
		create_file_button.c		\
		create_help_button.c		\
		create_edition_button.c		\
		create_menu_bar.c			\
		set_menubar_position.c		\
		display_menu_bar.c			\
		display_cursor.c			\
		analyse_events.c			\
		actualise_states.c			\
		mouse_event.c				\
		check_sliders.c				\
		move_sliders.c				\
		create_workspace.c			\
		display_workspace.c			\
		set_workspace_position.c	\
		draw_circle.c				\
		check_hover.c				\
		destroy_paint.c				\
		do_all_actions.c			\
		is_on_or_under.c			\
		open_action.c				\
		check_canva.c				\
		actualise_imagess.c			\
		swap_layers.c				\
		use_tool.c					\
		save_action.c				\
		simple_save.c				\
		pixbutton.c					\
		fill.c						\
		replace_rectangle.c

MAIN =	my_paint.c

OBJ = $(SRC:.c=.o)

OBJ_MAIN = $(MAIN:.c=.o)

NAME =	my_paint

LIBS =	-l csfml-graphics -l csfml-window -l csfml-system -lm

CFLAGS = -Wextra -Wall -Wshadow

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_MAIN)
	gcc -o $(NAME) $(OBJ_MAIN) $(OBJ) $(LIBS)

clean:
		rm -rf $(OBJ)
		rm -rf $(OBJ_MAIN)

fclean: clean
		rm -rf $(NAME)
		rm -rf *.gcno
		rm -rf *.gcda

re: fclean all

coverage: test_run
		gcovr

test_run: $(OBJ)
		gcc -o unit_tests $(OBJ) --coverage --lcriterion
		./unit_tests

code_line :
	find $(SRC) $(MAIN) -name '*.c' | xargs wc -l
