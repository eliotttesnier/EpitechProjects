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

MAIN = src/main.cpp

MAIN_OBJ = $(MAIN:.cpp=.o)

SRC =	src/Config/Config.cpp \
		src/Kitchen/Kitchen.cpp \
		src/Kitchen/IngredientStock.cpp \
		src/Pizza/Pizza.cpp \
		src/Reception/Reception.cpp \
		src/Kitchen/ThreadPool.cpp \
		src/Kitchen/Cook.cpp \
		src/IPC/FifoIPCChannel.cpp \
		src/Utils/Logger.cpp \
		src/Process/Process.cpp \
		src/Process/KitchenProcess.cpp \

OBJ = $(SRC:.cpp=.o)

TEST_SRC = tests/unit/main_test.cpp \
		   tests/unit/Config_test.cpp \
		   tests/unit/Exception_test.cpp \
		   tests/unit/Reception_test.cpp \
		   tests/unit/ThreadPool_test.cpp \
		   tests/unit/OrderData_test.cpp \
		   tests/unit/Cook_test.cpp \
		   tests/unit/FifoIPCChannel_test.cpp \
		   tests/unit/IngredientStock_test.cpp \
		   tests/unit/KitchenThreadSafety_test.cpp \
		   tests/unit/IPCOperators_test.cpp \
		   tests/unit/Process_test.cpp

TEST_OBJ = $(TEST_SRC:.cpp=.o)

INCLUDES = -I./src

CFLAGS =	-std=c++20 -Wall -Wextra -Werror
CFLAGS_COVERAGE = $(CFLAGS) --coverage -fprofile-arcs -ftest-coverage

LIBS =

NAME =	plazza

UNIT_TESTS = unit_tests

CC = g++

all: $(NAME)

$(NAME): $(OBJ) $(MAIN_OBJ)
	@echo -e "$(BLUE)ᒥ🔧ᒧ Compiling $(NAME)...$(NC)"
	$(CC) -o $(NAME) $(MAIN_OBJ) $(OBJ) $(CFLAGS) $(INCLUDES) $(LIBS)
	@echo -e "$(GREEN)ᒥ✅ᒧ Compilation completed successfully!$(NC)"

%.o: %.cpp
	@echo -e "$(YELLOW)ᒥ🚀ᒧ Compiling $<...$(NC)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo -e "$(RED)ᒥ🔥ᒧ Removing object files...$(NC)"
	@rm -rf $(OBJ)
	@rm -rf $(MAIN_OBJ)
	@rm -rf $(TEST_OBJ)
	@echo -e "$(GREEN)ᒥ✅ᒧ Clean completed!$(NC)"

fclean: clean
	@echo -e "$(RED)ᒥ🔥ᒧ Removing $(NAME)...$(NC)"
	@rm -rf $(NAME)
	@rm -rf $(UNIT_TESTS)
	@rm -rf *.gcno
	@rm -rf *.gcda
	@rm -rf *.gcov
	@rm -rf vgcore.*
	@rm -rf coverage_report.html
	@rm -rf coverage_report/
	@echo -e "$(GREEN)ᒥ✅ᒧ Full clean completed!$(NC)"

re: fclean all

coverage: tests_run
	@echo -e "$(BLUE)ᒥ📊ᒧ Generating coverage report...$(NC)"
	@mkdir -p coverage_report
	@gcovr --root . --exclude tests/ --exclude-unreachable-branches \
	--html --html-details -o coverage_report/index.html
	@echo -e "$(GREEN)ᒥ✅ᒧ Report generated in coverage_report/index.html$(NC)"
	@firefox coverage_report/index.html &> /dev/null || xdg-open \
		coverage_report/index.html &> /dev/null || echo "Please open \
		coverage_report/index.html in your browser"

tests_run: $(SRC) $(TEST_SRC)
	@echo -e "$(BLUE)ᒥ🧪ᒧ Compiling Google Test unit tests...$(NC)"
	$(CC) -o $(UNIT_TESTS) $(SRC) $(TEST_SRC) $(CFLAGS_COVERAGE) $(INCLUDES) \
		-lgtest -lgtest_main -pthread
	@echo -e "$(GREEN)ᒥ✅ᒧ Unit tests compiled! Running...$(NC)"
	./$(UNIT_TESTS)
	@echo -e "$(GREEN)ᒥ✅ᒧ All tests completed!$(NC)"

functional_tests: $(NAME)
	@echo -e "$(BLUE)ᒥ🧪ᒧ Running functional tests...$(NC)"
	@python3 ./tests/functional/Tester.py

styleChecker:
	@echo -e "$(BLUE)ᒥ🧪ᒧ Running style checker...$(NC)"
	./shell/styleChecker.sh
	@echo -e "$(GREEN)ᒥ✅ᒧ Style check completed!$(NC)"
