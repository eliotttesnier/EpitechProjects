##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC =	src/lib/str_to_array.c			\
		src/lib/my_strlen.c				\
		src/lib/nb_elements_array.c		\
		src/lib/my_strcmp.c				\
		src/lib/my_strccmp.c			\
		src/lib/my_strcat.c       	  	\
		src/lib/my_strdup.c				\
		src/lib/my_perror.c				\
		src/lib/free_arr.c				\
		src/lib/print_outpout.c   		\
		src/lib/my_getnbr.c 			\
		src/func/exit.c					\
		src/func/cd.c					\
		src/func/env.c					\
		src/func/setenv.c				\
		src/func/unsetenv.c				\
		src/error_cases.c				\
		src/process.c					\
		src/minishell.c					\
		src/init_struct.c				\
		src/valid_redir.c				\
		src/remove_redirect.c			\
		src/open_file.c					\
		src/failed_exec.c				\
		src/perm_dir.c					\
		src/free_lcom.c					\
		src/execution.c					\
		src/check_redirections.c		\
		src/exec_simple_com.c

MAIN =	main.c

TEST_SRC =	tests/test.c

SRC_OBJ = $(SRC:.c=.o)

MAIN_OBJ =	$(MAIN:.c=.o)

TEST_OBJ = $(TEST_SRC:.c=.o)

NAME = mysh

TEST_NAME = unit_tests

INCLUDES = -I ./includes

LIBS =

CFLAGS = -Wextra -Wshadow -Werror

CC := gcc -o $(NAME)

.PHONY: all clean fclean re coverage tests_run tester code_line

all: $(NAME)

$(NAME): $(SRC_OBJ)	$(MAIN_OBJ)
	$(CC) $(MAIN_OBJ) $(SRC_OBJ) $(CFLAGS) $(INCLUDES)

clean:
		rm -f $(MAIN_OBJ)
		rm -f $(SRC_OBJ)
		rm -f $(TEST_OBJ)

fclean: clean
		rm -f $(NAME)
		rm -f $(TEST_NAME)
		rm -rf *.gcda
		rm -rf *.gcda

re: fclean all

coverage: tests_run
	gcovr
	$(MAKE) fclean

tests_run:	$(TEST_OBJ) $(SRC_OBJ) all
	gcc -o $(TEST_NAME) $(TEST_OBJ) $(SRC_OBJ) --coverage -lcriterion
	./$(TEST_NAME)

tester: all
	mv tests temp
	mv temp/tester/tests tests
	./temp/tester/tester.sh
	mv tests temp/tester/tests
	mv temp tests

code_line :
	find $(SRC) $(MAIN) -name '*.c' | xargs wc -l
