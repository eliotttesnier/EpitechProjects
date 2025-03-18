##
## EPITECH PROJECT, 2025
## B-FUN-400-NAN-4-1-bswolfram-eliott.tesnier
## File description:
## Makefile
##

# Colors
GREEN = \033[1;32m
BLUE = \033[1;34m
RED = \033[1;31m
YELLOW = \033[1;33m
NC = \033[0m

NAME = wolfram

all: build copy

build:
	@echo -e "$(BLUE)ᒥ🔧ᒧ Building $(NAME)...$(NC)"
	@stack build
	@echo -e "$(GREEN)ᒥ✅ᒧ Build successful!$(NC)"

copy:
	@echo -e "$(YELLOW)ᒥ📋ᒧ Copying binary...$(NC)"
	@cp `stack path --local-install-root`/bin/$(NAME) .
	@echo -e "$(GREEN)ᒥ✅ᒧ Binary copied successfully!$(NC)"

clean:
	@echo -e "$(RED)ᒥ🧹ᒧ Cleaning build files...$(NC)"
	@stack clean
	@echo -e "$(GREEN)ᒥ✅ᒧ Clean complete!$(NC)"

fclean: clean
	@echo -e "$(RED)ᒥ🗑️ᒧ Removing $(NAME)...$(NC)"
	@rm -f $(NAME)
	@echo -e "$(GREEN)ᒥ✅ᒧ Full clean complete!$(NC)"

re: fclean all

tests_run:
	@echo -e "$(YELLOW)ᒥ🧪ᒧ Running tests...$(NC)"
	@stack test
	@rm -rf src/Main
	@echo -e "$(GREEN)ᒥ✅ᒧ Tests completed!$(NC)"

functional_tests: all
	@echo -e "$(YELLOW)ᒥ🧪ᒧ Running functional tests...$(NC)"
	@python3 tests/functional/tester.py

.PHONY: all build copy clean fclean re tests_run functional_tests
