##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

.PHONY: all clean fclean re coverage tests_run code_line

SRC =	lib/mini_printf.c				\
		lib/my_arrdup.c					\
		lib/my_arrlen.c					\
		lib/free_arr.c					\
		lib/my_getnbr.c					\
		lib/my_int_to_str.c				\
		lib/my_nbrlen.c					\
		lib/my_perror.c					\
		lib/my_putchar.c				\
		lib/my_putnbr.c					\
		lib/my_putstr.c					\
		lib/my_root.c					\
		lib/my_strcat.c					\
		lib/my_strcmp.c					\
		lib/my_strncmp.c				\
		lib/my_strdup.c					\
		lib/my_strcut.c					\
		lib/my_strlen.c					\
		lib/str_to_array.c				\
		lib/is_there_char.c				\
		src/corewar.c					\
		src/error_cases.c				\
		src/warrior_checking.c			\
		src/check_flags.c				\
		src/fill_prog.c					\
		src/update_id.c					\
		src/free_argument.c				\
		src/build_structure.c			\
		src/convert_to_binary.c			\
		src/endian_switch.c				\
		src/simulation_loop.c			\
		src/distrib_execution/short_read.c	\
		src/distrib_execution/int_read.c	\
		src/distrib_execution/calc_size.c	\
		src/distrib_execution/distrib_add.c	\
		src/distrib_execution/distrib_aff.c	\
		src/distrib_execution/distrib_and.c	\
		src/distrib_execution/distrib_fork.c	\
		src/distrib_execution/distrib_ld.c		\
		src/distrib_execution/distrib_ldi.c	\
		src/distrib_execution/distrib_lfork.c	\
		src/distrib_execution/distrib_live.c	\
		src/distrib_execution/distrib_lld.c	\
		src/distrib_execution/distrib_lldi.c	\
		src/distrib_execution/distrib_or.c		\
		src/distrib_execution/distrib_st.c		\
		src/distrib_execution/distrib_sti.c	\
		src/distrib_execution/distrib_sub.c	\
		src/distrib_execution/distrib_xor.c	\
		src/distrib_execution/distrib_zjmp.c	\
		src/exec_programs.c				\
		src/execution/execute_live.c	\
		src/execution/execute_ld.c		\
		src/execution/execute_st.c		\
		src/execution/execute_add.c		\
		src/execution/execute_sub.c		\
		src/execution/execute_and.c		\
		src/execution/execute_or.c		\
		src/execution/execute_xor.c		\
		src/execution/execute_zjmp.c	\
		src/execution/execute_ldi.c		\
		src/execution/execute_sti.c		\
		src/execution/execute_fork.c	\
		src/execution/execute_lld.c		\
		src/execution/execute_lldi.c	\
		src/execution/execute_lfork.c	\
		src/execution/execute_aff.c		\
		src/ncurse_display.c			\
		src/display_area_mem.c			\
		src/display_cw_winner.c			\
		src/display_cw_final.c			\
		src/intro_anim.c				\
		src/occurence.c					\
		op.c							\

MAIN	=	main.c

TEST_SRC	=	tests/test.c

SRC_OBJ	=	$(SRC:.c=.o)

MAIN_OBJ	=	$(MAIN:.c=.o)

TEST_OBJ	=	$(TEST_SRC:.c=.o)

NAME	=	corewar

TEST_NAME	=	unit_tests

INCLUDES	=	-I./include

LIBS	=

CFLAGS	=	-Wall -Wextra -Wshadow -Werror

CC	:=	gcc -o $(NAME) $(INCLUDES)

all: $(NAME)

$(NAME): $(SRC_OBJ)	$(MAIN_OBJ)
	$(CC) $(MAIN_OBJ) $(SRC_OBJ) -lm -l csfml-system -l csfml-audio -lncurses $(CFLAGS)

clean:
		rm -f $(MAIN_OBJ)
		rm -f $(SRC_OBJ)
		rm -f $(TEST_OBJ)

fclean: clean
		rm -f $(NAME)
		rm -f $(TEST_NAME)
		rm -rf *.gcno
		rm -rf *.gcda

re: fclean all

coverage: tests_run
	gcovr
	$(MAKE) fclean

tests_run:
	gcc -o $(TEST_NAME) $(TEST_SRC) $(SRC) $(INCLUDES) --coverage -lcriterion
	./$(TEST_NAME)

code_line :
	find $(SRC) $(MAIN) -name '*.c' | xargs wc -l
