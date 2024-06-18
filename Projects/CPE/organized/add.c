/*
** EPITECH PROJECT, 2023
** add
** File description:
** add to the chained list
*/

#include "libshell/shell.h"

static int verif_wire(char *wire, char *str)
{
    for (int i = 0; i < 4; i++) {
        if (str[i] != wire[i])
            return (0);
    }
    return (1);
}

static int verif_sensor(char *sensor, char *str)
{
    for (int i = 0; i < 6; i++) {
        if (str[i] != sensor[i])
            return (0);
    }
    return (1);
}

static int verif_processor(char *processor, char *str)
{
    for (int i = 0; i < 9; i++) {
        if (str[i] != processor[i])
            return (0);
    }
    return (1);
}

static int verif_device(char *device, char *str)
{
    for (int i = 0; i < 6; i++) {
        if (str[i] != device[i])
            return (0);
    }
    return (1);
}

static int verif_actuator(char *actuator, char *str)
{
    for (int i = 0; i < 8; i++) {
        if (str[i] != actuator[i])
            return (0);
    }
    return (1);
}

int verif(char *str)
{
    int verif = 0;
    int len = pfmy_strlen(str);
    char actuator[9] = "ACTUATOR";
    char device[7] = "DEVICE";
    char processor[10] = "PROCESSOR";
    char sensor[7] = "SENSOR";
    char wire[5] = "WIRE";

    if (len == 8)
        verif += verif_actuator(actuator, str);
    if (len == 6)
        verif += verif_device(device, str);
        verif += verif_sensor(sensor, str);
    if (len == 9)
        verif += verif_processor(processor, str);
    if (len == 4)
        verif += verif_wire(wire, str);
    if (verif == 1)
        return (0);
    return (-1);
}

int add_error_case(char **args)
{
    int nb_args = 0;

    for (nb_args = 0; args[nb_args] != NULL; nb_args++);
    if (nb_args == 0 || nb_args % 2 != 0)
        return (-1);
    for (int i = 0; i < nb_args; i += 2) {
        if (verif(args[i]) == -1)
            return (-1);
    }
    return (nb_args);
}

int adding(void *data, char *type, char *name)
{
    llist_t *newnode = malloc(sizeof(llist_t));

    if (newnode == NULL)
        return (84);
    ((organiz *)data)->max_id += 1;
    newnode->id = ((organiz *)data)->max_id;
    newnode->type = malloc(25);
    newnode->name = malloc(25);
    if (newnode->type == NULL || newnode->name == NULL)
        return (84);
    my_strcpy(newnode->type, type);
    my_strcpy(newnode->name, name);
    newnode->next = ((organiz *)data)->list;
    ((organiz *)data)->list = newnode;
    my_printf("%s ", newnode->type);
    my_printf("n°%i - ", newnode->id);
    my_printf("\"%s\" added.\n", newnode->name);
}

int add(void *data, char **args)
{
    int nb_args = add_error_case(args);

    if (nb_args == -1)
        return (84);
    for (int i = 0; i < nb_args; i += 2) {
        if (adding(data, args[i], args[i + 1]) == 84)
            return (84);
    }
    return (0);
}
