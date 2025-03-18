#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int mysh = 0;

    system("make re");
    mysh = system("echo \"ls nofile\" | ./mysh arg");
    printf("MYSH value -> %i\n", mysh);
    //cr_assert_stdout_eq_str("foo");
    //cr_assert_eq(result, 0);
    return (mysh);
}
