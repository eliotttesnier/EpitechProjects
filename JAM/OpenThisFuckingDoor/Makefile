##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Core Makefile
##

SRC			= 	src/main.cpp \
				src/Game/Game.cpp \
				src/Modules/HitboxModule.cpp \
				src/Modules/MovementModule.cpp \
				src/Modules/CollisionModule.cpp \
				src/Modules/DisplayModule.cpp \
				src/Modules/TimeModule.cpp \
				src/Modules/RotatableModule.cpp \
				src/Modules/PositionModule.cpp \
				src/Modules/PlayerModule.cpp \
				src/Modules/EventModule.cpp \
				src/GameMenu/GameMenu.cpp \
				src/button/button.cpp \
				src/Player/Player.cpp \
				src/Ground/Ground.cpp \
				src/OptionMenu/OptionMenu.cpp \
				src/GameMap/GameMap.cpp \
				src/Modules/InteractionModule.cpp \
				src/credit/credit.cpp \
				src/Wall/Wall.cpp \
				src/Totem/Totem.cpp \
				src/Door/Door.cpp \
				src/Pillar/Pillar.cpp \
				src/Warp/Warp_futur.cpp \
				src/Warp/Warp_past.cpp \
				src/Warp/Warp_present.cpp \
				src/Warp/Warp.cpp \

CXX_OBJS			= $(SRC:.cpp=.o)

NAME		= OpenThisFuckingDoor


INCLUDE 	= -I./src/Game/ -I./src/ -I./src/Modules -I./src/GameMenu -I./src/button -I./src/OptionMenu -I./src/GameMap/ -I./src/credit
GRAPHFLAG	= -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
CXXFLAGS 	= -std=c++20 -Wall -Wextra -Werror -g $(INCLUDE) $(GRAPHFLAG)

all: $(NAME)

$(NAME): $(CXX_OBJS)
	g++ -o $(NAME) $(CXX_OBJS) $(CXXFLAGS)

clean:
	rm -f $(CXX_OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all
