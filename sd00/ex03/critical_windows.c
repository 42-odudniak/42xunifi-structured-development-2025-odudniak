#include "critical_windows.h"

int count_critical_windows(const int *readings, int size)
{
	const int range = 5;
	const int range_idx = range - 1;

	int result = 0;

	for (int start = 0; start + range_idx < size; start++)
	{
		int exceeding_70_or_equal = 0;
		int exceeding_150 = 0;
		int average = 0;
		for (int i = start; i <= start + range_idx; i++)
		{
			average += (readings[i] / range);
			if (readings[i] >= 70)
				exceeding_70_or_equal++;
			if (readings[i] > 150)
				exceeding_150++;
		}
		printf("start[%d]-end[%d]:"
			   "\n\taverage[%d]"
			   "\n\treading>=70[%d]"
			   "\n\treading>150[%d]\n",
			   start, start + range - 1,
			   average, exceeding_70_or_equal, exceeding_150);

		if (exceeding_70_or_equal >= 3 && exceeding_150 == 0 && average >= 90)
		{
			result++;
		}
	}
	return result;
}

int main()
{
	int readings[] = {80, 70, 90, 85, 120};
	int size = 5;
	printf("res[%d]\n", count_critical_windows(readings, size));
}
