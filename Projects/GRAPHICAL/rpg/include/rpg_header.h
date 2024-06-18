/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** rpg_header
*/

#pragma once

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/System.h>
#include <SFML/Window/Keyboard.h>
#include "math.h"

#include "debug_header.h"
#include "rpg_macro.h"
#include "rpg_struct.h"

#define ATTACK_SPEED_ENY 1.5
#define INV_SIZE 32
#define FRAMERATE 160
#define SPEED 7500 * 1.75

typedef void (*load_func_t)(gamedata_t *gamedata, config_t *config);
typedef void (*scene_loop_t)(gamedata_t *gamedata, sfEvent *event);

//divers animations
void anime_splashscreen(gamedata_t *);
void update_view(gamedata_t *game);

//load and save handling
text_t *create_text(char *path);
text_t *recreate_text(text_t *old, char *path);
text_t *create_text_menu(char *path, char *text, sfVector2f pos,
    sfVector2f scale);
config_t *get_config(char *filepath);
char **str_to_array(char *line, char *ban);

//fill of games data
config_t *get_node(char *id, config_t *config);
item_t *copy_item(int id);
void fill_gamedata(gamedata_t *);
void fill_backpack(gamedata_t *gamedata, config_t *config);
void fill_equipment(gamedata_t *gamedata, config_t *config);
void fill_skilltree(gamedata_t *gamedata, config_t *config);
void fill_maps(gamedata_t *gamedata, config_t *config);
void fill_pnj_list(gamedata_t *gamedata, config_t *config);
void fill_player(gamedata_t *gamedata, config_t *config);
void fill_ennemy_list(gamedata_t *gamedata, config_t *config);
void fill_object_list(gamedata_t *gamedata, config_t *config);
void fill_musics(gamedata_t *gamedata, config_t *config);
void fill_settings(gamedata_t *gamedata, config_t *config);
void fill_startmenu(gamedata_t *gamedata, config_t *config);
void fill_optionmenu(gamedata_t *gamedata, config_t *config);
void fill_gamemenu(gamedata_t *gamedata, config_t *config);
void fill_preview(gamedata_t *gamedata, config_t *config);
void fill_game_hud(gamedata_t *game, config_t *config);
void fill_credit(gamedata_t *game);
void fill_keybind_button(gamedata_t *gamedata);
void set_keybind_button_text(gamedata_t *gamedata);

//scene loops
void start_menu_loop(gamedata_t *gamedata, sfEvent *event);
void game_loop(gamedata_t *gamedata, sfEvent *event);
void inventory_loop(gamedata_t *gamedata, sfEvent *event);
void game_loading_loop(gamedata_t *gamedata, sfEvent *event);
void settings_menu_loop(gamedata_t *gamedata, sfEvent *event);
void credits_menu_loop(gamedata_t *gamedata, sfEvent *event);
void key_bind(gamedata_t *gamedata, sfEvent *event);
void ingame_menu_loop(gamedata_t *gamedata, sfEvent *event);
void over_loop(gamedata_t *game, sfEvent *event);

//events
void world_events(gamedata_t *game, sfEvent *event);
void inventory_event(gamedata_t *game, sfEvent *event);
void credits_event(gamedata_t *game, sfEvent *event);
void toggle_event(gamedata_t *gamedata, sfEvent *event, toggle_t *toggle);

//displays
void game_display(gamedata_t *game, bool inventory);
void game_display_pnj_back(gamedata_t *game);
void game_display_pnj_front(gamedata_t *game);
void game_display_ennemy_back(gamedata_t *game);
void game_display_ennemy_front(gamedata_t *game);
void display_objects_front(gamedata_t *game);
void display_objects_back(gamedata_t *game);
void display_hud(gamedata_t *game);
void inventory_display(gamedata_t *game);
void credits_display(gamedata_t *game);
void over_display(gamedata_t *game);
void display_ennemy_lifebar(gamedata_t *game);

//process
void game_process(gamedata_t *game);
void player_attack(gamedata_t *game);
void update_entity_pos(gamedata_t *game);
void check_attack(gamedata_t *game);
void inventory_positions(gamedata_t *game);
void inventory_drag(gamedata_t *game, sfVector2f pix);
void inventory_drop(gamedata_t *game, sfVector2f pix);
void inventory_consume(gamedata_t *game, sfVector2f pix);
void remove_stats(gamedata_t *game, item_t *item);
void add_stats(gamedata_t *game, item_t *item);
void revive_ennemy(gamedata_t *game);
void ennemy_attack(gamedata_t *game);

//animations
void player_anim(player_t *player);
void pnj_anim(gamedata_t *game);
void eny_anim(gamedata_t *game);
void chest_anim(gamedata_t *game);

//Hitbox
bool check_walls(gamedata_t *game);
bool check_height(gamedata_t *game);
bool check_entity(gamedata_t *game, float x, float y);
bool check_object(gamedata_t *game, float x, float y);
bool is_in_pnj_hitbox(sfVector2f pos, pnj_t *pnj);
sfFloatRect get_eny_hitbox(ennemy_t *eny);

//Interactions
void interact(gamedata_t *game);
pnj_t *interact_pnj(gamedata_t *game);
chest_t *interact_chest(gamedata_t *game);

//Functions
bool is_on_item(backpack_t *back, sfVector2f pix);
bool is_on_trash(gamedata_t *game, sfVector2f pix);
int get_on_equip(equipment_t *equip, sfVector2f pix);
int is_on_equip(gamedata_t *game, sfVector2f pix);
void put_to_hang(gamedata_t *game, backpack_t *back, sfVector2f pix);
void put_equip_to_hang(gamedata_t *game, equipment_t *equip, stuff_t stf,
    sfVector2f pix);
