##
## EPITECH PROJECT, 2024
## Rush 3
## File description:
## Makefile
##

.PHONY: all clean fclean re coverage tests_run functional_tests

# ANSI Colors
GREEN=\033[1;32m
BLUE=\033[1;34m
RED=\033[1;31m
YELLOW=\033[1;33m
NC=\033[0m

MAIN = src/main.c

MAIN_OBJ = $(MAIN:.c=.o)

SRC =	src/error.c						\
		src/signals.c					\
		src/server.c					\
		src/socket_manager.c			\
		src/running.c					\
		src/client_handler.c			\
		src/utils/paths.c				\
		src/utils/normalize.c			\
		src/utils/abs.c					\
		src/utils/access.c				\
		src/commands_handling.c			\
		src/commands/quit.c				\
		src/commands/help.c				\
		src/commands/noop.c				\
		src/commands/user.c				\
		src/commands/pass.c				\
		src/commands/pwd.c				\
		src/commands/cwd.c				\
		src/commands/cdup.c				\
		src/commands/dele.c				\
		src/commands/pasv.c				\
		src/commands/port.c				\
		src/commands/retr.c				\
		src/commands/stor.c				\
		src/commands/list.c				\
		src/commands/mkd.c				\
		src/commands/rmd.c				\
		src/commands/rnfr.c				\
		src/commands/rnto.c				\
		src/commands/cpfr.c				\
		src/commands/cpto.c				\
		src/commands/size.c				\
		src/commands/mdtm.c				\

OBJ = $(SRC:.c=.o)

TEST_SRC =  tests/tests_utils.c			\
			tests/tests_server.c		\
			tests/tests_user.c			\
			tests/tests_pass.c			\
			tests/tests_noop.c			\
			tests/tests_help.c			\
			tests/tests_quit.c			\
			tests/tests_pwd.c			\
			tests/tests_cwd.c			\
			tests/tests_cdup.c			\
			tests/tests_dele.c			\

TEST_OBJ = $(TEST_SRC:.c=.o)

INCLUDES = -I./include

CFLAGS =	-Wall -Wextra -Werror

LIBS =

NAME =  myftp

CC = gcc

all: $(NAME)

$(NAME): $(OBJ) $(MAIN_OBJ)
	@echo -e "$(BLUE)ᒥ🔧ᒧ Compiling $(NAME)...$(NC)"
	@$(CC) -o $(NAME) $(MAIN_OBJ) $(OBJ) $(CFLAGS) $(INCLUDES) $(LIBS)
	@echo -e "$(GREEN)ᒥ✅ᒧ Compilation completed successfully!$(NC)"

%.o: %.c
	@echo -e "$(YELLOW)ᒥ🚀ᒧ Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo -e "$(RED)ᒥ🔥ᒧ Removing object files...$(NC)"
	@rm -rf $(OBJ)
	@rm -rf $(MAIN_OBJ)
	@echo -e "$(GREEN)ᒥ✅ᒧ Clean completed!$(NC)"

fclean: clean
	@echo -e "$(RED)ᒥ🔥ᒧ Removing $(NAME)...$(NC)"
	@rm -rf $(NAME)
	@rm -rf unit_tests
	@rm -rf *.gcno
	@rm -rf *.gcda
	@rm -rf vgcore.*
	@echo -e "$(GREEN)ᒥ✅ᒧ Full clean completed!$(NC)"

re: fclean all

coverage: tests_run
	@echo -e "$(BLUE)ᒥ📊ᒧ Generating coverage report...$(NC)"
	@gcovr
	@echo -e "$(GREEN)ᒥ✅ᒧ Report generated!$(NC)"

tests_run: $(OBJ) $(TEST_OBJ)
	@echo -e "$(BLUE)ᒥ🧪ᒧ Compiling tests...$(NC)"
	@gcc -o unit_tests $(SRC) $(TEST_OBJ) $(CFLAGS) $(INCLUDES) \
		--coverage -lcriterion
	@echo -e "$(GREEN)ᒥ✅ᒧ Tests compiled! Running...$(NC)"
	@./unit_tests

functional_tests: $(NAME)
	@echo -e "$(BLUE)ᒥ🧪ᒧ Running functional tests...$(NC)"
	@python3 ./tests/functional/Tester.py
