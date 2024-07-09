#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include "../../../../ex04/ft_fibonacci.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    int n;
    int expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
        {
            .desc = "Fibonacci of 0",
            .n = 0,
            .expected = 0,
        },
        {
            .desc = "Fibonacci of 1",
            .n = 1,
            .expected = 1,
        },
        {
            .desc = "Fibonacci of 2",
            .n = 2,
            .expected = 1,
        },
        {
            .desc = "Fibonacci of 5",
            .n = 5,
            .expected = 5,
        },
        {
            .desc = "Fibonacci of a negative number",
            .n = -5,
            .expected = -1,
        },
        {
            .desc = "Biggest Fibonacci number in int range",
            .n = 46,
            .expected = 1836311903,
        },
        {
            .desc = "Fibonacci of the Biggest negative number in int",
            .n = INT_MIN,
            .expected = -1,
        },
        // Add more test cases here
    };
    int count = sizeof(tests) / sizeof(tests[0]);

    return run_tests(tests, count);
}

int run_tests(t_test *tests, int count)
{
    int i;
    int error = 0;

    for (i = 0; i < count; i++)
    {
        if(i == count - 2)
            printf("\t\t" CYAN "===> It will takes few seconds... <===\n");
        int result = ft_fibonacci(tests[i].n);

        if (result != tests[i].expected)
        {
            printf("\t" RED "[%d] %s Expected %d, got %d\n", i + 1, tests[i].desc, tests[i].expected, result);
            error -= 1;
        }
        else
    {
            printf("  " GREEN CHECKMARK GREY " [%d] %s Expected %d, got %d\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, result);
        }
    }

    return error;
}
