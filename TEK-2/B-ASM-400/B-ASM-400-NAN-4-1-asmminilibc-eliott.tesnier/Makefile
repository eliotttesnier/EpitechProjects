##
## EPITECH PROJECT, 2024
## minilibc
## File description:
## Makefile
##

.PHONY: all clean fclean re tests tests_run

# Couleurs ANSI
GREEN=\033[1;32m
BLUE=\033[1;34m
RED=\033[1;31m
YELLOW=\033[1;33m
NC=\033[0m

SRC =	src/strlen.asm		\
		src/strchr.asm		\
		src/strrchr.asm		\
		src/memset.asm		\
		src/memcpy.asm		\
		src/strcmp.asm		\
		src/memmove.asm		\
		src/strncmp.asm		\
		src/strcasecmp.asm	\
		src/strstr.asm		\
		src/strpbrk.asm		\
		src/strcspn.asm		\
		src/syscall.asm		\
		src/ffs.asm			\
		src/memfrob.asm		\
		src/strfry.asm		\

TEST_SRC =  tests/tests_strlen.c		\
			tests/tests_memset.c		\
			tests/tests_strchr.c		\
			tests/tests_strrchr.c		\
			tests/tests_memcpy.c		\
			tests/tests_memmove.c		\
			tests/tests_strcmp.c		\
			tests/tests_strncmp.c		\
			tests/tests_strcasecmp.c	\
			tests/tests_strstr.c		\
			tests/tests_strpbrk.c		\
			tests/tests_strcspn.c		\
			tests/tests_index.c			\
			tests/tests_rindex.c		\
			tests/tests_syscall.c		\
			tests/tests_ffs.c			\
			tests/tests_memfrob.c		\
			tests/tests_strfry.c 		\

OBJ = $(SRC:.asm=.o)

NAME = libasm.so

CC = nasm -f elf64

all: $(NAME)

$(NAME): $(OBJ)
	ld -shared -o $(NAME) $(OBJ)

%.o: %.asm
	nasm -f elf64 $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf *gcno *gcda

re: fclean all

tests: all
	gcc main.c -L. -lasm -o temp
	LD_PRELOAD=./libasm.so ./temp

tests_run: all
	gcc $(TEST_SRC) -L. -lasm -o unit_tests --coverage -lcriterion
	LD_PRELOAD=./libasm.so ./unit_tests
