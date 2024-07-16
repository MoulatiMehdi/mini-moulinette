#include "../../../../ex04/ft_convert_base.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if __has_include("../../../../ex04/ft_convert_base2.c")
# include "../../../../ex04/ft_convert_base2.c"
#endif
#include "../../../utils/constants.h"

typedef struct s_test
{
	char	*desc;
	char	*nbr;
	char	*base_from;
	char	*base_to;
	char	*expected;
}			t_test;

int			run_tests(t_test *tests, int count);

int	main(void)
{
	int	count;

	t_test tests[] = {
		{
			.desc = "Decimal with invalid character",
			.nbr = "12x34",
			.base_from = "0123456789",
			.base_to = "01",
			.expected = "1100"
		},
		{
			.desc = "Binary with invalid character",
			.nbr = "1011a",
			.base_from = "01",
			.base_to = "0123456789",
			.expected = "11"
		},
		{
			.desc = "Hexadecimal with invalid character",
			.nbr = "FF%G",
			.base_from = "0123456789ABCDEF",
			.base_to = "01234567",
			.expected = "377"
		},
		{
			.desc = "Base 5 with invalid character",
			.nbr = "1234+",
			.base_from = "01234",
			.base_to = "0123456789",
			.expected = "194"
		},
		{
			.desc = "Octal with invalid character",
			.nbr = "0728",
			.base_from = "01234567",
			.base_to = "0123456789",
			.expected = "58"
		},
		{
			"Decimal to binary",
			"42",
			"0123456789",
			"01",
			"101010"
		},
		{
			"Decimal to hexadecimal (negative)",
			"-42",
			"0123456789",
			"0123456789abcdef",
			"-2a"
		},
		{
			"Decimal to decimal with whitespace and signs",
			"  +--+-42",
			"0123456789",
			"0123456789",
			"-42"
		},
		{
			"INT_MIN",
			"-2147483648",
			"0123456789",
			"0123456789",
			"-2147483648"
		},
		{
			"INT_MAX",
			"2147483647",
			"0123456789",
			"0123456789abcdef",
			"7fffffff"
		},
		{
			"INT_MIN to hexadecimal",
			"-2147483648",
			"0123456789",
			"0123456789abcdef",
			"-80000000"
		},
		{
			"Zero",
			"0",
			"0123456789",
			"01",
			"0"
		},
		{
			"Empty string (should return NULL)",
			"",
			"0123456789",
			"01",
			NULL
		},
		{
			"Empty base_from (should return NULL)",
			"42",
			"",
			"01",
			NULL
		},
		{
			"Empty base_to (should return NULL)",
			"42",
			"0123456789",
			"",
			NULL
		},
		{
			"Invalid base_from (repeated digit)",
			"42",
			"01234567890",
			"01",
			NULL
		},
		{
			"Invalid base_to (contains '+')",
			"42",
			"0123456789",
			"0123456789+",
			NULL
		},
		{
			"Invalid base_from (contains space)",
			"42",
			"0123456789 ",
			"01",
			NULL
		},
		{
			"Invalid base_to (single character)",
			"42",
			"0123456789",
			"0",
			NULL
		},
		{
			"Binary to decimal",
			"101010",
			"01",
			"0123456789",
			"42"
		},
		{
			"Custom base to decimal",
			"bca",
			"abcdefghij",
			"0123456789",
			"120"
		},
		{
			"Decimal to base 16",
			"255",
			"0123456789",
			"0123456789abcdef",
			"ff"
		},
		{
			"Base 16 to decimal",
			"ff",
			"0123456789abcdef",
			"0123456789",
			"255"
		},
		{
			"Negative binary to decimal",
			"-1010",
			"01",
			"0123456789",
			"-10"
		},
		{
			"Decimal to base 36",
			"123456",
			"0123456789",
			"0123456789abcdefghijklmnopqrstuvwxyz",
			"2n9c"
		},
		{
			.desc = "Convert positive decimal to binary",
			.nbr = "42",
			.base_from = "0123456789",
			.base_to = "01",
			.expected = "101010",
		},
		{
			.desc = "Convert negative decimal to hexadecimal",
			.nbr = "-255",
			.base_from = "0123456789",
			.base_to = "0123456789ABCDEF",
			.expected = "-FF",
		},
		{
			.desc = "Convert binary to decimal",
			.nbr = "1010",
			.base_from = "01",
			.base_to = "0123456789",
			.expected = "10",
		},
		{
			.desc = "Convert hexadecimal to decimal",
			.nbr = "FF",
			.base_from = "0123456789ABCDEF",
			.base_to = "0123456789",
			.expected = "255",
		},
		{
			.desc = "Convert with whitespace and sign",
			.nbr = "   ---++--42",
			.base_from = "0123456789",
			.base_to = "0123456789ABCDEF",
			.expected = "-2A",
		},
		{
			.desc = "Convert zero",
			.nbr = "0",
			.base_from = "0123456789",
			.base_to = "01",
			.expected = "0",
		},
		{
			.desc = "Convert INT_MIN",
			.nbr = "-2147483648",
			.base_from = "0123456789",
			.base_to = "0123456789ABCDEF",
			.expected = "-80000000",
		},
		{
			.desc = "Convert INT_MAX",
			.nbr = "2147483647",
			.base_from = "0123456789",
			.base_to = "0123456789ABCDEF",
			.expected = "7FFFFFFF",
		},
		{
			.desc = "Convert between same base",
			.nbr = "42",
			.base_from = "0123456789",
			.base_to = "0123456789",
			.expected = "42",
		},
		{
			.desc = "Invalid character inside number",
			.nbr = "42X",
			.base_from = "0123456789",
			.base_to = "01",
			.expected = "101010",
		},
		{
			.desc = "Invalid base (duplicate character)",
			.nbr = "42",
			.base_from = "0123456789",
			.base_to = "011",
			.expected = NULL,
		},
		{
			.desc = "Invalid base (contains '+')",
			.nbr = "42",
			.base_from = "0123456789",
			.base_to = "01+",
			.expected = NULL,
		},
		{
			.desc = "Invalid base (contains '-')",
			.nbr = "42",
			.base_from = "01-23456789",
			.base_to = "01",
			.expected = NULL,
		},
		{
			.desc = "Invalid base (contains space)",
			.nbr = "42",
			.base_from = "0123456789",
			.base_to = "01 23456789",
			.expected = NULL,
		},
		{
			.desc = "Empty number string",
			.nbr = "",
			.base_from = "0123456789",
			.base_to = "01",
			.expected = NULL,
		},
		{
			.desc = "Empty base_from",
			.nbr = "42",
			.base_from = "",
			.base_to = "01",
			.expected = NULL,
		},
		{
			.desc = "Empty base_to",
			.nbr = "42",
			.base_from = "0123456789",
			.base_to = "",
			.expected = NULL,
		},
		{
			.desc = "Base with length 1",
			.nbr = "42",
			.base_from = "0123456789",
			.base_to = "0",
			.expected = NULL,
		},
		{
			.desc = "Convert to base 36",
			.nbr = "123456789",
			.base_from = "0123456789",
			.base_to = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",
			.expected = "21I3V9",
		},
		{
			.desc = "Convert from base 36",
			.nbr = "HELLO",
			.base_from = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",
			.base_to = "0123456789",
			.expected = "29234652",
		},
		{
			.desc = "Convert positive decimal to binary",
			.nbr = "42",
			.base_from = "0123456789",
			.base_to = "01",
			.expected = "101010",
		},
		{
			.desc = "Convert negative decimal to binary",
			.nbr = "-42",
			.base_from = "0123456789",
			.base_to = "01",
			.expected = "-101010",
		},
		{
			.desc = "Convert binary to hexadecimal",
			.nbr = "101010",
			.base_from = "01",
			.base_to = "0123456789ABCDEF",
			.expected = "2A",
		},
		{
			.desc = "Invalid base_from",
			.nbr = "42",
			.base_from = "01234567899",
			.base_to = "01",
			.expected = NULL,
		},
		{
			.desc = "Invalid base_to",
			.nbr = "42",
			.base_from = "0123456789",
			.base_to = "5",
			.expected = NULL,
		},
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
		result = ft_convert_base(tests[i].nbr, tests[i].base_from,
			   tests[i].base_to);
		if (!result && !tests[i].expected)
		{
      printf(GREEN CHECKMARK GREY " [%d] %s\n" DEFAULT, i + 1,	tests[i].desc);
      }
		else if (!result || !tests[i].expected)
		{
			printf(RED "[%d] %s got \"%s\" instead of \"%s\"\n" DEFAULT, i + 1,	tests[i].desc, result, tests[i].expected);
			error -= 1;
		}
		else if (strcmp(result, tests[i].expected) != 0)
		{
			printf(RED "[%d] %s got \"%s\" instead of \"%s\"\n" DEFAULT, i + 1,	tests[i].desc, result, tests[i].expected);
			error -= 1;
		}
		else
	{
      printf(GREEN CHECKMARK GREY " [%d]	%s got \"%s\" as expected\n" DEFAULT, i + 1, tests[i].desc,	result);
      }
		free(result);
	}
	return (error);
}
