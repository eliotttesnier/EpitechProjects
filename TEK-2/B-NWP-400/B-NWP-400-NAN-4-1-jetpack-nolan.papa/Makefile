##
## EPITECH PROJECT, 2025
## NTS
## File description:
## Makefile
##

.PHONY: all clean fclean re client server functional_tests

# Couleurs ANSI
GREEN=\033[1;32m
BLUE=\033[1;34m
RED=\033[1;31m
YELLOW=\033[1;33m
NC=\033[0m

# Server
MAIN_SRC_SERVER =	src/server/main.cpp							\

SRC_SERVER	=	src/server/Parser.cpp							\
				src/server/Player.cpp							\
				src/server/entities/AEntity.cpp 				\
				src/server/entities/VoidEntity.cpp				\
				src/server/entities/CoinEntity.cpp				\
				src/server/entities/ElectricEntity.cpp			\
				src/server/Game.cpp								\
				src/server/communication/Communication.cpp		\
				src/server/communication/ClientData.cpp		\
				src/server/communication/GameState.cpp		\

MAIN_OBJ_SERVER = $(MAIN_SRC_SERVER:.cpp=.o)

OBJ_SERVER = $(SRC_SERVER:.cpp=.o)

# Client
MAIN_SRC_CLIENT =	src/client/main.cpp

SRC_CLIENT	=	src/client/Display.cpp							\
				src/client/DisplayGame.cpp						\
				src/client/Menu.cpp								\
				src/client/buttons/AButton.cpp					\
				src/client/buttons/CloseButton.cpp				\
				src/client/buttons/PlayButton.cpp				\
				src/client/buttons/ConnectButton.cpp			\
				src/client/input/Input.cpp						\
				src/client/communication/Communication.cpp		\

MAIN_OBJ_CLIENT = $(MAIN_SRC_CLIENT:.cpp=.o)

OBJ_CLIENT = $(SRC_CLIENT:.cpp=.o)

INCLUDES = -I./src/ -I./src/server/ -I./src/entities \
			-I./src/client/

CFLAGS =	-std=c++20 -Wall -Wextra -Werror

SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

NAME_SERVER = jetpack_server

NAME_CLIENT = jetpack_client

CC = g++

all: server client

server: $(OBJ_SERVER) $(MAIN_OBJ_SERVER)
	@echo -e "$(BLUE)ᒥ🔧ᒧ Compiling $(NAME_SERVER)...$(NC)"
	$(CC) -o $(NAME_SERVER) $(MAIN_OBJ_SERVER) $(OBJ_SERVER)
	@echo -e "$(GREEN)ᒥ✅ᒧ Compilation successful!$(NC)"

client: $(OBJ_CLIENT) $(MAIN_OBJ_CLIENT)
	@echo -e "$(BLUE)ᒥ🔧ᒧ Compiling $(NAME_CLIENT)...$(NC)"
	$(CC) -o $(NAME_CLIENT) $(MAIN_OBJ_CLIENT) $(OBJ_CLIENT) $(SFML_FLAGS)
	@echo -e "$(GREEN)ᒥ✅ᒧ Compilation successful!$(NC)"

$(OBJ_SERVER) $(MAIN_OBJ_SERVER): %.o: %.cpp
	@echo -e "$(YELLOW)ᒥ🚀ᒧ Compiling $<...$(NC)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_CLIENT) $(MAIN_OBJ_CLIENT): %.o: %.cpp
	@echo -e "$(YELLOW)ᒥ🚀ᒧ Compiling $<...$(NC)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo -e "$(RED)ᒥ🔥ᒧ Removing object files...$(NC)"
	@rm -rf $(OBJ_SERVER)
	@rm -rf $(MAIN_OBJ_SERVER)
	@rm -rf $(OBJ_CLIENT)
	@rm -rf $(MAIN_OBJ_CLIENT)
	@echo -e "$(GREEN)ᒥ✅ᒧ Clean complete!$(NC)"

fclean: clean
	@echo -e "$(RED)ᒥ🔥ᒧ Removing $(NAME_CLIENT) and $(NAME_SERVER) ...$(NC)"
	@rm -rf $(NAME_SERVER)
	@rm -rf $(NAME_CLIENT)
	@rm -rf unit_tests
	@rm -rf *.gcno
	@rm -rf *.gcda
	@rm -rf vgcore.*
	@echo -e "$(GREEN)ᒥ✅ᒧ Full clean complete!$(NC)"

re: fclean all

functional_tests: all
	@echo -e "$(BLUE)ᒥ🔧ᒧ Running functional tests...$(NC)"
	@python3 tests/functional/Tester.py
	@echo -e "$(GREEN)ᒥ✅ᒧ Functional tests passed!$(NC)"
