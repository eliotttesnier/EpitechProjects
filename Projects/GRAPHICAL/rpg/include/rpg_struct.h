/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** struct_header
*/

#pragma once

#include "rpg_header.h"

typedef struct splash_screen_s {
    sfSprite *bg;
    sfTexture *bg_text;
    sfSprite *logo;
    sfTexture *logo_text;
    sfSprite *fondu_bg;
    sfTexture *fondu_bg_text;
    sfClock *anime_clock;
} splashscreen_t;

typedef struct window_s {
    sfRenderWindow *window;
    sfView *view;
    sfVideoMode resolution;
    sfBool fullscreen;
    sfUint8 *icon;
} window_t;

typedef struct stats_s {
    int health;
    int max_health;
    int attack;
    int defense;
    int xp;
    int mana;
} stats_t;

typedef struct sprite_s {
    sfIntRect rect;
    sfTexture *texture;
    sfSprite *sprite;
} sprite_t;

typedef enum skill_state_e {
    LOCKED = 0,
    UNLOCKED,
    HAS,
    HOVER,
    CANT
} skillstate_t;

typedef struct skill_tree_s {
    int to_defind;
} skilltree_t;

typedef enum stuff {
    HELMET = 0,
    CHEST,
    GLOVES,
    BOOTS,
    WEAPON
} stuff_t;

typedef struct item_s {
    char *asset_path;
    int id;
    int lvl;
    int atk;
    int def;
    int reg;
    void (*function)(void *);
    char *name;
} item_t;

typedef struct text_s {
    sfText *text;
    sfFont *font;
    char *str;
} text_t;

typedef struct equipment_s {
    struct sprite_s *sprites[5];
    struct item_s *equiped[5];
} equipment_t;

typedef struct backpack_s {
    struct sprite_s *sprite;
    struct item_s *item;
    struct backpack_s *next;
} backpack_t;

typedef struct hanging_s {
    item_t *item;
    struct sprite_s *sprite;
    sfVector2f pos;
} hanging_t;

typedef struct preview_s {
    struct sprite_s worn[4];
    struct sprite_s not_worn[4];
} preview_t;

typedef struct hud_map_s {
    struct sprite_s *map;
    struct sprite_s *player;
    struct sprite_s *cadre;
} hud_map_t;

typedef struct popup_s {
    text_t *msg;
    sprite_t *back;
    sfClock *time_since_display;
} popup_t;

typedef struct hud_s {
    hud_map_t *minimap;
    text_t *hp;
    text_t *mana;
    text_t *xp;
    popup_t *popup;
    sprite_t *adv[14];
    sprite_t *gameover;
} hud_t;

typedef struct inventory_s {
    struct stats_s *stats;
    struct sprite_s *skillsprite;
    struct skill_tree_s *skilltree;
    struct equipment_s *equipment;
    struct sprite_s *equipsprite;
    struct backpack_s *backpack;
    struct sprite_s *backsprite;
    struct hanging_s *hanging;
    struct preview_s *preview;
    struct text_s *hp;
    struct text_s *mana;
    struct text_s *atk;
    struct text_s *def;
    struct text_s *xp;
} inventory_t;

typedef struct map_s {
    sfImage *colmap;
    sprite_t *back;
    sprite_t *dec;
} map_t;

typedef struct movement_s {
    sfVector2f direction;
    sfClock *clock;
} movement_t;

typedef struct animation_s {
    sfClock *clock;
} animation_t;

typedef struct fight_s {
    sfIntRect spear_hitbox;
    sfIntRect axe_hitbox;
    sfIntRect sword_hitbox;
    sfClock *buffer;
    bool attacking;
    bool can_attack;
} fight_t;

typedef struct player_s {
    sfVector2f position;
    struct stats_s *stat;
    struct movement_s *movement;
    struct animation_s *animation;
    struct sprite_s sprite[4];
    struct sprite_s attack[3];
    struct fight_s *fight;
} player_t;

typedef struct lifebar_s {
    sfRectangleShape *life;
    sfRectangleShape *back;
} lifebar_t;

typedef struct ennemy_s {
    int id;
    int atk;
    int hp;
    int maxhp;
    struct sprite_s *sprite;
    sfVector2f position;
    sfVector2f anchor;
    struct movement_s *movement;
    struct animation_s *animation;
    char *path;
    bool alive;
    sfClock *respawn;
    int respawn_time;
    struct ennemy_s *next;
    struct fight_s *fight;
    lifebar_t *lifebar;
} ennemy_t;

typedef struct voicebox_s {
    char *msg;
    struct voicebox_s *next;
} voicebox_t;

typedef struct pnj_s {
    int id;
    struct sprite_s *sprite;
    struct movement_s *movement;
    struct animation_s *animation;
    sfVector2f position;
    sfVector2f anchor;
    struct voicebox_s *voicebox;
    struct pnj_s *next;
    char *path;
    bool unlocked;
    bool talked;
} pnj_t;

typedef struct entity_s {
    struct player_s *player;
    struct ennemy_s *ennemy;
    struct pnj_s *pnj;
} entity_t;

typedef struct chest_s {
    struct sprite_s *sprite;
    struct animation_s *animation;
    item_t *content;
    bool opened;
    bool opening;
    sfVector2f position;
    struct chest_s *next;
    int id;
    char *path;
} chest_t;

typedef struct bridge_s {
    sprite_t *broken;
    sprite_t *fixed;
    bool repaired;
} bridge_t;

typedef struct object_s {
    chest_t *chests;
    bridge_t *bridge;
    sprite_t *gate;
} object_t;

typedef struct music_s {
    sfMusic *menu;
    sfMusic *world;
    sfMusic *epic;
} music_t;

