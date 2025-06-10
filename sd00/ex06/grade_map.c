#include "grade_map.h"

GradeMapperReturn plusminus_mapper(int score)
{
	if (score < 0 || score > 100)
		return (NULL);

	if (score < 60)
		return ("F");

	if (score <= 62)
		return ("D-");
	if (score <= 66)
		return ("D");
	if (score <= 69)
		return ("D+");

	if (score <= 72)
		return ("C-");
	if (score <= 76)
		return ("C");
	if (score <= 79)
		return ("C+");

	if (score <= 82)
		return ("B-");
	if (score <= 86)
		return ("B");
	if (score <= 89)
		return ("B+");

	if (score <= 92)
		return ("A-");
	if (score <= 96)
		return ("A");
	return ("A+");
}

GradeMapperReturn passfail_mapper(int score)
{
	if (score < 0 || score > 100)
		return (NULL);
	if (score <= 60)
		return ("F");
	if (score <= 100)
		return ("P");
	return (NULL);
}

GradeMapperReturn standard_mapper(int score)
{
	if (score < 0 || score > 100)
		return (NULL);
	if (score < 60)
		return ("F");
	if (score < 70)
		return ("D");
	if (score < 80)
		return ("C");
	if (score < 90)
		return ("B");
	if (score <= 100)
		return ("A");
	return (NULL);
}

void map_scores(const int *scores, int size,
				GradeMapper mapper, const char **mapped_grades)
{
	for (int i = 0; i < size; i++)
	{
		mapped_grades[i] = mapper(scores[i]);
	}
}

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
}
