#ifndef PASSWORD_VALIDATOR_H
#define PASSWORD_VALIDATOR_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum PwStatusEnum
{
	VALID,
	INVALID
} PwStatus;

PwStatus validate_password(const char *new_pw, const char *curr_pw);

#endif
