#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../../../ex12/ft_print_memory.c"

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define GREY "\033[0;90m"
#define DEFAULT "\033[0m"
#define CHECKMARK "\xE2\x9C\x93"

// Function prototype
void *ft_print_memory(void *addr, unsigned int size);

// Test case structure
typedef struct {
    char *desc;
    void *addr;
    unsigned int size;
    char *expected_output;
} t_test;

// Function to extract hex and text from output
void extract_hex_and_text(char *output, char *hex, char *text) {
    char *line = strtok(output, "\n");
    while (line) {
        char *colon = strchr(line, ':');
        if (colon) {
            char *space = strchr(colon, ' ');
            if (space) {
                strncat(hex, colon + 2, space - colon - 2);
                strcat(hex, " ");
                strcat(text, space + 1);
            }
        }
        line = strtok(NULL, "\n");
    }
}

int run_tests(t_test *tests, int count);

int main(void)
{
	t_test tests[] = {
		{
			.desc = "Ten Queen ",
			.expected_output = "",
			.size=0,
			.addr="",
		},
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
		// Flush the standard output buffer
		fflush(stdout);

		char buffer[8024];
		// Clear the buffer used to capture the output of the function being tested
		memset(buffer, 0, sizeof(buffer));

		// Redirect the output to a file
		int saved_stdout = dup(STDOUT_FILENO);
		int output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);

		// Call the function to be tested
		int result = ft_ten_queens_puzzle();

		// Restore the original output
		fflush(stdout);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);


		// Open the output file and check its contents
		FILE *fp = fopen("output.txt", "rt");

		int line = 0;

		while(fgets(buffer + 11*line, sizeof(buffer), fp) != NULL)
		{
			line++;
		}

		fclose(fp);

		int test_return = result == tests[i].expected  ;
		int test_output =  strcmp(buffer, tests[i].expected_output)  == 0;  

		if (!test_return || !test_output)
		{
			if(test_return)
			{

				printf(RED"\t[%d] %s\n\t" GREEN CHECKMARK GREY " Return : Expected %d, got %d\n", i + 1, tests[i].desc, tests[i].expected, result);
			}
			else{
				printf("\t" RED "[%d] %s\n\t  Return : Expected %d, got %d\n", i + 1, tests[i].desc, tests[i].expected, result);
			}

			if(test_output){
				printf("\t" GREEN CHECKMARK GREY " Output : Valid\n");
			}
			else{
				printf("\t" RED "  Output : Invalid\n");
			}
			error -= 1;
		}
		else
	{
			printf("  " GREEN CHECKMARK GREY " [%d] %s\n\t" GREEN CHECKMARK GREY " Return : Expected %d, got %d\n\t"GREEN CHECKMARK GREY" Output : Valid\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, result);
		}
	}

	return error;
}
