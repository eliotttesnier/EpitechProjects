##
## EPITECH PROJECT, 2024
## my_paint
## File description:
## Makefile
##

.PHONY: all clean fclean re coverage code_line

SRC =	src/splash_screen/anime_splashscreen.c	\
		src/functions/parsing_config.c			\
		src/functions/str_to_array.c			\
		src/loading_assets/get_node.c			\
		src/loading_assets/fill_gamedata.c		\
		src/loading_assets/fill_entity.c		\
		src/loading_assets/fill_player.c		\
		src/loading_assets/fill_musics.c		\
		src/loading_assets/fill_inventory.c		\
		src/loading_assets/fill_maps_object.c	\
		src/loading_assets/fill_menus.c			\
		src/loading_assets/fill_settings.c		\
		src/loading_assets/fill_preview.c		\
		src/loading_assets/fill_hud.c			\
		src/loading_assets/fill_optionmenu.c	\
		src/loading_assets/fill_credit.c		\
		src/loading_assets/fill_keybind.c		\
		debug_functions.c						\
		src/worldmap/world_event.c				\
		src/worldmap/game_loop.c				\
		src/worldmap/game_display.c				\
		src/worldmap/display_hud.c				\
		src/worldmap/objects_display.c			\
		src/worldmap/entity_display.c			\
		src/worldmap/entity_pos.c				\
		src/worldmap/game_process.c				\
		src/worldmap/player_anim.c				\
		src/worldmap/pnj_anim.c					\
		src/worldmap/ennemy_anim.c				\
		src/worldmap/chest_anim.c				\
		src/worldmap/player_hitbox.c			\
		src/worldmap/entity_hitbox.c			\
		src/worldmap/objects_hitbox.c			\
		src/worldmap/player_attack.c			\
		src/worldmap/interactions.c				\
		src/worldmap/process_adv.c				\
		src/worldmap/revive_ennemy.c			\
		src/worldmap/ennemy_attack.c			\
		src/worldmap/drop_item.c				\
		src/functions/get_pixcoord.c			\
		src/functions/random.c					\
		src/functions/is_on_item.c				\
		src/functions/is_on_trash.c				\
		src/functions/put_to_hang.c				\
		src/functions/remove_from_hang.c		\
		src/functions/swap_with_hang.c			\
		src/functions/create_text.c				\
		src/functions/insert_in.c				\
		src/functions/pnj_visible.c				\
		src/functions/ennemy_visible.c			\
		src/functions/object_visible.c			\
		src/functions/get_eny_hitbox.c			\
		src/functions/interact_pnj.c			\
		src/functions/interact_chest.c			\
		src/functions/is_inv_full.c				\
		src/functions/add_to_inv.c				\
		src/functions/put_popup.c				\
		src/functions/free/free_gamedata.c		\
		src/functions/create_toggle.c			\
		src/functions/free/free_map.c			\
		src/functions/free/free_music.c			\
		src/functions/free/free_settings.c		\
		src/functions/free/free_inventory.c		\
		src/functions/texte_center.c			\
		src/functions/free/free_window.c		\
		src/functions/free/free_entity.c		\
		src/functions/free/free_sprite.c		\
		src/functions/free/free_animation.c		\
		src/functions/free/free_movement.c		\
		src/functions/free/free_text.c			\
		src/functions/free/free_objects.c		\
		src/functions/free/free_sfx.c			\
		src/functions/free/free_button.c		\
		src/functions/free/free_menu.c			\
		src/functions/save/save.c				\
		src/functions/get_keycode.c				\
		src/functions/key_bind_loop.c			\
		src/functions/save/save_settings.c		\
		src/functions/save/save_stuff.c			\
		src/functions/save/save_bag.c			\
		src/functions/save/save_player.c		\
		src/functions/save/save_obj.c			\
		src/functions/save/save_pnj.c			\
		src/functions/load.c					\
		src/functions/buttons_actions.c			\
		src/functions/my_itoa.c					\
		src/functions/create_slider.c			\
		src/functions/is_mob_killed.c			\
		src/functions/get_eny_type.c			\
		src/start_menu/draw_key_bind_button.c			\
		src/functions/get_pnj_by_id.c			\
		src/functions/get_chest_by_id.c			\
		src/functions/talked_to.c				\
		src/functions/opened_chest.c			\
		src/functions/ennemy_range.c			\
		src/functions/is_there_save.c			\
		src/functions/set_player_color.c		\
		src/functions/del_pnj.c					\
		src/start_menu/start_menu_button_function.c		\
		src/start_menu/game_loading_button_function.c	\
		src/start_menu/settings_menu_buttons_function.c	\
		src/start_menu/settings_key_bind_function.c		\
		src/start_menu/settings_key_bind_function_two.c	\
		src/start_menu/start_menu_loop.c		\
		src/start_menu/game_loading_loop.c		\
		src/start_menu/settings_menu_loop.c		\
		src/credits/credits_menu_loop.c			\
		src/credits/credits_event.c				\
		src/credits/credits_display.c			\
		src/functions/create_sprite.c			\
		src/inventory/inventory_loop.c			\
		src/inventory/inventory_event.c			\
		src/inventory/inventory_display.c		\
		src/inventory/inventory_position.c		\
		src/inventory/dragndrop.c				\
		src/inventory/stats_handler.c			\
		src/functions/stats_to_str.c			\
		src/functions/slider_event.c			\
		src/functions/toggle_event.c			\
		src/functions/toggle_fullscreen.c		\
		src/functions/big_toggle_event.c		\
		src/functions/set_keybind_position.c	\
		src/functions/button_keybind_event.c	\
		src/functions/play_sfx.c				\
		src/worldmap/update_text.c				\
		src/ingame_menu/ingame_menu_loop.c		\
		src/ingame_menu/ingame_menu_functions.c	\
		src/ingame_menu/ingame_menu_functions_two.c	\
		src/gameover/over_loop.c				\
		src/gameover/over_display.c				\

