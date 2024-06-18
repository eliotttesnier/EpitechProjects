/*
** EPITECH PROJECT, 2024
** COREWAR
** File description:
** build_map
*/

#include "corewar_header.h"

int get_instructions(int fd, prog_t *prog, int size)
{
    int i = 0;
    unsigned char byte = 0;

    prog->prog = malloc(sizeof(unsigned char) * size);
    if (read(fd, &byte, sizeof(unsigned char)) <= 0)
        return (-1);
    prog->prog[i] = byte;
    for (i = 1; read(fd, &byte, sizeof(unsigned char)) > 0; i++) {
        prog->prog[i] = byte;
    }
    prog->next = NULL;
    prog->first_time = true;
    prog->carry = true;
    prog->alive = false;
    prog->reg[0] = prog->id;
    return (i);
}

int check_validity(header_t *header, prog_t *prog)
{
    if (header->magic != COREWAR_EXEC_MAGIC)
        return (my_perror("Warrior: Invalid magic number.\n", 84));
    if (my_strlen(header->prog_name) < 1)
        return (my_perror("Warrior: Invalid name.\n", 84));
    if (my_strlen(header->comment) < 1)
        return (my_perror("Warrior: Invalid comment.\n", 84));
    if (prog->size < 1 || header->prog_size < 1)
        return (my_perror("Warrior: No instructions.\n", 84));
    if (prog->pc < 0 || prog->pa < 0)
        return (my_perror("Wariror: Invalid position.\n", 84));
    if (prog->prog[0] < 1 || prog->prog[0] > 16)
        return (my_perror("Warrior: Invalid instruction.\n", 84));
    free(header);
    return (0);
}

prog_t *build_prog(char *path, int pa, int id)
{
    prog_t *new_prog = malloc(sizeof(prog_t));
    header_t *header = malloc(sizeof(header_t));
    int fd = open(path, O_RDONLY);

    read(fd, header, sizeof(header_t));
    header->magic = little_to_big_u(header->magic);
    header->prog_size = little_to_big_u(header->prog_size);
    new_prog->freeze_cycle = 0;
    new_prog->pa = pa;
    new_prog->pc = pa;
    new_prog->name = my_strdup(header->prog_name);
    for (int i = 0; i < REG_NUMBER; i++) {
        new_prog->reg[i] = 0;
    }
    new_prog->id = id;
    new_prog->size = get_instructions(fd, new_prog, header->prog_size);
    close(fd);
    return (check_validity(header, new_prog) == 84 ? NULL : new_prog);
}

map_t *build_map(int nb_prog, int cycle)
{
    map_t *vm = malloc(sizeof(map_t));

    vm->nb_prog = nb_prog;
    vm->nb_live = 0;
    vm->cycle = cycle;
    vm->programs = malloc(sizeof(prog_t) * (nb_prog + 1));
    for (int i = 0; i < 6144; i++) {
        vm->map[i] = 0;
        vm->idmap[i] = -1;
    }
    return (vm);
}
