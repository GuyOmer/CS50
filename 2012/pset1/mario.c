#include <stdio.h>
#include <cs50.h>

int
main(void)
{
    int pyrah;
    while(true)
        {
        printf("Height: ");
        pyrah = GetInt();
        if (pyrah >= 0 && pyrah <= 23)
        break;
        }
    if (pyrah == 0)
    return 0;
    else if (pyrah == 1)
    {
    printf("##\n");
    return 0;
    }
    else
    {
    for(int i = 0; i < pyrah; i++)
        {
        for (int j = 0;j < pyrah-i-1;j++) //Prints spaces
        printf(" ");
        for (int n = 0;n <= i+1;n++)  //Prints "#"
        printf("#");
        printf("\n");
        }
    }
    return 0;
}
