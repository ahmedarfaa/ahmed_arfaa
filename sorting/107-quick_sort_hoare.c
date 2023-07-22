#include "sort.h"


/**
*swap - the pstions of two elements into an arr
*@arr: array
*@itm1: arr element
*@itm2: arr element
*/
void swap(int *arr, ssize_t itm1, ssize_t itm2)
{
	int tmp;

	tmp = arr[itm1];
	arr[itm1] = arr[itm2];
	arr[itm2] = tmp;
}
/**
 *hoare_partition - hoare partition sorting scheme implementation
 *@arr: array
 *@first: first arr element
 *@last: last arr element
 *@size: size arr
 *Return: return the pstion of the last element sorted
 */
int hoare_partition(int *arr, int first, int last, int size)
{
	int current = first - 1, finder = last + 1;
	int pvt = arr[last];

	while (1)
	{

		do {
			current++;
		} while (arr[current] < pvt);
		do {
			finder--;
		} while (arr[finder] > pvt);
		if (current >= finder)
			return (current);
		swap(arr, current, finder);
		print_array(arr, size);
	}
}
/**
 *qk_sort - qucksort algorithm implementation
 *@arr: array
 *@frst: first arr element
 *@lst: last arr element
 *@size: arr size
 */
void qk_sort(int *arr, ssize_t frst, ssize_t lst, int size)
{
	ssize_t pstion = 0;

	if (frst < lst)
	{
		pstion = hoare_partition(arr, frst, lst, size);
		qk_sort(arr, frst, pstion - 1, size);
		qk_sort(arr, pstion, lst, size);
	}
}
/**
 *quick_sort_hoare - prepare the terrain to quicksort algorithm
 *@arr: array
 *@size: arr size
 */
void quick_sort_hoare(int *arr, size_t size)
{
	if (!arr || size < 2)
		return;
	qk_sort(arr, 0, size - 1, size);
}