MAIN =	main.c

OBJ = $(SRC:.c=.o)

OBJ_MAIN = $(MAIN:.c=.o)

NAME =	my_rpg

INCLUDES =	-I./include -I./include/entity -I./include/menu -I./include/map \
			-I./include/inventory

LIBS =	-l csfml-graphics -l csfml-window -l csfml-system -l csfml-audio -lm

CFLAGS =	-Wextra -Wall -Wshadow -Werror

CC := gcc -o $(NAME) $(INCLUDES)

GREEN =		"\033[1;32m"
YELLOW =	"\033[1;33m"
RED =		"\033[1;31m"
BLUE =		"\033[1;36m"
GOLD =		"\033[1;33m"
MAGENTA =	"\033[1;35m"
RESET =		"\033[0m"

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_MAIN)
		chmod 444 files/config.txt || true
		printf $(YELLOW)"\nCreating binary file...\n"$(RESET)
		$(CC) $(OBJ_MAIN) $(OBJ) $(LIBS) $(CFLAGS)
		printf $(GREEN)"\nBinary file created !\n"$(RESET)

clean:
		printf $(YELLOW)"\nCLEANING...\n"$(RESET)
		rm -rf $(OBJ)
		rm -rf $(OBJ_MAIN)
		printf $(GREEN)"Cleaned !\n"$(RESET)

fclean: clean
		rm -rf $(NAME)
		rm -rf *.gcno
		rm -rf *.gcda
		printf $(RED)"Removed binary file !\n"$(RESET)

re: fclean all

coverage: test_run
		printf $(YELLOW)"\nGenerating coverage...\n"$(RESET)
		gcovr
		printf $(GREEN)"Coverage generated !\n"$(RESET)

test_run: $(OBJ)
		printf $(YELLOW)"\Generating tests...\n"$(RESET)
		gcc -o unit_tests $(OBJ) --coverage --lcriterion
		printf $(GREEN)"Tests generated !\n"$(RESET)
		./unit_tests
		printf $(GREEN)"Tests launched !\n"$(RESET)

code_line :
	printf $(MAGENTA)"\nCode lines :\n"$(RESET)
	find $(SRC) $(MAIN) -name '*.c' | xargs wc -l
	find include -name '*.h' | xargs wc -l
