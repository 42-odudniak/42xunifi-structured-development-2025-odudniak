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

PwStatus validate_password(const char *new_pw, PasswordHistory *history)
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
		return INVALID_WEAK;
	if (uppercase_counter == 0)
		return INVALID_WEAK;
	if (lowercase_counter == 0)
		return INVALID_WEAK;
	if (digit_counter == 0)
		return INVALID_WEAK;
	if (special_counter == 0)
		return INVALID_WEAK;

	for (int i = 0; i < history->inserted; i++)
	{
		int edit_distance = calc_edit_distance(new_pw, history->last_passwords[i]);
		printf("\e[90m\tnew_pw[%s]\thist[%s]\tedit_distance[%d]\e[0m\n", new_pw, history->last_passwords[i], edit_distance);
		if (edit_distance <= 1)
			return INVALID_SIMILAR;
	}

	if (history->inserted < PASSW_HISTORY_SIZE)
		history->inserted++;

	history->last_passwords[history->curr_idx] = new_pw;
	history->curr_idx = (history->curr_idx + 1) % PASSW_HISTORY_SIZE;

	return VALID;
}

/*
int main(void)
{
	const char *inputs[] = {"@ABC1test", "@ABC1tst", "@ABC1hello", "@ABC1world", "@ABC1cold", "tst"};
	int size = sizeof(inputs) / sizeof(inputs[0]);

	PasswordHistory history = (PasswordHistory){0};
	for (int i = 0; i < size; i++)
	{
		PwStatus result = validate_password(inputs[i], &history);
		printf("Candidate[%s]: ", inputs[i]);
		if (result == VALID)
			printf("\e[92m valid!\e[0m");
		else if (result == INVALID_WEAK)
			printf("\e[91m invalid! password is weak\e[0m");
		else if (result == INVALID_SIMILAR)
			printf("\e[91m invalid! password too similar\e[0m");
		printf("\n");
	}
}
*/
