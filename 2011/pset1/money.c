#include <stdio.h>
#include <cs50.h>
int
main(void)
  {
    int days;
    do {
        printf("Type in number of days in month: "); //Get days
        days = GetInt();
       }
    while (days < 28 || days >31); //Month vaild test

    printf("Enter amount of pennies on first day: "); //get pennies
    int penny = GetInt();

float total2 = penny * 2;   //calculate total
for(int i = 0; i<days-2;i++)
    {total2 *= 2;
 //   printf("%.2f \n", total2); //my test
    }
    printf("\n Total in $: %.2f \n", total2/100.0); //Total
  }
