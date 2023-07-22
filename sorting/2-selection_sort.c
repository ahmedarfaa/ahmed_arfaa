#include "sort.h"
#include <stdio.h>

/**
 * selection_sort - sorts an array of integers in ascending order
 * @array: The array
 * @size: size of the array
 */
void selection_sort(int *array, size_t size)
{
	size_t x, stp, mini_indx;
	int tmp;

	for (stp = 0; stp < size - 1; stp++)
	{
		mini_indx = stp;
		for (x = stp + 1; x < size; x++)
		{
			if (array[x] < array[mini_indx])
				mini_indx = x;
		}

		if (mini_indx != stp)
		{
			tmp = array[stp];
			array[stp] = array[mini_indx];
			array[mini_indx] = tmp;
			print_array(array, size);
		}
	}
}
