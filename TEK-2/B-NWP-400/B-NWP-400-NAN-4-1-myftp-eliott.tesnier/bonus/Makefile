##
## EPITECH PROJECT, 2024
## Rush 3
## File description:
## Makefile
##

.PHONY: all clean fclean re coverage

# ANSI Colors
GREEN=\033[1;32m
BLUE=\033[1;34m
RED=\033[1;31m
YELLOW=\033[1;33m
NC=\033[0m

MAIN = src/main.cpp

MAIN_OBJ = $(MAIN:.cpp=.o)

SRC =	src/Client.cpp							\
		src/DataConnection.cpp					\
		src/Utils.cpp							\
		src/commands/BasicCommands.cpp			\
		src/commands/InfoCommands.cpp			\
		src/commands/FileManagementCommands.cpp	\
		src/commands/DirectoryCommands.cpp		\
		src/commands/NavigationCommands.cpp		\
		src/commands/FileCommands.cpp			\

OBJ = $(SRC:.cpp=.o)

INCLUDES = -I./src

CFLAGS =	-std=c++20 -Wall -Wextra -Werror

LIBS =

NAME =  client

CC = g++

all: $(NAME)

$(NAME): $(OBJ) $(MAIN_OBJ)
	@echo -e "$(BLUE)ᒥ🔧ᒧ Compiling $(NAME)...$(NC)"
	@$(CC) -o $(NAME) $(MAIN_OBJ) $(OBJ) $(CFLAGS) $(INCLUDES) $(LIBS)
	@echo -e "$(GREEN)ᒥ✅ᒧ Compilation completed successfully!$(NC)"

%.o: %.cpp
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
	@rm -rf vgcore.*
	@echo -e "$(GREEN)ᒥ✅ᒧ Full clean completed!$(NC)"

re: fclean all
