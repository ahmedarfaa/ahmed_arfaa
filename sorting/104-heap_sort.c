#include "sort.h"


/**
 * check_tree - M E 
 * @arr: ptr to array
 * @size: size of ptr
 * @init_size: original size of arr
 * @i: index as a root of the tree
**/
void check_tree(int *arr, size_t init_size, size_t size, size_t i)
{

	int n, brnch1, brnch2;
	size_t br1, br2;

	br1 = i * 2 + 1;
	br2 = br1 + 1;
	brnch1 = arr[br1];
	brnch2 = arr[br2];
	if (((br1 < size) && (br2 < size) &&
		(brnch1 >= brnch2 && brnch1 > arr[i]))
		|| ((br1 == size - 1) && brnch1 > arr[i]))
	{
		n = arr[i];
		arr[i] = brnch1;
		arr[br1] = n;
		print_array(arr, init_size);
	}
	else if ((br1 < size) && (br2 < size) &&
		(brnch2 > brnch1 && brnch2 > arr[i]))
	{
		n = arr[i];
		arr[i] = brnch2;
		arr[br2] = n;
		print_array(arr, init_size);
	}
	if (br1 < size - 1)
		check_tree(arr, init_size, size, br1);
	if (br2 < size - 1)
		check_tree(arr, init_size, size, br2);
}
/**
 * heap_sort - sorts an arr of integers
 * @arr: pointer to array
 * @size: size of the pointer
**/
void heap_sort(int *arr, size_t size)
{
	size_t i, init_size = size;
	int n;

	if (!arr)
		return;
	for (i = 0; i < size / 2 ; i++)
	{
		check_tree(arr, init_size, size, size / 2 - 1 - i);
	}
	for (i = 0; i < init_size - 1; i++)
	{
		n = arr[0];
		arr[0] = arr[size - 1 - i];
		arr[size - 1 - i] = n;
		print_array(arr, init_size);
		check_tree(arr, init_size, size - i - 1, 0);
	}
}
