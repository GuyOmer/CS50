#include <stdio.h>
#include <cs50.h>
#include <math.h>

/****************************************
 * greedy.c
 *
 * edx CS50x
 * Guy O. Israel
 *
 * Checks how many coins are returned
 * for a given amount of change.
 *
 ****************************************/



int
main(void)
{
    float owed_change;
    int coins = 0;
    while(true)
        {
        printf("O hai!  How much change is owed?\n");
        owed_change = GetFloat();
        if (owed_change >= 0 )   //Verify positive input
        break;
        }
    //Some math for a proper float to int conversion  
    float change1 = owed_change * 100;
    int change = (int) round(change1);
    
    int change_coins[] = {25,10,5,1}; //Array of possible change coins
    for (int i = 0; i < 4; i++)
        {
        coins = (change-(change%change_coins[i]))/change_coins[i]+coins; //Calcluates how many coins
        change = change%change_coins[i];                                 //should be given back + recalcluates change
        }
    printf("%d\n", coins);
}
