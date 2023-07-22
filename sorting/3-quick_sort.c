#include "sort.h"

/**
 * swap_items - Swaps two items in An-array.
 * @array: array to modify.
 * @l: index of the left Item.
 * @r: index of the right Item.
 */
void swap_items(int *array, size_t l, size_t r)
{
	int temp;

	if (array != NULL)
	{
		temp = array[l];
		array[l] = array[r];
		array[r] = temp;
	}
}

/**
 * quick_sort_range_lomuto - Sorts a sub array
 * @array: array containing the sub-array.
 * @low: starting position of the sub-array.
 * @high: ending position of the sub-array.
 * @size: length of the array.
 */
void quick_sort_range_lomuto(int *array, size_t low, size_t high, size_t size)
{
	size_t k, i;
	int pvt;

	if ((low >= high) || (array == NULL))
		return;
	pvt = array[high];
	k = low;
	for (i = low; i < high; i++)
	{
		if (array[i] <= pvt)
		{
			if (k != i)
			{
				swap_items(array, k, i);
				print_array(array, size);
			}
			k++;
		}
	}
	if (k != high)
	{
		swap_items(array, k, high);
		print_array(array, size);
	}
	if (k - low > 1)
		quick_sort_range_lomuto(array, low, k - 1, size);
	if (high - k > 1)
		quick_sort_range_lomuto(array, k + 1, high, size);
}

/**
 * quick_sort - Sorts an array using quick sort algorithm
 * @array: array to sort.
 * @size: length of the array.
 */
void quick_sort(int *array, size_t size)
{
	if (array != NULL)
	{
		quick_sort_range_lomuto(array, 0, size - 1, size);
	}
}
