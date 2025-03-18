/*
** EPITECH PROJECT, 2023
** unit_tests
** File description:
** tests for sort
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "header.h"

direction_t *create_dir(int front, int rf, int right, int lf, int left)
{
    direction_t *new = malloc(sizeof(direction_t) * 1);

    new->front = front;
    new->left = left;
    new->right = right;
    new->lf = lf;
    new->rf = rf;
    return (new);
}

Test(is_biggest, front)
{
    direction_t *dir = create_dir(1000, 800, 800, 800, 800);

    cr_assert_eq(is_biggest(dir, dir->front), true);
}

Test(is_biggest, right)
{
    direction_t *dir = create_dir(800, 800, 1000, 800, 800);

    cr_assert_eq(is_biggest(dir, dir->right), true);
}

Test(is_biggest, left)
{
    direction_t *dir = create_dir(800, 800, 800, 800, 1000);

    cr_assert_eq(is_biggest(dir, dir->left), true);
}

Test(is_biggest, rf)
{
    direction_t *dir = create_dir(800, 1000, 800, 800, 800);

    cr_assert_eq(is_biggest(dir, dir->rf), true);
}

Test(is_biggest, lf)
{
    direction_t *dir = create_dir(800, 800, 800, 1000, 800);

    cr_assert_eq(is_biggest(dir, dir->lf), true);
}

Test(calc_direction, neutral)
{
    direction_t *dir = create_dir(1000, 800, 800, 800, 800);

    cr_assert_eq(calc_direction(dir), 0.00);
}

Test(calc_direction, right)
{
    direction_t *dir = create_dir(800, 800, 1000, 800, 800);

    cr_assert_eq(calc_direction(dir), -0.5);
}

Test(calc_direction, left)
{
    direction_t *dir = create_dir(800, 800, 800, 800, 1000);

    cr_assert_eq(calc_direction(dir), 0.5);
}

Test(calc_direction, rf)
{
    direction_t *dir = create_dir(800, 1000, 800, 800, 800);

    cr_assert_eq(calc_direction(dir), -0.25);
}

Test(calc_direction, lf)
{
    direction_t *dir = create_dir(800, 800, 800, 1000, 800);

    cr_assert_eq(calc_direction(dir), 0.25);
}

Test(calc_direction, close_wall_right)
{
    direction_t *dir = create_dir(1000, 800, 1000, 800, 400);

    cr_assert_eq(calc_direction(dir), -0.25);
}

Test(calc_direction, close_wall_left)
{
    direction_t *dir = create_dir(1000, 800, 400, 800, 1000);

    cr_assert_eq(calc_direction(dir), 0.25);
}

Test(calc_backwards, no_backward)
{
    cr_assert_eq(calc_backwards(500, 500, 500), 0);
}

Test(calc_backwards, backward_front)
{
    cr_assert_eq(calc_backwards(500, 500, 10), -0.5);
}

Test(calc_backwards, backward_right)
{
    cr_assert_eq(calc_backwards(500, 10, 500), -0.5);
}

Test(calc_backwards, backward_left)
{
    cr_assert_eq(calc_backwards(10, 500, 500), -0.5);
}

Test(calc_speed, straight)
{
    direction_t *dir = create_dir(1000, 1000, 1000, 1000, 1000);

    cr_assert_eq(calc_speed(dir, 0.0), 0.5);
}
