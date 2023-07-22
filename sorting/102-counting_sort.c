#include "sort.h"
/**
 * counting_sort - sorts an arr of integers in ascending sort
 * @arr: pointer to array
 * @size: size of the arr
 **/
void counting_sort(int *arr, size_t size)
{
	int n, j, *cunt_arr, *aux;
	size_t x;

	if (!arr || size < 2)
		return;
	n = arr[0];
	for (x = 0; x < size; x++)
	{
		if (arr[x] > n)
			n = arr[x];
	}
	cunt_arr = calloc((n + 1), sizeof(int));
	for (x = 0; x < size; x++)
	{
		cunt_arr[arr[x]]++;
	}
	for (j = 1; j < n; j++)
	{
		cunt_arr[j + 1] += cunt_arr[j];
	}
	print_array(cunt_arr, n + 1);
	aux = malloc(sizeof(int) * size);
	for (x = 0; x < size; x++)
	{
		cunt_arr[arr[x]]--;
		aux[cunt_arr[arr[x]]] = arr[x];
	}
	for (x = 0; x < size; x++)
	{
		arr[x] = aux[x];
	}
	free(aux);
	free(cunt_arr);
}
