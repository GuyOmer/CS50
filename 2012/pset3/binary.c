#include <cs50.h>
#include <stdio.h>
#include <math.h>

#define SIZE 8

bool search(int needle, int haystack[], int size, int minpt, int maxpt)
{

    if (maxpt < minpt)  //Checks if array is vaild
            return false;

    int midpt = floor((minpt+maxpt)/2);      //finds mid point
    
    if (haystack[midpt] > needle)  //target is at lower part of array
            return search(needle, haystack, size, minpt, midpt-1);
            
    else if (haystack[midpt] < needle)  //target is at upper part of array
        return search (needle, haystack, size,midpt+1, maxpt);
    
    else  //key found
        return true;
}

int main(void)
{
    int minpt = 0;
    int maxpt = SIZE-1;
    int numbers[SIZE] = { 4, 8, 15, 16, 23, 42, 50, 108 };
    printf("> ");
    int n = GetInt();
    if (search(n, numbers, SIZE, minpt, maxpt))
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}