void insert_in_equip(gamedata_t *game, int stf);
void remove_from_hang(gamedata_t *game);
void remove_in_back(gamedata_t *game, backpack_t *back);
void swap_with_hang(gamedata_t *game, backpack_t *back);
void insert_in_back(gamedata_t *game, backpack_t *back);
sfVector2f get_pixcoord(gamedata_t *game);
bool is_pnj_visible(gamedata_t *game, pnj_t *pnj);
bool is_eny_visible(gamedata_t *game, ennemy_t *eny);
bool is_chest_visible(gamedata_t *game, chest_t *chest);
bool is_on_button(button_t *button, sfVector2f pix);
slider_t *create_slider(char *path_back, sfIntRect rect_back, char *path_dot,
    sfIntRect rect_dot);
bool is_inv_full(gamedata_t *game);
void add_to_inv(gamedata_t *game, item_t *item);
void put_popup(gamedata_t *game, char *msg);
void slider_event(gamedata_t *gamedata, sfEvent *event, slider_t *slider);
void slider_action(gamedata_t *gamedata, slider_t *slider);
bool is_on_sprite(sprite_t *sprite, sfVector2f pix);
char *my_itoa(int nbr);
int my_nbrlen(int nbr);
toggle_t *create_toggle(sfVector2f pos);
void update_text(gamedata_t *game);
void toggle_fullscreen(void *gamedata);
void set_pos_keybind_button(struct option_menu_s *optionmenu);
void button_event_keybind(gamedata_t *gamedata, sfEvent *event);
void texte_center(button_t *button, text_t *text);
const char *key_code_to_string(sfKeyCode key);
void key_bind_loop(call_key_bind_t *arg);
pnj_t *get_pnj_by_id(gamedata_t *game, int id);
bool talked_to_pnj(gamedata_t *game, int id);
void process_adv(gamedata_t *game);
chest_t *get_chest_by_id(gamedata_t *game, int id);
bool opened_chest(gamedata_t *game, int id);
bool is_in_eny_range(gamedata_t *game, ennemy_t *eny);
sfVector2f get_center(sprite_t *sprite);
bool is_eny_killed(gamedata_t *game, int id);
ennemy_t *get_eny_by_id(gamedata_t *game, int id);
eny_t get_eny_type(ennemy_t *eny);
void drop_item(gamedata_t *game, ennemy_t *eny);
int my_random(int min, int max);
bool is_there_save(void);
void set_player_color(gamedata_t *game, bool red);
void del_pnj(gamedata_t *game, int id);
void update_position(gamedata_t *game);

//save
void save(gamedata_t *game);
void save_settings(gamedata_t *game, int fd);
void save_stuff(gamedata_t *game, int fd);
void save_bag(gamedata_t *game, int fd);
void save_player(gamedata_t *game, int fd);
void save_obj(gamedata_t *game, int fd);
void save_pnj(gamedata_t *game, int fd);

//load
void load(gamedata_t *game, bool new);

//free
void free_gamedata(gamedata_t *game, bool load);
void free_sprite(sprite_t *sprite);
void free_sprite_l(sprite_t sprite);
void free_text(text_t *text);
void free_map(map_t *map);
void free_music(music_t *music);
void free_window(window_t *window);
void free_settings(settings_t *settings);
void free_inventory(inventory_t *inv);
void free_animation(animation_t *anim);
void free_movement(movement_t *move);
void free_entity(entity_t *entity);
void free_obj(object_t *obj);
void free_sfx(sfx_t *sfx);
void free_button(button_t *button);
void free_slider(slider_t *slider);
void free_toggle(toggle_t *toggle);
void free_keybind(key_bind_t *keybind);
void free_big_toggle(big_toggle_t *toggle);
void free_menu(menu_t *menu);

//sprite creation
sprite_t *create_sprite(char *path, sfIntRect rect);
sfTexture *create_texture(char *path);
button_t *create_button(char *path, sfIntRect rect);
big_toggle_t *create_big_toggle(sfVector2f pos);

//buttons actions
void button_event(gamedata_t *gamedata, sfEvent *event, button_t *buton);
void big_toggle_event(gamedata_t *gamedata, sfEvent *event,
    big_toggle_t *toggle);
void draw_button(gamedata_t *gamedata, button_t *button);
void button_press(gamedata_t *gamedata, button_t *button);
void button_hover(gamedata_t *gamedata, button_t *button);
void settings_button(void *arg);
void play_button(void *arg);
void credit_button(void *arg);
void leave_button(void *arg);
void back_button(void *arg);
void newsave_button(void *arg);
void load_button(void *arg);
void resolutionscreen(void *arg);
void forward_key(void *arg);
void backward_key(void *arg);
void left_key(void *arg);
void right_key(void *arg);
void inventory_key(void *arg);
void interact_key(void *arg);
void attack_key(void *arg);
void fire_spell_key(void *arg);
void heal_spell_key(void *arg);
void stun_spell_key(void *arg);
void draw_key_bind_button(gamedata_t *gamedata);
void save_button(void *arg);
void load_button_ingame_menu(void *arg);
void settings_button_ingame_menu(void *arg);
void inventory_button(void *arg);
void close_button_ingame_menu(void *arg);
void leave_button_ingame_menu(void *arg);

//get stats for hud text
char *get_atk(gamedata_t *game);
char *get_def(gamedata_t *game);
char *get_xp(gamedata_t *game);
char *get_mana(gamedata_t *game);
char *get_hp(gamedata_t *game);

//SFX
void play_sfx(gamedata_t *game, sfx_enum_t sfx);
