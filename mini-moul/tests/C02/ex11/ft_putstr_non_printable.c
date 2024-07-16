#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "../../../../ex11/ft_putstr_non_printable.c"
#include "../../../utils/constants.h"
#include <ctype.h>
#include <sys/stat.h>


// Function prototype
void *ft_print_memory(void *addr, unsigned int size);

// Test case structure
typedef struct {
    char *desc;
    void *addr;
    unsigned int size;
    char *expected_output;
} t_test;

// Function to compare output ignoring addresses
int compare_output_ignore_address(const char *expected, const char *actual) {
    const char *exp_ptr = expected;
    const char *act_ptr = actual;

    while (*exp_ptr && *act_ptr) {
        // Skip over the address part in both strings
        exp_ptr = strchr(exp_ptr, ':');
        act_ptr = strchr(act_ptr, ':');

        if (!exp_ptr || !act_ptr) {
            return 0;  // Mismatch in format
        }

        exp_ptr++;  // Move past the ':'
        act_ptr++;  // Move past the ':'

        // Compare the rest of the line
        while (*exp_ptr != '\n' && *act_ptr != '\n') {
            if (*exp_ptr != *act_ptr) {
                return 0;  // Mismatch in content
            }
            exp_ptr++;
            act_ptr++;
        }

        // Both should be at a newline now
        if (*exp_ptr != *act_ptr) {
            return 0;  // Mismatch in line ending
        }

        // Move to next line
        exp_ptr++;
        act_ptr++;
    }

    // Both strings should end at the same time
    return (*exp_ptr == *act_ptr);
}

// Function to run tests
int run_tests(t_test *tests, int count)
{
    int i;
    int error = 0;
    for (i = 0; i < count; i++)
    {
        fflush(stdout);
        char buffer[4096];
        memset(buffer, 0, sizeof(buffer));

        int saved_stdout = dup(STDOUT_FILENO);
        int output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);

        ft_print_memory(tests[i].addr, tests[i].size);

        fflush(stdout);
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);

        FILE *fp = fopen("output.txt", "r");
        size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, fp);
        buffer[bytes_read] = '\0';
        fclose(fp);

        if (!compare_output_ignore_address(tests[i].expected_output, buffer))
        {
            printf("    " RED "[%d] %s\n", i + 1, tests[i].desc);
            printf("Expected output:\n%s\n", tests[i].expected_output);
            printf("Got output:\n%s\n" DEFAULT, buffer);
            error -= 1;
        }
        else
            printf("  " GREEN CHECKMARK GREY " [%d] %s output as expected\n" DEFAULT, i + 1, tests[i].desc);

        remove("output.txt");
    }
    return error;
}

int main()
{
    char test_str[] = "Bonjour les aminches\t\n\tc\a est fou\ttout\tce qu on peut faire avec\t\n\tprint_memory\n\n\n\tlol.lol\n ";

    t_test tests[] = {
        {
            "Basic test",
            test_str,
            strlen(test_str),
            "00000000: 426f 6e6a 6f75 7220 6c65 7320 616d 696e Bonjour les amin\n"
            "00000010: 6368 6573 090a 0963 0720 6573 7420 666f ches...c. est fo\n"
            "00000020: 7509 746f 7574 0963 6520 7175 206f 6e20 u.tout.ce qu on \n"
            "00000030: 7065 7574 2066 6169 7265 2061 7665 6309 peut faire avec.\n"
            "00000040: 0a09 7072 696e 745f 6d65 6d6f 7279 0a0a ..print_memory..\n"
            "00000050: 0a09 6c6f 6c2e 6c6f 6c0a 2000            ..lol.lol. .\n"
        },
        {
            "Empty string",
            "",
            0,
            ""
        },
        {
            "Short string",
            "Hello",
            5,
            "00000000: 4865 6c6c 6f                           Hello\n"
        }
    };

    int test_count = sizeof(tests) / sizeof(t_test);
    int errors = run_tests(tests, test_count);

    if (errors == 0)
        printf(GREEN "All tests passed!\n" DEFAULT);
    else
        printf(RED "%d test(s) failed.\n" DEFAULT, -errors);

    return 0;
}
