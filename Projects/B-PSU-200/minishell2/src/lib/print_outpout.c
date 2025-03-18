/*
** EPITECH PROJECT, 2024
** len_first_error
** File description:
** len_first_error
*/

#include "../../includes/header.h"

int print_outpout(int ret)
{
    char *str = strerror(errno);

    if (ret == 129)
        write(2, "[Segmentation fault]", 21);
    if (ret == 0)
        return (0);
    for (int i = 0; str[i] != '\0'; i++) {
        if (i != 0 && str[i] >= 'A' && str[i] <= 'Z')
            break;
        write(1, &str[i], 1);
    }
    write(1, "\n", 1);
    return (ret);
}
