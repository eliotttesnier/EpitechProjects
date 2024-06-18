/*
** EPITECH PROJECT, 2023
** header
** File description:
** header
*/

#ifndef SFML_GRAPHICS_TYPES
    #define SFML_GRAPHICS_TYPES

    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <stdlib.h>

struct sound_effect {
    sfSoundBuffer *buffer;
    sfSound *sound;
};

struct sounds {
    struct sound_effect error;
    struct sound_effect shotgun;
    struct sound_effect reload;
    struct sound_effect empty;
    struct sound_effect music;
    struct sound_effect button;
    struct sound_effect book;
};

struct duck_coor {
    int x;
    int y;
    int speed;
};

struct variables {
    sfBool pause;
    sfBool anim_gun;
    sfClock *gun_anim;
    struct sounds sounds;
    struct duck_coor duck1;
    struct duck_coor duck2;
    struct duck_coor duck3;
    struct duck_coor duck4;
    int bonus_heart;
    int diff;
    int voleff;
    int volmus;
    int max_streak;
    int max_score;
    int curr_streak;
    int score;
    int lives;
    int bullets;
};

struct sprite {
    sfTexture *texture;
    sfSprite *sprite;
    sfIntRect rect;
};

struct all_s {
    struct sprite duck1;
    struct sprite duck2;
    struct sprite duck3;
    struct sprite duck4;
    struct sprite shotgun;
    struct sprite back;
    struct sprite pause;
    struct sprite volefdown;
    struct sprite volefup;
    struct sprite volmudown;
    struct sprite volmusup;
    struct sprite diffdown;
    struct sprite diffup;
    struct sprite volmusic;
    struct sprite volsdef;
    struct sprite difficulty;
    struct sprite play;
    struct sprite leave;
    struct sprite restart;
    struct sprite game_over;
};

struct text {
    sfFont *font;
    sfText *text;
};

struct texts_display {
    struct text ammo;
    struct text lives;
    struct text difficulty;
    struct text mus_volume;
    struct text sef_volume;
    struct text curr_streak;
    struct text max_streak;
    struct text score;
    struct text max_score;
};

typedef struct duck_coor s_duck_coor;
typedef struct texts_display s_tdisplay;
typedef struct sound_effect s_seffect;
typedef struct sounds s_sounds;
typedef struct variables s_var;
typedef struct all_s s_all_s;
typedef struct sprite s_sprite;
typedef struct text s_text;
int readme(int ac, char **av);
void anim_button(sfRenderWindow *win, s_all_s *d);
void actualise_volume(s_var *va);
void actualise_text(s_tdisplay *texts, s_var *va);
int check_button(sfRenderWindow *, sfEvent *, s_all_s *, s_var *);
void fill_menu(s_all_s *all_s);
void pause_menu(sfRenderWindow *win, s_var *va, s_all_s *d);
void fill_sounds(s_sounds *sounds);
void fill_text(s_tdisplay *tdis);
void fill_var(s_var *va, int beg);
int check_shot(sfMouseButtonEvent *event, s_all_s *ducks, s_var *);
void error_sound(s_sounds *sounds);
void book_sound(s_sounds *sounds);
void button_sound(s_sounds *sounds);
void reload_sound(s_sounds *sounds);
void empty_shot(s_sounds *s);
void shotgun_shot(s_sounds *s);
void fill_ducks(s_all_s *all_s);
void move_ducks(s_all_s *all_s, s_var *va, sfClock *clock, sfRenderWindow *w);
void animation(sfClock *clock, s_all_s *ducks, s_var *va);
void music(s_sounds *);
void analyse_events(sfEvent *, sfRenderWindow *, s_var *, s_all_s *);
void anim_shot(s_all_s *ducks, s_var *va);
void destroy(s_tdisplay *tdisplay, s_all_s *a, s_var *va);
void game_loop(sfRenderWindow *win, int beg);
int pfmy_compute_power_rec(int nb, int p);
int my_len_nbr(int nb);
void destroy_sprites(s_all_s *a);
void destroy_variables(s_var *va);
int my_getnbr(char const *str, int a);
int my_strlen(char const *str);
void save(s_var *va);

#endif /* SFML_GRAPHICS_TYPES_H */