typedef enum custom_key_e {
    FORWARD = 0,
    BACKWARD,
    LEFT,
    RIGHT,
    INTERACT,
    ATTACK,
    INVENTORY,
    PAUSE,
    SPELL1,
    SPELL2,
    SPELL3
} customkey_t;

typedef struct settings_s {
    int vol_music;
    int vol_sfx;
    sfKeyCode *keys;
} settings_t;

typedef enum button_state_s {
    RELEASE,
    HOVERED,
    PRESS
} button_state_t;

typedef enum toggle_state_s {
    ON,
    ON_HOVERED,
    OFF,
    OFF_HOVERED
} toggle_state_t;

typedef struct button_s {
    struct sprite_s *sprite;
    void (*func)(void *);
    enum button_state_s state;
    bool clickable;
} button_t;

typedef struct slider_s {
    struct sprite_s *back;
    struct sprite_s *dot;
    void (*func)(void *);
    bool clicked;
} slider_t;

typedef struct toggle_s {
    struct sprite_s *toggle;
    void (*func)(void *);
    enum toggle_state_s state;
    bool active;
} toggle_t;

typedef struct key_bind_s {
    struct text_s *name;
    struct text_s *key;
    struct button_s *button;
} key_bind_t;


typedef struct big_toggle_s {
    struct sprite_s *toggle;
    void (*func)(void *);
    enum toggle_state_s state;
    bool active;
} big_toggle_t;

typedef struct option_menu_s {
    struct button_s *back;
    struct slider_s *sfx;
    struct slider_s *mus;
    struct sprite_s *keymenu;
    struct sprite_s *soundmenu;
    struct sprite_s *winmenu;
    struct text_s *mustext;
    struct text_s *musdata;
    struct text_s *sfxtext;
    struct text_s *sfxdata;
    struct text_s *fullscreentext;
    struct text_s *resolution;
    struct toggle_s *fullscreen;
    struct big_toggle_s *resolutionscreen;
    struct key_bind_s *forward;
    struct key_bind_s *backward;
    struct key_bind_s *left;
    struct key_bind_s *right;
    struct key_bind_s *inventory;
    struct key_bind_s *interact;
    struct key_bind_s *attack;
    struct key_bind_s *fire_spell;
    struct key_bind_s *heal_spell;
    struct key_bind_s *stun_spell;
} optionmenu_t;

typedef struct game_menu_s {
    struct button_s *close;
    struct button_s *back;
    struct button_s *save;
    struct button_s *load;
    struct button_s *inventory;
    struct button_s *option;
    struct button_s *quit;
    struct sprite_s *panel;
} gamemenu_t;

typedef struct start_menu_s {
    struct option_menu_s *options;
    struct button_s *settings;
    struct button_s *credits;
    struct button_s *play;
    struct button_s *leave;
    struct button_s *back;
    struct button_s *newsave;
    struct button_s *load;
    struct sprite_s *grayed;
    struct sprite_s *background;
    struct sprite_s *first_panel;
    struct sprite_s *second_panel;
    struct text_s *titre;
} startmenu_t;

typedef struct credit_menu_s {
    struct sprite_s *back;
    struct button_s *backbutt;
    struct sprite_s *display;
    sfClock *clock;
} credit_menu_t;

typedef struct menu_s {
    struct game_menu_s *gamemenu;
    struct start_menu_s *startmenu;
    struct option_menu_s *optionmenu;
    struct credit_menu_s *creditmenu;
} menu_t;

typedef enum scene_e {
    S_START_MENU = 0,
    S_GAME_LOADING,
    S_GAME,
    S_PAUSE_MENU,
    S_INVENTORY,
    S_SETTINGS_MENU,
    S_CREDITS_MENU,
    S_GAME_OVER,
} scene_t;

typedef enum adv_e {
    WAKEUP = 0,
    TALK_BEACHMAN,
    OPEN_CHEST,
    TALK_BRIDGEMAN,
    TALK_NORTHGIRL,
    TALK_DAMOPIES,
    KILL_WOLVES,
    TALK_MINER,
    KILL_GOLEM,
    ENTER_MINES,
    FIND_CHESTS,
    TALK_DAMOPIES_END,
    END,
} adv_t;

typedef enum eny_e {
    GOBLIN,
    WOLF,
    GOLEM,
} eny_t;

#define NB_SFX 15

typedef enum sfx_e {
    SFX_GOBELIN = 0,
    SFX_WOLF,
    SFX_GOLEM,
    SFX_SPEAR,
    SFX_SWORD,
    SFX_AXE,
    SFX_DAMAGE,
    SFX_DIE,
    SFX_INV,
    SFX_EAT,
    SFX_CHEST,
    SFX_TALKING,
    SFX_GDEATH,
    SFX_WDEATH,
    SFX_GODEATH,
} sfx_enum_t;

typedef struct sfx_s {
    sfMusic *sounds[NB_SFX];
} sfx_t;

typedef struct gamedata_s {
    struct window_s *window;
    struct inventory_s *inventory;
    struct map_s *map;
    struct entity_s *entity;
    struct object_s *obj;
    struct music_s *music;
    struct settings_s *settings;
    struct menu_s *menu;
    struct hud_s *hud;
    int kill_count;
    struct sfx_s *sfx;
    enum scene_e scene;
    enum adv_e adv;
    enum scene_e prescene;
} gamedata_t;

typedef struct config_s {
    char **line;
    struct config_s *next;
} config_t;

typedef struct call_key_bind_s {
    struct key_bind_s *keybind;
    struct gamedata_s *game;
    int key_type;
} call_key_bind_t;
