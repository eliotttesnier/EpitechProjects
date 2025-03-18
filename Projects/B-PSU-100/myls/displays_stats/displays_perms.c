/*
** EPITECH PROJECT, 2023
** displays_perms
** File description:
** display the -l
*/

#include <time.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../struct.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "../myprintf/include/my.h"

void displays_time(struct stat *sb)
{
    for (int i = 4; i < 7; i++) {
        my_printf("%c", ctime(&sb->st_mtime)[i]);
    }
    my_printf(" ");
    for (int i = 8; i < 16; i++) {
        my_printf("%c", ctime(&sb->st_mtime)[i]);
    }
    my_printf(" ");
}

static void display_type2(int mode)
{
    switch (mode & S_IFMT) {
    case S_IFLNK:
        my_printf("l");
        return;
    case S_IFSOCK:
        my_printf("s");
        return;
    default:
        my_printf("-");
    }
}

static void displays_type(int mode)
{
    switch (mode & S_IFMT) {
    case S_IFBLK:
        my_printf("b");
        return;
    case S_IFCHR:
        my_printf("c");
        return;
    case S_IFDIR:
        my_printf("d");
        return;
    }
    display_type2(mode);
}

void displays_perms(int mode)
{
    displays_type(mode);
    my_printf( (mode & S_IRUSR) ? "r" : "-");
    my_printf( (mode & S_IWUSR) ? "w" : "-");
    my_printf( (mode & S_IXUSR) ? "x" : "-");
    my_printf( (mode & S_IRGRP) ? "r" : "-");
    my_printf( (mode & S_IWGRP) ? "w" : "-");
    my_printf( (mode & S_IXGRP) ? "x" : "-");
    my_printf( (mode & S_IROTH) ? "r" : "-");
    my_printf( (mode & S_IWOTH) ? "w" : "-");
    my_printf( (mode & S_IXOTH) ? "x" : "-");
    my_printf(". ");
}
