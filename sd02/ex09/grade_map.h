#ifndef GRADE_MAP_H
#define GRADE_MAP_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef const char *GradeMapperReturn;

typedef GradeMapperReturn (*GradeMapper)(int score);

void map_scores(const int *scores, int size,
				GradeMapper mapper, const char **mapped_grades);

GradeMapperReturn plusminus_mapper(int score);
GradeMapperReturn passfail_mapper(int score);
GradeMapperReturn standard_mapper(int score);

typedef struct s_grade_node
{
	char *grade;
	int occurrences;

	struct s_grade_node *next;
} GradeNode;

GradeNode *compute_distribution(const char **mapped_grades, int size);
void print_distribution(GradeNode *head);
void free_distribution(GradeNode *head);

#endif
