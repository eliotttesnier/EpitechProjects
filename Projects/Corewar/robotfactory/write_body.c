/*
** EPITECH PROJECT, 2024
** write_body.c
** File description:
** write the body
*/

#include "include/robot_header.h"

void write_param(int param, int byte, int cor_fd)
{
    char param_char = -1;
    short param_short = -1;
    int param_int = -1;

    if (byte == 1) {
        param_char = (char)param;
        write(cor_fd, &param_char, sizeof(char));
    }
    if (byte == 2) {
        param_short = (short)param;
        if (check_endian() == true)
            param_short = little_to_big_s(param_short);
        write(cor_fd, &param_short, sizeof(short));
    }
    if (byte == 4) {
        param_int = (int)param;
        if (check_endian() == true)
            param_int = little_to_big_u(param_int);
        write(cor_fd, &param_int, sizeof(int));
    }
}

void write_instruction(body_t *instru, int cor_fd)
{
    char code = (char)instru->code;
    char codingbyte = (char)instru->codingbyte;

    write(cor_fd, &code, sizeof(char));
    if (code != 1 && code != 9 && code != 12 && code != 15)
        write(cor_fd, &codingbyte, sizeof(char));
    if (instru->param1 != -1)
        write_param(instru->param1, instru->bytes1, cor_fd);
    if (instru->param2 != -1)
        write_param(instru->param2, instru->bytes2, cor_fd);
    if (instru->param3 != -1)
        write_param(instru->param3, instru->bytes3, cor_fd);
}

void write_body(body_t **body_arr, int cor_fd)
{
    for (int i = 0; body_arr[i] != NULL; i++) {
        write_instruction(body_arr[i], cor_fd);
    }
}
