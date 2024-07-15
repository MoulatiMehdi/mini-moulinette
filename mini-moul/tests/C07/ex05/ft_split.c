#include "../../../../ex05/ft_split.c"
#include "../../../utils/constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_test
{
	char	*desc;
	char	*str;
	char	*charset;
	char	**expected;
}			t_test;

int			run_tests(t_test *tests, int count);

int	main(void)
{
	int	count;

	t_test tests[] = {
		{
			.desc = "Basic split with single character separator",
			.str = "hello,world,how,are,you",
			.charset = ",",
			.expected = (char *[]){"hello", "world", "how", "are", "you", NULL},
		},
		{
			.desc = "Split with multiple character separator",
			.str = "apple##banana##cherry##date",
			.charset = "##",
			.expected = (char *[]){"apple", "banana", "cherry", "date", NULL},
		},
		{
			.desc = "Split with multiple different separators",
			.str = "one,two;three:four",
			.charset = ",;:",
			.expected = (char *[]){"one", "two", "three", "four", NULL},
		},
		{
			.desc = "Empty string",
			.str = "",
			.charset = ",",
			.expected = (char *[]){NULL},
		},
		{
			.desc = "No separators in string",
			.str = "hello",
			.charset = ",",
			.expected = (char *[]){"hello", NULL},
		},
		{
			.desc = "Empty charset",
			.str = "hello,world",
			.charset = "",
			.expected = (char *[]){"hello,world", NULL},
		},
		{
			.desc = "String with only separators",
			.str = ",,,,",
			.charset = ",",
			.expected = (char *[]){NULL},
		},
		{
			.desc = "String starting and ending with separators",
			.str = ",hello,world,",
			.charset = ",",
			.expected = (char *[]){"hello", "world", NULL},
		},
		{
			.desc = "Multiple consecutive separators",
			.str = "one,,two,,,three",
			.charset = ",",
			.expected = (char *[]){"one", "two", "three", NULL},
		},
		{
			.desc = "Split with whitespace separators",
			.str = "  hello   world  how are   you  ",
			.charset = " ",
			.expected = (char *[]){"hello", "world", "how", "are", "you", NULL},
		},
		{
			.desc = "Split with tab and newline separators",
			.str = "line1\tword1\nline2\tword2",
			.charset = "\t\n",
			.expected = (char *[]){"line1", "word1", "line2", "word2", NULL},
		},
		{
			.desc = "Split with all ASCII separators",
			.str = "a!b\"c#d$e%f&g'h(i)j*k+l,m-n.o/p:q;r<s=t>u?v@w[x]y{z}",
			.charset = "!\"#$%&'()*+,-./:;<=>?@[]{}",
			.expected = (char *[]){"a", "b", "c", "d", "e", "f", "g", "h", "i",
				"j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v",
				"w", "x", "y", "z", NULL},
		},
		{
			.desc = "Long string with few separators",
			.str = "This is a very long string with only a few separators to test memory allocation",
			.charset = "x",
			.expected = (char *[]){"This is a very long string with only a few separators to test memory allocation",
				NULL},
		},
		{
			.desc = "Unicode separators",
			.str = "hello世界how你好are你好you",
			.charset = "世界你好",
			.expected = (char *[]){"hello", "how", "are", "you", NULL},
		},
		{
			.desc = "Empty string with empty charset",
			.str = "",
			.charset = "",
			.expected = (char *[1]){0},
		},
		{
			.desc = "Single-word string with empty charset",
			.str = "hello",
			.charset = "",
			.expected = (char *[2]){"hello", 0},
		},
		{
			.desc = "String with leading and trailing separators",
			.str = ",,hello,world,,",
			.charset = ",",
			.expected = (char *[3]){"hello", "world", 0},
		},
		{
			.desc = "String with multiple consecutive separators",
			.str = "hello,,,,world",
			.charset = ",",
			.expected = (char *[3]){"hello", "world", 0},
		},
		{
			.desc = "String with repeated separators",
			.str = "aaabbbaaaccc",
			.charset = "ab",
			.expected = (char *[]){"ccc", 0},
		},
	};
	count = sizeof(tests) / sizeof(tests[0]);
	return (run_tests(tests, count));
}

int	run_tests(t_test *tests, int count)
{
	int		i;
	int		error;
	char	**result;
	int		j;

	error = 0;
	for (i = 0; i < count; i++)
	{
		result = ft_split(tests[i].str, tests[i].charset);
		
		if (!result[0] && !tests[i].expected[0])
			printf(GREEN CHECKMARK GREY " [%d] %s\n" DEFAULT, i + 1,tests[i].desc);
		
		else if (!result[0] || !tests[i].expected[0])
		{
			printf(RED "[%d] %s got \"", i + 1, tests[i].desc);
			if (result[0])
			{
				printf("%s", result[0]);
				for (int j = 1; result[j]; j++)
				{
					printf("\", \"%s", result[j]);
				}
			}
			else
				printf("(null)");
			
			printf("\" instead of \"");
			if (tests[i].expected[0])
			{
				printf("%s", tests[i].expected[0]);
				for (int j = 1; tests[i].expected[j]; j++)
				{
					printf("\", \"%s", tests[i].expected[j]);
				}
			}
			else
				printf("(null)");
			
			printf("\"\n" DEFAULT);
			error -= 1;
		}
		else
	{
			j = 0;
			while (tests[i].expected[j] && result[j])
			{
				if (strcmp(tests[i].expected[j], result[j]) != 0)
				{
	  printf(RED "[%d] %s Element %d: expected \"%s\",got \"%s\"\n" DEFAULT, i + 1, tests[i].desc, j,tests[i].expected[j], result[j]);
					error -= 1;
					break ;
				}
				j++;
			}
			if (tests[i].expected[j] != result[j])
			{
				printf(RED "[%d] %s got \"", i + 1, tests[i].desc);
				if (result[0])
				{
					printf("%s", result[0]);
					for (int j = 1; result[j]; j++)
					{
						printf("\", \"%s", result[j]);
					}
				}
				else
			{
					printf("(null)");
				}
				printf("\" instead of \"");
				if (tests[i].expected[0])
				{
					printf("%s", tests[i].expected[0]);
					for (int j = 1; tests[i].expected[j]; j++)
					{
						printf("\", \"%s", tests[i].expected[j]);
					}
				}
				else
			{
					printf("(null)");
				}
				printf("\"\n" DEFAULT);
				error -= 1;
			}
			else
		{
	  printf(GREEN CHECKMARK GREY " [%d] %s got \"", i + 1,tests[i].desc);
				if (result[0])
				{
					printf("%s", result[0]);
					for (int j = 1; result[j]; j++)
					{
						printf("\", \"%s", result[j]);
					}
				}
				printf("\" as expected\n" DEFAULT);
			}
		}
		if (result[0])
		{
			j = 0;
			while (result[j])
			{
				free(result[j]);
				j++;
			}
			free(result);
		}
	}
	return (error);
}
