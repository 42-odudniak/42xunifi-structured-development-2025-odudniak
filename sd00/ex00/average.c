#include "average.h"

float average(const int *arr, int size)
{
	float result = 0;

	if (size == 0)
		return 0;

	for (int i = 0; i < size; i++)
	{
		result += arr[i];
	}
	return result / size;
}
