#include "password_validator.h"

bool is_special(char c)
{
	const char special_chars[] = "@#$%ˆ&*";

	for (int i = 0; special_chars[i]; i++)
	{
		if (special_chars[i] == c)
			return true;
	}
	return false;
}

bool is_upper(char c)
{
	return c >= 'A' && c <= 'Z';
}

bool is_lower(char c)
{
	return c >= 'a' && c <= 'z';
}

bool is_digit(char c)
{
	return c >= '0' && c <= '9';
}

bool str_equals(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return false;

	int i = 0;
	for (; s1[i] && s2[i]; i++)
	{
		if (s1[i] != s2[i])
			return false;
	}
	return (s1[i] - s2[i]) == 0;
}

PwStatus validate_password(const char *new_pw, const char *curr_pw)
{
	int size = 0;

	int uppercase_counter = 0;
	int lowercase_counter = 0;
	int digit_counter = 0;
	int special_counter = 0;

	for (; new_pw[size]; size++)
	{
		char c = new_pw[size];
		if (is_upper(c))
			uppercase_counter++;
		else if (is_lower(c))
			lowercase_counter++;
		else if (is_digit(c))
			digit_counter++;
		else if (is_special(c))
			special_counter++;
	}
	if (size < 8)
		return INVALID;
	if (uppercase_counter == 0)
		return INVALID;
	if (lowercase_counter == 0)
		return INVALID;
	if (digit_counter == 0)
		return INVALID;
	if (special_counter == 0)
		return INVALID;

	bool are_equal = str_equals(new_pw, curr_pw);
	if (are_equal)
		return INVALID;
	return VALID;
}

/*
int main(int ac, char **av)
{
	if (ac > 2)
	{
		printf("res[%d]\n", validate_password(av[1], av[2]));
	}
}
*/
