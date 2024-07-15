#include "../../../../ex03/ft_strjoin.c"
#include "../../../utils/constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_test
{
	char	*desc;
	int		size;
	char	**strs;
	char	*sep;
	char	*expected;
}			t_test;

int			run_tests(t_test *tests, int count);

int	main(void)
{
	int	count;

	t_test tests[] = {
		{
			.desc = "Basic join with comma separator",
			.size = 3,
			.strs = (char *[]){"Hello", "world", "!"},
			.sep = ",",
			.expected = "Hello,world,!",
		},
		{
			.desc = "Join with space separator",
			.size = 4,
			.strs = (char *[]){"This", "is", "a", "test"},
			.sep = " ",
			.expected = "This is a test",
		},
		{
			.desc = "Join with empty separator",
			.size = 3,
			.strs = (char *[]){"abc", "def", "ghi"},
			.sep = "",
			.expected = "abcdefghi",
		},
		{
			.desc = "Join single string",
			.size = 1,
			.strs = (char *[]){"loneliness"},
			.sep = "***",
			.expected = "loneliness",
		},
		{
			.desc = "Join empty strings",
			.size = 3,
			.strs = (char *[]){"", "", ""},
			.sep = ",",
			.expected = ",,",
		},
		{
			.desc = "Zero size",
			.size = 0,
			.strs = NULL,
			.sep = ",",
			.expected = "",
		},
		{
			.desc = "Join with long separator",
			.size = 3,
			.strs = (char *[]){"one", "two", "three"},
			.sep = " --- ",
			.expected = "one --- two --- three",
		},
		{
			.desc = "Join many short strings",
			.size = 10,
			.strs = (char *[]){"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"},
			.sep = "-",
			.expected = "a-b-c-d-e-f-g-h-i-j",
		},
		{
			.desc = "Join with newline separator",
			.size = 3,
			.strs = (char *[]){"Line 1", "Line 2", "Line 3"},
			.sep = "\n",
			.expected = "Line 1\nLine 2\nLine 3",
		},
		{
			.desc = "Join with tab separator",
			.size = 4,
			.strs = (char *[]){"Column1", "Column2", "Column3", "Column4"},
			.sep = "\t",
			.expected = "Column1\tColumn2\tColumn3\tColumn4",
		},
		{
			.desc = "Join strings of varying lengths",
			.size = 5,
			.strs = (char *[]){"", "a", "ab", "abc", "abcd"},
			.sep = ",",
			.expected = ",a,ab,abc,abcd",
		},
		{
			.desc = "Join with Unicode separator",
			.size = 3,
			.strs = (char *[]){"Hello", "世界", "!"},
			.sep = "•",
			.expected = "Hello•世界•!",
		},

		{.desc = "ft_strjoin with size 1", .size = 1,
			.strs = (char *[]){"Hello"}, .sep = ",", .expected = "Hello"},
		{.desc = "ft_strjoin with size 3", .size = 3,
			.strs = (char *[]){"Hello", "world", "!"}, .sep = ", ",
			.expected = "Hello, world, !"},
		{.desc = "ft_strjoin with size 4 and empty strings", .size = 4,
			.strs = (char *[]){"", "Hello", "", "world"}, .sep = "-",
			.expected = "-Hello--world"},
		{.desc = "ft_strjoin with size 2 and empty separator", .size = 2,
			.strs = (char *[]){"Hello", "world"}, .sep = "",
			.expected = "Helloworld"},
		{.desc = "ft_strjoin with size 0", .size = 0, .strs = NULL, .sep = ",",
			.expected = ""},
	};
	count = sizeof(tests) / sizeof(tests[0]);
	return (run_tests(tests, count));
}

int	run_tests(t_test *tests, int count)
{
	int		i;
	int		error;
	char	*result;

	error = 0;
	for (i = 0; i < count; i++)
	{
		result = ft_strjoin(tests[i].size, tests[i].strs, tests[i].sep);
		if (strcmp(result, tests[i].expected) != 0)
		{
			printf("    " RED "[%d] %s Expected \"%s\", got \"%s\"\n", i + 1,tests[i].desc, tests[i].expected, result);
			error -= 1;
		}
		else
		printf("  " GREEN CHECKMARK GREY " [%d] %s Expected \"%s\",	got \"%s\"\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected,	result);
		free(result);
	}
	return (error);
}
