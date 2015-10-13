#include <stdio.h>
#include <cs50.h>

#define MAX_INT 65535

// function prototype
void sort(int values[], int size);

    int size;
    int values[13];
    
    int
    main(void)
    {

    for (size = 0; size < MAX_INT; size++)
    {
        // wait for hay until EOF
        printf("\nvalues[%d] = ", size);
        int straw = GetInt();
        if (straw == MAX_INT)  //ingnore
            break;
        
        // add hay to stack
        values[size] = straw;
    }
    printf("\n\n\n");

    //sorting  
    sort(values[], size);
    /**int chk = 1;
    for (;chk == 1;chk--)
    {
    for (int i = 0; i < size-2; i++ )
     {
     chk = 0;
    if (values[i] > values[i+1])
        {
        int temp = values[i];
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
    printf("\n");**/
    return 0;
}

    void
    sort(int values[],int size)  //selection sort
    {
    int chk, i; 
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

