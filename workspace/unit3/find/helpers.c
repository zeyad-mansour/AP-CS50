
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

bool search(int value, int values[], int n)
{
	int middle;
    int right = n - 1;
	int left = 0; //zero, not one! Or index will be one off.

   while (left <= right)
    {
        middle = left + (right - left)/2;
        if (values[middle] == value) //Lucky if this happens!
        {
            return true;
        }
        else if (values[middle] > value)
        {
            right = middle - 1; //narrow down the search to only the values on the left
        }
        else
        {
            left = middle + 1; //narrow down the search to only the values on the right
        }

    }
    return false;
	//value is not in haystack!
}

void sort(int values[], int n)
{
    for (int i = 0; i < n - 1; i++) //loop to find the minimum value(min)
    {

        int min = i;

        for (int x = i; x < n; x++)
        {
            if (values[min] > values[x])
            {
                min = x;
            }
        }

        if (min != i)
        {

            int sort = values[min];
            values[min] = values[i];
            values[i] = sort; // switches the current value in loop with the lowest value
        }
    }
    return;
}