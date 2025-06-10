#include "first_last.h"

void first_last(int arr[], int size, int target,
				int *first, int *last)
{
	bool found_one = false;

	for (int i = 0; i < size; i++)
	{
		if (arr[i] == target)
		{
			if (found_one == false)
			{
				*first = i;
				found_one = true;
			}
			*last = i;
		}
	}
	if (found_one == false)
	{
		*first = -1;
		*last = -1;
	}
}
