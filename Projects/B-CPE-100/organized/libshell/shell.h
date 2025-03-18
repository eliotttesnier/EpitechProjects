/*
** EPITECH PROJECT, 2023
** B-CPE-110 : Setting Up Shell
** File description:
** shell.h
*/

#ifndef SHELL_H
    #define SHELL_H

    #include <stdlib.h>
    #include "../myprintf/include/my.h"

typedef struct linked_list_s {
    int id;
    char *name;
    char *type;
    struct linked_list_s *next;
} llist_t;

typedef struct organized {
    int max_id;
    llist_t *list;
} organiz;

int multiple(llist_t *list, char **args, int ind);

int compares_type_r(llist_t *list, char **args, int ind);
int compares_type(llist_t *list, char **args, int ind);
int compares_id_r(llist_t *list);
int compares_id(llist_t *list);
int compares_name(llist_t *list, char **args, int ind);
int compares_name_r(llist_t *list, char **args, int ind);

int sort_name(void *data, char **args);
int sort_name_r(void *data, char **args);
int sort_type_r(void *data, char **args);
int sort_type(void *data, char **args);
int sort_id_r(void *data);
int sort_id(void *data);

void redirect_all_std(void);
int organized(int ac, char **av);
int swap(void *data, int id);
void my_strcpy(char *str, char *tocopy);

// To be implemented
int add(void *data, char **args);
int del(void *data, char **args);
int sort(void *data, char **args);
int disp(void *data, char **args);

// Already implemented
int workshop_shell(void *data);

#endif /* SHELL_H */
