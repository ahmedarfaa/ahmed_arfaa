#include "sort.h"
#include <stdio.h>
#include <stdbool.h>


void bubble_sort(int *array, size_t size)
{
    bool sort;
    size_t i;
    int temp;
    do
    {
        sort = false;
        for (i = 0; i < size - 1; i++)
        {
            if (array[i]> array[i+1])
            {
                sort = true;
                temp = array[i];
                array[i] = array[i+1];
                array[i+1]= temp;
                 print_array(array, size);
               
            }
           
           
        }
       
    } while (sort);
    
    
}