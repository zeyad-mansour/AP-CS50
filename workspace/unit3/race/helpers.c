#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"
#include <cs50.h>


bool check_flag(char* str)
{
    if (strcmp(str, "-a") != 0 && strcmp(str, "-b") != 0 &&
    strcmp(str, "-r") != 0 && strcmp(str, "-s") != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void bubble(int values[], int n)
{
    int i;
	int j;
	int temp;

    for (i = 0 ; i < ( n - 1 ); i++)
    {
        for (j = 0 ; j < n - i - 1; j++)
        {
            if (values[j] > values[j + 1])
            {
                temp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp;
            }
        }
    }
    return;
}

void selection(int values[], int n)
{
    int i;
	int j;
	int temp;
	int min;


    for (i = 0 ; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (values[min] > values[j])
            {
                min = j;
            }
        }
        if (min != i)
        {
            temp = values[i];
            values[i] = values[min];
            values[min] = temp;
        }
    }
    return;
}


void insertion(int values[], int n)
{
    int selected_char;
	int i;
	int j;

    for (i = 1 ; i <= n - 1; i++)
    {
        selected_char = values[i];
        j = i;

        while ( j > 0 && selected_char < values[j - 1])
        {
            values[j] = values[j - 1];
            j--;
            values[j] = selected_char;
        }
    }
    return;
}