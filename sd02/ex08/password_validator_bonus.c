#include "password_validator.h"

int int_min(int a, int b)
{
	return a < b ? a : b;
}

static int get_edit_distance(
	const char *from, const char *to,
	int from_len, int to_len)
{
	//`from` is empty. For it to become `to` we need to do `to_len` insertions
	if (from_len == 0)
		return (to_len);

	//`to` is empty. For `from` to become `to` we need to do `from_len` removals
	if (to_len == 0)
		return (from_len);

	if (from[from_len - 1] == to[to_len - 1])
		return get_edit_distance(from, to, from_len - 1, to_len - 1);

	// Insert
	int min_distance = get_edit_distance(from, to, from_len, to_len - 1);

	// Remove
	min_distance = int_min(min_distance, get_edit_distance(from, to, from_len - 1, to_len));

	// Replace
	min_distance = int_min(min_distance, get_edit_distance(from, to, from_len - 1, to_len - 1));

	return 1 + min_distance;
}

int calc_edit_distance(const char *from, const char *to)
{
	int from_len = 0;

	while (from[from_len])
		from_len++;

	int to_len = 0;
	while (to[to_len])
		to_len++;
	return get_edit_distance(from, to, from_len, to_len);
}
