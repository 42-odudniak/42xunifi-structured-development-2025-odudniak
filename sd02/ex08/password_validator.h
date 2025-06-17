#ifndef PASSWORD_VALIDATOR_H
#define PASSWORD_VALIDATOR_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASSW_HISTORY_SIZE 3

typedef enum PwStatusEnum
{
	VALID,
	INVALID_WEAK,
	INVALID_SIMILAR
}	PwStatus;

typedef struct s_history
{
	int			inserted;
	int			curr_idx;

	// Better to have a strdup + free on the new password insertion ?
	const char	*last_passwords[PASSW_HISTORY_SIZE];

}	PasswordHistory;

PwStatus	validate_password(const char *new_pw, PasswordHistory *history);

int			int_min(int a, int b);

int			calc_edit_distance(const char *from, const char *to);

#endif
