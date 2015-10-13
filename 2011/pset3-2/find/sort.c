#include <stdio.h>
#include <cs50.h>


    int size;
    int values[15];
    
    
    int
    main(void)
    {

    for (size = 0; size < 11; size++)
    {
        // wait for hay until EOF
        printf("\nvalues[%d] = ", size);
        int straw = GetInt();
        if (straw == 15)  //ingnore
            break;
        
        // add hay to stack
        values[size] = straw;
    }
    printf("\n\n\n");

//sorting

    int temp;

    for (int i = 0; i < size-2; i++ )
     {
     cng = 0
     if (values[i] > values[i+1])
      {
         temp = values[i+1];
         values[i+1] = values[i];
         values[i] = temp;
         printf("%d - %d\n", values[i], values [i+1]);
         cng = 1
      }
    }
    printf("\n");
    return 0;
}


if (cng = 0)
{
for (int i=size-2; i!=0;i--)
cng=1
}
