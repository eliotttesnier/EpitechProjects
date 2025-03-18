##
## EPITECH PROJECT, 2024
## NTS
## File description:
## Makefile
##

.PHONY: all clean fclean re coverage tests_run functionnal_tests

# Couleurs ANSI
GREEN=\033[1;32m
BLUE=\033[1;34m
RED=\033[1;31m
YELLOW=\033[1;33m
NC=\033[0m

MAIN_SRC = main.cpp

SRC	=	src/AComponent.cpp					\
		src/Factory.cpp						\
		src/core/Circuit.cpp				\
		src/core/Parser.cpp					\
		src/core/Simulator.cpp				\
		src/components/special/Input.cpp	\
		src/components/special/Output.cpp	\
		src/components/special/True.cpp		\
		src/components/special/False.cpp	\
		src/components/special/Clock.cpp	\
		src/components/elementary/And.cpp	\
		src/components/elementary/Or.cpp	\
		src/components/elementary/Xor.cpp	\
		src/components/elementary/Not.cpp	\
		src/components/gates/4001.cpp		\
		src/components/gates/4011.cpp		\
		src/components/gates/4030.cpp		\
		src/components/gates/4069.cpp		\
		src/components/gates/4071.cpp		\
		src/components/gates/4081.cpp		\
		src/components/advanced/4008.cpp	\
		src/components/advanced/4013.cpp	\
		src/components/advanced/4017.cpp	\
		src/components/advanced/4040.cpp	\
		src/components/advanced/4094.cpp	\
		src/components/advanced/4512.cpp	\
		src/components/advanced/4514.cpp	\
		src/components/advanced/4801.cpp	\
		src/components/advanced/2716.cpp	\
		src/components/advanced/Logger.cpp	\

MAIN_OBJ = $(MAIN_SRC:.cpp=.o)

OBJ = $(SRC:.cpp=.o)

TEST_SRC =	tests/unit/Parser/tests_parser.cpp		\
			tests/unit/Factory/tests_factory.cpp	\
			tests/unit/Error/tests_error.cpp		\
			tests/unit/Core/tests_circuit.cpp		\
			tests/unit/Core/tests_simulator.cpp		\
			tests/unit/tests_acomponent.cpp			\
			tests/unit/Special/tests_clock.cpp		\
			tests/unit/Special/tests_false.cpp		\
			tests/unit/Special/tests_true.cpp		\
			tests/unit/Special/tests_input.cpp		\
			tests/unit/Special/tests_output.cpp		\
			tests/unit/Elementary/tests_and.cpp		\
			tests/unit/Elementary/tests_not.cpp		\
			tests/unit/Elementary/tests_or.cpp		\
			tests/unit/Elementary/tests_xor.cpp		\
			tests/unit/Gates/tests_4001.cpp			\
			tests/unit/Gates/tests_4011.cpp			\
			tests/unit/Gates/tests_4030.cpp			\
			tests/unit/Gates/tests_4069.cpp			\
			tests/unit/Gates/tests_4071.cpp			\
			tests/unit/Gates/tests_4081.cpp			\
			tests/unit/Advanced/tests_2716.cpp		\
			tests/unit/Advanced/tests_4008.cpp		\
			tests/unit/Advanced/tests_4013.cpp		\
			tests/unit/Advanced/tests_4017.cpp		\
			tests/unit/Advanced/tests_4040.cpp		\
			tests/unit/Advanced/tests_4094.cpp		\
			tests/unit/Advanced/tests_4512.cpp		\
			tests/unit/Advanced/tests_4514.cpp		\
			tests/unit/Advanced/tests_4801.cpp		\
			tests/unit/Advanced/tests_logger.cpp	\

TEST_OBJ = $(TEST_SRC:.cpp=.o)

INCLUDES = -I./src/ -I./src/core/ -I./src/error/ \
			-I./src/components/ -I./src/components/special/ \
			-I./src/components/elementary/ -I./src/components/gates/ \
			-I./src/components/advanced/

CFLAGS =	-std=c++20 -Wall -Wextra -Werror

NAME =  nanotekspice

CC = g++

all: $(NAME)

$(NAME): $(OBJ) $(MAIN_OBJ)
	@echo -e "$(BLUE)ᒥ🔧ᒧ Compiling $(NAME)...$(NC)"
	@$(CC) -o $(NAME) $(MAIN_OBJ) $(OBJ) $(CFLAGS) $(INCLUDES)
	@echo -e "$(GREEN)ᒥ✅ᒧ Compilation successful!$(NC)"

%.o: %.cpp
	@echo -e "$(YELLOW)ᒥ🚀ᒧ Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo -e "$(RED)ᒥ🔥ᒧ Removing object files...$(NC)"
	@rm -rf $(OBJ)
	@rm -rf $(MAIN_OBJ)
	@rm -rf $(TEST_OBJ)
	@echo -e "$(GREEN)ᒥ✅ᒧ Clean complete!$(NC)"

fclean: clean
	@echo -e "$(RED)ᒥ🔥ᒧ Removing $(NAME)...$(NC)"
	@rm -rf $(NAME)
	@rm -rf unit_tests
	@rm -rf *.gcno
	@rm -rf *.gcda
	@rm -rf vgcore.*
	@echo -e "$(GREEN)ᒥ✅ᒧ Full clean complete!$(NC)"

re: fclean all

coverage: tests_run
	@echo -e "$(BLUE)ᒥ📊ᒧ Generating coverage report...$(NC)"
	@gcovr --exclude tests/
	@echo -e "$(GREEN)ᒥ✅ᒧ Report generated!$(NC)"

tests_run: $(OBJ) $(TEST_OBJ)
	@echo -e "$(BLUE)ᒥ🧪ᒧ Compiling tests...$(NC)"
	@g++ -o unit_tests $(SRC) $(TEST_OBJ) $(CFLAGS) $(INCLUDES) \
		--coverage -lcriterion
	@echo -e "$(GREEN)ᒥ✅ᒧ Tests compiled! Running...$(NC)"
	@./unit_tests

functionnal_tests: all
	@echo -e "$(BLUE)ᒥ🧪ᒧ Running functional tests...$(NC)"
	@python3 ./tests/functionnal_tests/Tester.py
