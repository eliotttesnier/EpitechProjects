/*
** EPITECH PROJECT, 2023
** main
** File description:
** main file
*/

#include "include/header.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "myprintf/include/my.h"

int main(int ac, char **av)
{
    struct stat sb;

    if (ac == 2) {
        if (file_errors(av) == -1)
            return (84);
        return (get_from_file(av));
    }
    if (ac == 3) {
        if (generate_errors(av) == -1)
            return (84);
        return (generate(av));
    }
    return (84);
}
