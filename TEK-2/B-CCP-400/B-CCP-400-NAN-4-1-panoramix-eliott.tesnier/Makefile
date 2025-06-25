##
## EPITECH PROJECT, 2024
## Rush 3
## File description:
## Makefile
##

.PHONY: all clean fclean re tests_run coverage functional_tests

# ANSI Colors
GREEN=\033[1;32m
BLUE=\033[1;34m
RED=\033[1;31m
YELLOW=\033[1;33m
NC=\033[0m

MAIN = src/main.c

MAIN_OBJ = $(MAIN:.c=.o)

SRC =	src/panoramix.c						\
		src/cleanup.c						\
		src/parsing/parse_arguments.c		\
		src/init/init_prog_state.c			\
		src/villager/villager_routine.c		\
		src/druid/druid_routine.c			\

OBJ = $(SRC:.c=.o)

TEST_SRC =	tests/unit/parsing.c			\
			tests/unit/cleanup.c			\
			tests/unit/loop.c				\

TEST_OBJ = $(TEST_SRC:.c=.o)

INCLUDES = -I./include

CFLAGS =	-Wall -Wextra -Werror -lpthread

LIBS =

NAME =	panoramix

CC = gcc

all: $(NAME)

$(NAME): $(OBJ) $(MAIN_OBJ)
	@echo -e "$(BLUE)ᒥ🔧ᒧ Compiling $(NAME)...$(NC)"
	$(CC) -o $(NAME) $(MAIN_OBJ) $(OBJ) $(CFLAGS) $(INCLUDES) $(LIBS)
	@echo -e "$(GREEN)ᒥ✅ᒧ Compilation completed successfully!$(NC)"

%.o: %.c
	@echo -e "$(YELLOW)ᒥ🚀ᒧ Compiling $<...$(NC)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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
	@rm -rf *.gcov
	@rm -rf vgcore.*
	@echo -e "$(GREEN)ᒥ✅ᒧ Full clean completed!$(NC)"

re: fclean all

coverage: tests_run
	@echo -e "$(BLUE)ᒥ📊ᒧ Generating coverage report...$(NC)"
	@gcovr --exclude tests/ --html --html-details -o coverage_report.html
	@firefox coverage_report.html &> /dev/null
	@echo -e "$(GREEN)ᒥ✅ᒧ Report generated!$(NC)"
	@rm -rf *.html *.css

tests_run: $(OBJ) $(TEST_OBJ)
	@echo -e "$(BLUE)ᒥ🧪ᒧ Compiling tests...$(NC)"
	@gcc -o unit_tests $(SRC) $(TEST_OBJ) $(CFLAGS) $(INCLUDES) \
		--coverage -lcriterion
	@echo -e "$(GREEN)ᒥ✅ᒧ Tests compiled! Running...$(NC)"
	@./unit_tests

functional_tests: $(NAME)
	@echo -e "$(BLUE)ᒥ🧪ᒧ Running functional tests...$(NC)"
	@python3 ./tests/functional/Tester.py
