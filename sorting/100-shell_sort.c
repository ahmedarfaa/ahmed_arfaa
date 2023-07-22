#include "sort.h"
#include <stdio.h>
/**
 * _Swap - swaped 2 values.
 * @arr: array for swap him values.
 * @x: First index
 * @y: Second index
 */
void _Swap(int *arr, int x, int y)
{
	int temp;

	if (arr[x] != arr[y])
	{
		temp = arr[x];
		arr[x] = arr[y];
		arr[y] = temp;
	}
}

/**
 * shell_sort - sort the list & print the changes
 * @array: array to sort.
 * @size: Size of array
 */
void shell_sort(int *array, size_t size)
{
	size_t h = 0,  x, y;

	if (size < 2)
		return;

	while (h <= size / 3)
		h = h * 3 + 1;

	while (h >= 1)
	{
		for (x = h; x < size; x++)
			for (y = x; y >= h && array[y] < array[y - h]; y -= h)
				_Swap(array, y, y - h);
		h /= 3;
		print_array(array, size);
	}
}
