/**************************************************************************** 
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 ***************************************************************************/
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"


/*
 * Returns true if value is in array of n values, else false.
 */

bool 
search(int value, int array[], int n)
{
    // TODO: re-implement as binary search
    for (int i = 0; i < n; i++)
        if (array[i] == value)
            return true;
    return false;
}


/*
 * Sorts array of n values.
 */

void 
sort(int values[], int n) //Bubble sort O(n^2) omega(n)
{

    // TODO: implement a O(n^2) sort
    int chk = 0;
    do
    {
        chk=0;
        for (int i = 0; i < size-2; i++ )
          {
        if (values[i] > values[i+1])
        {
        int temp = values[i];
        values[i] = values[i+1];
        values[i+1] = temp;
        chk++;
        }
     }
     
     printf("\n");
    }
    
    while (chk!=0);
    printf("\n");
    return;
}
