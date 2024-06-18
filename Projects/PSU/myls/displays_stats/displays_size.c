/*
** EPITECH PROJECT, 2023
** displays_size
** File description:
** display the -l
*/

#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../struct.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "../myprintf/include/my.h"

void displays_size(char **files, int nb_files, char *p, int size)
{
    struct stat sb;
    int max_len = 0;
    int actual_len = 0;

    for (int i = 0; i < nb_files; i++) {
        get_stats(files[i], p, &sb);
        if (max_len < my_len_nbr(sb.st_size))
            max_len = my_len_nbr(sb.st_size);
    }
    actual_len = my_len_nbr(size);
    for (int i = 0; i <= max_len - actual_len - 1; i++) {
        my_printf(" ");
    }
    my_printf("%i ", size);
}
