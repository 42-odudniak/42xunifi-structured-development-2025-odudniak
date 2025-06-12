#include "grade_map.h"

static char *str_dup(const char *s)
{
	if (!s)
		return NULL;
	const size_t len = strlen(s);

	char *result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return NULL;

	int i;
	for (i = 0; i < len && s[i]; i++)
	{
		result[i] = s[i];
	}
	result[i] = 0;

	return result;
}

static GradeNode *insert_distribution_node(GradeNode **head, const char *grade)
{
	if (!head)
		return NULL;

	GradeNode *node = (GradeNode *)malloc(sizeof(GradeNode));
	if (!node)
		return NULL;

	node->grade = str_dup(grade);
	node->occurrences = 0;
	node->next = NULL;

	if (!*head)
	{
		*head = node;
		return node;
	}

	GradeNode *last_node = *head;
	while (last_node && last_node->next)
		last_node = last_node->next;
	last_node->next = node;

	return node;
}

static GradeNode *find_distribution_node(GradeNode *head, const char *grade)
{
	for (GradeNode *node = head; node; node = node->next)
	{
		if (!node->grade)
			continue;

		if (!strcmp(grade, node->grade))
		{
			return node;
		}
	}
	return NULL;
}

GradeNode *compute_distribution(const char **mapped_grades, int size)
{
	GradeNode *result = NULL;

	for (int i = 0; i < size; i++)
	{
		const char *grade = mapped_grades[i];

		GradeNode *node = find_distribution_node(result, grade);

		if (!node)
		{
			node = insert_distribution_node(&result, grade);
			if (!node)
			{
				free_distribution(result);
				return NULL;
			}
		}
		node->occurrences++;
	}

	return result;
}

void print_distribution(GradeNode *head)
{
	for (GradeNode *node = head; node; node = node->next)
	{
		printf("[%s]:\t%d\n", node->grade, node->occurrences);
	}
}

void free_distribution(GradeNode *head)
{
	if (!head)
		return;

	free_distribution(head->next);
	free(head->grade);
	free(head);
}

/*
int main(void)
{
// Change only the array values
	const int scores[] = {12, 53, 67, 57, 90, 99, 40};

	int size = sizeof(scores) / sizeof(scores[0]);

	const char *mapped_plusminus_grades[size];
	map_scores(scores, size, plusminus_mapper, mapped_plusminus_grades);

	const char *mapped_passfail_grades[size];
	map_scores(scores, size, passfail_mapper, mapped_passfail_grades);

	const char *mapped_standard_grades[size];
	map_scores(scores, size, standard_mapper, mapped_standard_grades);

	for (int i = 0; i < size; i++)
	{
		printf("[%d]\tscore[%d]:"
			   "\tplusminus=%s"
			   "\tpassfail=%s"
			   "\tstandard=%s\n",
			   i, scores[i],
			   mapped_plusminus_grades[i],
			   mapped_passfail_grades[i],
			   mapped_standard_grades[i]);
	}
	printf("\n");
	printf("plusminus distribution:\n");
	GradeNode *plusminus_distribution = compute_distribution(mapped_plusminus_grades, size);
	print_distribution(plusminus_distribution);
	free_distribution(plusminus_distribution);

	printf("passfail distribution:\n");
	GradeNode *passfail_distribution = compute_distribution(mapped_passfail_grades, size);
	print_distribution(passfail_distribution);
	free_distribution(passfail_distribution);

	printf("standard distribution:\n");
	GradeNode *standard_distribution = compute_distribution(mapped_standard_grades, size);
	print_distribution(standard_distribution);
	free_distribution(standard_distribution);

}
*/
