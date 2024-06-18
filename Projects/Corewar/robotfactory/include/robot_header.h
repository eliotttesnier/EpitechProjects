/*
** EPITECH PROJECT, 2024
** header
** File description:
** header file
*/

#pragma once

#include "my_lib.h"
#include "op.h"

extern char *instruction_tab[];

typedef struct instruction_s {
    int code;
    int codingbyte;
    int param1;
    int param2;
    int param3;
    int bytes1;
    int bytes2;
    int bytes3;
} body_t;

int create_cor_file(char *file_name);
int open_asm_file(char *file_name);
char **get_head_in_arr(char *buffer);
char **get_body_in_arr(char *buffer);
void format_arr(char **arr);
int find_label(char **body, int i);
int multiple_label(char **body);
int check_header_error(char **head);
int check_body_error(char **body);
int check_all_params(char *instruction, int ind);
int organize_for_compilation(char **head_arr, char **body_arr, char *file);
header_t *setup_header_struct(char **head_arr);
body_t *fill_labeled(char *line);
body_t **setup_body_struct(char **body_arr);
void check_param_size(char **params, body_t *instru, int beg);
int check_endian(void);
unsigned int little_to_big_u(unsigned int num);
short little_to_big_s(short num);
void set_label_args(body_t **instru_tab, char **body);
void write_body(body_t **body_arr, int cor_fd);
int calc_codingbyte(body_t *instru, char **params, int beg);
int check_param_type(char *param);
int is_a_register(char *param);
int is_a_direct(char *param);
int is_a_indirect(char *param);
