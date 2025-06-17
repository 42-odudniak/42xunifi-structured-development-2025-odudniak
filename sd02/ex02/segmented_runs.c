#include "segmented_runs.h"

int sequence_size_until_block_end(const int *arr, int size, int start_idx)
{
	int count = 1;

	for (int i = start_idx; i < size && arr[i] != -1; i++)
	{
		if (i == 0 || arr[i - 1] == -1)
			continue;

		if (arr[i] < arr[i - 1])
			return count;
		count++;
	}
	return count;
}

int count_segments(const int *arr, int size)
{
	const int threshold = 3;

	int result = 0;
	bool added = false;

	for (int i = 0; i < size; i++)
	{
		if (arr[i] == -1)
		{
			added = false;
			continue;
		}

		if (!added && sequence_size_until_block_end(arr, size, i) >= threshold)
		{
			result++;
			added = true;
		}
	}
	return result;
}

/*
int main()
{
	int arr[] = {-1,-1,2, 3, 4, -1, 5, 6, -1, 1, 2, 3, 4};
	int size = 13;
	printf("res[%d]\n", count_segments(arr, size));
}
*/
