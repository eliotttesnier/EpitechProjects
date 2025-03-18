/*
** EPITECH PROJECT, 2025
** ASM
** File description:
** tests_syscall
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>

extern long syscall(long number, ...);

Test(syscall, write_test)
{
    char str[] = "Hello";
    cr_redirect_stdout();
    long ret = syscall(SYS_write, STDOUT_FILENO, str, 5);
    cr_assert_eq(ret, 5);
    cr_assert_stdout_eq_str("Hello");
}

Test(syscall, read_test)
{
    char buffer[6] = {0};
    // First open the file for writing
    int fd = open("tests/test_file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(fd, "Test!", 5);
    close(fd);

    // Then open it for reading
    fd = open("tests/test_file.txt", O_RDONLY);
    long ret = syscall(SYS_read, fd, buffer, 5);
    close(fd);

    cr_assert_eq(ret, 5);
    cr_assert_str_eq(buffer, "Test!");

    unlink("tests/test_file.txt");
}

Test(syscall, getpid_test)
{
    long pid = syscall(SYS_getpid);
    cr_assert_gt(pid, 0);
    cr_assert_eq(pid, getpid());
}
