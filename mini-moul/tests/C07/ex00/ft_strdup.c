#include "../../../../ex00/ft_strdup.c"
#include "../../../utils/constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_test
{
	char	*desc;
	char	*src;
	char	*expected;
}			t_test;

int			run_tests(t_test *tests, int count);

int	main(void)
{
	int	count;

	t_test tests[] = {
		{
			.desc = "Basic string duplication",
			.src = "Hello, world!",
			.expected = "Hello, world!",
		},
		{
			.desc = "Empty string",
			.src = "",
			.expected = "",
		},
		{
			.desc = "String with spaces",
			.src = "   Spaces   at   both   ends   ",
			.expected = "   Spaces   at   both   ends   ",
		},
		{
			.desc = "String with special characters",
			.src = "!@#$%^&*()_+{}[]|\\:;\"'<>,.?/",
			.expected = "!@#$%^&*()_+{}[]|\\:;\"'<>,.?/",
		},
		{
			.desc = "Long string",
			.src = "This is a very long string that is meant to test the memory allocation for larger inputs. It should be correctly duplicated without any issues.",
			.expected = "This is a very long string that is meant to test the memory allocation for larger inputs. It should be correctly duplicated without any issues.",
		},
		{
			.desc = "String with null characters",
			.src = "Hello\0World",
			.expected = "Hello",
		},
		{
			.desc = "String with newline characters",
			.src = "Line 1\nLine 2\nLine 3",
			.expected = "Line 1\nLine 2\nLine 3",
		},
		{
			.desc = "String with tab characters",
			.src = "Column1\tColumn2\tColumn3",
			.expected = "Column1\tColumn2\tColumn3",
		},
		{
			.desc = "String with non-ASCII characters",
			.src = "こんにちは世界",
			.expected = "こんにちは世界",
		},
		{
			.desc = "String with mixed ASCII and non-ASCII",
			.src = "Hello, 世界!",
			.expected = "Hello, 世界!",
		},
		{.desc = "ft_strdup with empty string", .src = "", .expected = ""},
		{.desc = "ft_strdup with non-empty string", .src = "test",
			.expected = "test"},
		{.desc = "ft_strdup with long string",
			.src = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()",
			.expected = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()"},
		{.desc = "ft_strdup with string containing a NULL character",
			.src = "test\0test", .expected = "test"},
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
		result = ft_strdup(tests[i].src);
		if (tests[i].src == NULL && result != NULL)
		{
			printf("    " RED "[%d] %s Expected NULL, got \"%s\"\n" DEFAULT, i
		  + 1, tests[i].desc, result);
			error -= 1;
		}
		else if (tests[i].src == NULL && result == NULL)
		{
			printf("  " GREEN CHECKMARK GREY " [%d]%s output NULL as expected\n" DEFAULT, i + 1, tests[i].desc);
		}
		else if (strcmp(result, tests[i].expected) != 0)
		{
			printf("    " RED "[%d] %s Expected \"%s\", got \"%s\"\n" DEFAULT, i+ 1, tests[i].desc, tests[i].expected, result);
			error -= 1;
		}
		else
		printf("  " GREEN CHECKMARK GREY " [%d]	%s output \"%s\" as expected\n" DEFAULT, i + 1, tests[i].desc,
		 result);
		free(result);
	}
	return (error);
}
