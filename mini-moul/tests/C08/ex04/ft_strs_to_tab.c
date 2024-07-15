#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ft_stock_str.h"
#include "../../../../ex04/ft_strs_to_tab.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    int ac;
    char **av;
    struct s_stock_str *expected;
} t_test;

int compare_stock_str(struct s_stock_str *result, struct s_stock_str *expected, int size)
{
    for (int i = 0; i < size; i++)
    {
        // Check if sizes are equal
        if (result[i].size != expected[i].size)
        {
            printf("expected : %d  result : %d\n",expected[i].size,result[i].size);
            return 0;
        }

        // Check if str pointers are both NULL or both non-NULL and then compare their contents
        if ((expected[i].str == NULL && result[i].str != NULL) || 
            (expected[i].str != NULL && result[i].str == NULL) ||
            (expected[i].str != NULL && strcmp(result[i].str, expected[i].str) != 0))
        {
            printf("expected : '%s'  result '%s'\n",expected[i].str,result[i].str);
            return 0;
        }

        // Check if copy pointers are both NULL or both non-NULL and then compare their contents
        if ((expected[i].copy == NULL && result[i].copy != NULL) || 
            (expected[i].copy != NULL && result[i].copy == NULL) ||
            (expected[i].copy != NULL && strcmp(result[i].copy, expected[i].copy) != 0))
        {
            printf("expected : '%s'  result: '%s'\n",expected[i].copy,result[i].copy);
            return 0;
        }

    }
    return 1;
}
void free_stock_str(struct s_stock_str *stock, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(stock[i].copy);
    }
    free(stock);
}

int main(void)
{
    printf(CYAN "\t\t====> DON'T FORGET TO INCLUDE THE HEADER IN YOUR FILE <====\n" DEFAULT);

    t_test tests[] = {
        {
            .desc = "Basic case with multiple strings",
            .ac = 3,
            .av = (char *[]){"Hello", "World", "!"},
            .expected = (t_stock_str[]){
                {5, "Hello", "Hello"},
                {5, "World", "World"},
                {1, "!", "!"},
                {0, NULL, NULL}
            },
        },
        {
            .desc = "Empty array (ac = 0)",
            .ac = 0,
            .av = NULL,
            .expected = (t_stock_str[]){{0, NULL, NULL}},
        },
        {
            .desc = "Single empty string",
            .ac = 1,
            .av = (char *[]){""},
            .expected = (t_stock_str[]){
                {0, "", ""},
                {0, NULL, NULL}
            },
        },
        {
            .desc = "Array with empty strings",
            .ac = 3,
            .av = (char *[]){"", "", ""},
            .expected = (t_stock_str[]){
                {0, "", ""},
                {0, "", ""},
                {0, "", ""},
                {0, NULL, NULL}
            },
        },
        {
            .desc = "Strings of varying lengths",
            .ac = 4,
            .av = (char *[]){"a", "ab", "abc", "abcd"},
            .expected = (t_stock_str[]){
                {1, "a", "a"},
                {2, "ab", "ab"},
                {3, "abc", "abc"},
                {4, "abcd", "abcd"},
                {0, NULL, NULL}
            },
        },
        {
            .desc = "Very long string",
            .ac = 1,
            .av = (char *[]){"This is a very long string to test memory allocation"},
            .expected = (t_stock_str[]){
                {52, "This is a very long string to test memory allocation", 
                    "This is a very long string to test memory allocation"},
                {0, NULL, NULL}
            },
        },
        {
            .desc = "Strings with special characters",
            .ac = 3,
            .av = (char *[]){"Hello!", "World?", "Special@#$%"},
            .expected = (t_stock_str[]){
                {6, "Hello!", "Hello!"},
                {6, "World?", "World?"},
                {11, "Special@#$%", "Special@#$%"},
                {0, NULL, NULL}
            },
        },
        {
            .desc = "Strings with spaces",
            .ac = 2,
            .av = (char *[]){"Hello World", "   Spaces   "},
            .expected = (t_stock_str[]){
                {11, "Hello World", "Hello World"},
                {12, "   Spaces   ", "   Spaces   "},
                {0, NULL, NULL}
            },
        },
        {
            .desc = "Negative ac",
            .ac = -1,
            .av = (char *[]){"Should", "not", "process"},
            .expected = NULL,
        },
        // Add more test cases here
    };

    int num_tests = sizeof(tests) / sizeof(t_test);
    int error = 0;
    for (int i = 0; i < num_tests; i++)
    {
        struct s_stock_str *result = ft_strs_to_tab(tests[i].ac, tests[i].av);

        if (!result && !tests[i].expected)
        {
         printf(GREEN CHECKMARK GREY " [%d] %s\n" DEFAULT, i + 1, tests[i].desc);
         }
         else if (!result || !tests[i].expected)
         {
            printf("%p  %p\n",result,tests[i].expected);
            printf(RED "x [%d] %s: One is NULL, the other is not\n" DEFAULT, i + 1, tests[i].desc);
            error++;
        }
        else if (compare_stock_str(result, tests[i].expected, tests[i].ac + 1))
        {
         printf(GREEN CHECKMARK GREY " [%d] %s\n" DEFAULT, i + 1, tests[i].desc);
         }
         else
         {
            printf(RED "x [%d] %s: Structures do not match\n" DEFAULT, i + 1, tests[i].desc);
            error++;
        }

        if (result)
        {
            free_stock_str(result, tests[i].ac + 1);
        }
    }

    return error;
}
