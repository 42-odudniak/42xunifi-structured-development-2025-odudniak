#ifndef GRADE_MAP_H
#define GRADE_MAP_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum e_grade
{
	A,
	B,
	C,
	D,
	E,
	F,
} t_grade;

typedef const char * GradeMapperReturn;

typedef const char *(*GradeMapper)(int score);

void map_scores(const int *scores, int size,
				GradeMapper mapper, const char **mapped_grades);

#endif
