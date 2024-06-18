/*
** EPITECH PROJECT, 2024
** header
** File description:
** header file
*/

#pragma once

#include "my_lib.h"
#include "macro.h"
#include "op.h"

typedef struct prog_pars_s {
    char *path;
    int load;
    int id;
    struct prog_pars_s *next;
} prog_pars_t;

typedef struct args_s {
    char *arg;
    bool valor;
    bool flag;
    bool path;
    int id;
    struct args_s *next;
} args_t;

typedef struct argument_s {
    int cycle;
    int nb_programs;
    args_t *args;
    prog_pars_t *progs;
} argument_t;

typedef struct prog_s {
    int id;
    int pa;
    char *name;
    int pc;
    unsigned char reg[REG_NUMBER];
    int freeze_cycle;
    int size;
    unsigned char *prog;
    bool carry;
    bool alive;
    bool first_time;
    struct prog_s *next;
} prog_t;

typedef struct map_s {
    unsigned char map[MEM_SIZE];
    int idmap[MEM_SIZE];
    prog_t **programs;
    prog_t *crt_prog;
    int nb_prog;
    int cycle;
    int nb_live;
} map_t;

typedef int (*call_function_t) (map_t *vm);

int error_cases(int ac, char **av, argument_t *args);
int corewar(int ac, char **av);
int check_for_warriors(argument_t *args);
int check_flags(argument_t *args);
void fill_progs(argument_t *args);
void update_id_prog(argument_t *args);
void update_load_prog(argument_t *args);
void free_arguments(argument_t *args);
int convert_to_binary(char bytecode);
map_t *build_map(int nb_prog, int cycle);
prog_t *build_prog(char *path, int pa, int id);
unsigned int big_to_little(unsigned int num);
unsigned short little_to_big_s(unsigned short num);
unsigned int little_to_big_u(unsigned int num);
void simulate_loop(map_t *vm);
void display_mem(map_t *vm);

//Execution
void exec_programs(map_t *vm);

//Distrib instructions
int short_read(map_t *vm, int i);
int int_read(map_t *vm, int i);
int calc_size_codingbyte(int byte);
int distrib_add(map_t *vm);
int distrib_aff(map_t *vm);
int distrib_and(map_t *vm);
int distrib_fork(map_t *vm);
int distrib_ld(map_t *vm);
int distrib_ldi(map_t *vm);
int distrib_lfork(map_t *vm);
int distrib_live(map_t *vm);
int distrib_lld(map_t *vm);
int distrib_lldi(map_t *vm);
int distrib_or(map_t *vm);
int distrib_st(map_t *vm);
int distrib_sti(map_t *vm);
int distrib_sub(map_t *vm);
int distrib_xor(map_t *vm);
int distrib_zjmp(map_t *vm);

//Exec instructions
void exec_live(map_t *vm, int player_nbr);
void exec_ld(map_t *vm, int value, unsigned char reg_id);
void exec_st_nbr(map_t *vm, int value, int adress);
void exec_st_reg(map_t *vm, int value, unsigned char reg_id);
void exec_add(map_t *vm, int value1, int value2, unsigned char reg_id);
void exec_sub(map_t *vm, int value1, int value2, unsigned char reg_id);
void exec_and(map_t *vm, int value1, int value2, unsigned char reg_id);
void exec_or(map_t *vm, int value1, int value2, unsigned char reg_id);
void exec_xor(map_t *vm, int value1, int value2, unsigned char reg_id);
void exec_zjmp(map_t *vm, int value);
void exec_ldi(map_t *vm, int value1, int value2, unsigned char reg_id);
void exec_sti(map_t *vm, int value1, int value2, int value3);
void exec_fork(map_t *vm, int value);
void exec_lld(map_t *vm, int value, unsigned char reg_id);
void exec_lldi(map_t *vm, int value1, int value2, unsigned char reg_id);
void exec_lfork(map_t *vm, int value);
void exec_aff(map_t *vm, int value);

//Unit tests
bool check_path(char *path);
