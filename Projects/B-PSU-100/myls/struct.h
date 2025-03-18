/*
** EPITECH PROJECT, 2023
** struct
** File description:
** used to define a struct
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

    #include <time.h>
    #include <sys/stat.h>
    #include <sys/sysmacros.h>
    #include <fcntl.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <sys/types.h>
    #include <dirent.h>

struct mods {
    int a;
    int l;
    int R;
    int d;
    int r;
    int t;
};

int non_existing_secu(char **arr, int nb_paths, int *i);
int check_existing(char *check);
void reverse_file(char **files, int nb_files);
void tree_tflag(char **files, int nb_files, char *path);
void displays_time(struct stat *sb);
void displays_group_name(char **files, int nb_files, char *p, int a);
void displays_name(char **files, int nb_files, char *p, int a);
void get_stats(char *file, char *path, struct stat *sb);
void displays_perms(int mode);
void displays_size(char **files, int nb_files, char *p, int size);
void fill_struct(struct mods *modifiers, char **av, int ac);
int cal_paths(int ac, char **av);
int cal_len_max(int ac, char **av);
void fill_arr(char **av, char **arr, int nb_paths);
int call_cal_file(char *str, struct mods *modifiers);
int call_file_len(char *str, struct mods *modifiers);
void call_fill_file(char *p, char **f, int nb_f, struct mods *mods);
char lower(char c);
int swap_files(char **files, int a, int b);
int compares(char **files, int a, int b);
int tree_file(char **files, int nb_files);
void call_display(char **f, int nb_f, struct mods *m, char *p);

#endif /* STRUCT_H_ */
