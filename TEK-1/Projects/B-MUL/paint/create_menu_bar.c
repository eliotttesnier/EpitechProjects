/*
** EPITECH PROJECT, 2024
** PAINT
** File description:
** create_menu_bar
*/

#include "include/my_paint_header.h"

s_menubar *create_menubar(void)
{
    s_menubar *menubar = malloc(sizeof(s_menubar));

    menubar->file = create_file_button();
    menubar->help = create_help_button();
    menubar->edition = create_edition_button();
    menubar->redo = create_button("redo.png", NULL);
    menubar->undo = create_button("undo.png", NULL);
    return (menubar);
}
