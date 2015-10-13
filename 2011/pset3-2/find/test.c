#include <stdio.h>
#include <cs50.h>

#define MAX_INT 65535

// function prototype
//void swap(int values[11],int  i);
    
    int
    main(void)
{    int chk, i, size, values[11];
    for (i = 0; i < size-2; i++ )
       {
       chk = 0;
       if (values[i] > values[i+1])
        {
        int temp = values[i]; //swap
        values[i] = values[i+1];
        values[i+1] = temp;
        chk = 1;
        }
     }
     for (int i = 0; i < size-2; i++ )
      {
      printf("%d\n", values[i]);
      printf("\n");
      }
    printf("\n");
    if (chk == 1)
    sort();
    }
