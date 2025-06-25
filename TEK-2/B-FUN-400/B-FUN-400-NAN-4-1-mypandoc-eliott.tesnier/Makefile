##
## EPITECH PROJECT, 2025
## B-FUN-400-NAN-4-1-bswolfram-eliott.tesnier
## File description:
## Makefile
##

NAME = mypandoc

MAIN = src/Main

C_STYLE = coding-style-reports.log

all: build copy

build:
	@echo "$(BLUE)ᒥ🔧ᒧ Building $(NAME)...$(NC)"
	stack build --allow-different-user
	@echo "$(GREEN)ᒥ✅ᒧ Build successful!$(NC)"

copy:
	@echo "$(YELLOW)ᒥ📋ᒧ Copying binary...$(NC)"
	cp `stack path --local-install-root`/bin/$(NAME) .
	@echo "$(GREEN)ᒥ✅ᒧ Binary copied successfully!$(NC)"

clean:
	@echo "$(RED)ᒥ🧹ᒧ Cleaning build files...$(NC)"
	stack clean
	@echo "$(GREEN)ᒥ✅ᒧ Clean complete!$(NC)"

fclean: clean
	@echo "$(RED)ᒥ🗑️ᒧ Removing $(NAME)...$(NC)"
	rm -f $(NAME)
	@echo "$(RED)ᒥ🗑️ᒧ Removing $(C_STYLE)...$(NC)"
	rm -f $(C_STYLE)
	@echo "$(RED)ᒥ🗑️ᒧ Removing $(MAIN)...$(NC)"
	rm -f $(MAIN)
	@echo "$(GREEN)ᒥ✅ᒧ Full clean complete!$(NC)"

re: fclean all

tests_run:
	@echo "$(YELLOW)ᒥ🧪ᒧ Running tests...$(NC)"
	stack test --allow-different-user
	@rm -rf src/Main
	@echo "$(GREEN)ᒥ✅ᒧ Tests completed!$(NC)"

functional_tests: all
	@echo "$(YELLOW)ᒥ🧪ᒧ Running functional tests...$(NC)"
	@python3 tests/functional/Tester.py

.PHONY: all build copy clean fclean re tests_run functional_tests
