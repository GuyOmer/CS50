#include <stdio.h>
#include <cs50.h>

#define MAX_INT 65535


    int size;
    int values[13];
    
    int
    main(void)
    {

        for (size = 0; size < 11; size++)
    {
        // wait for hay until EOF
        printf("\nvalues[%d] = ", size);
        int straw = GetInt();
        if (straw == 15)
            break;
        
        // add hay to stack
        values[size] = straw;
    }
    printf("\n\n\n");

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
    return 0;
}


