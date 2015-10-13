#include <stdio.h>
#include <cs50.h>


int
main(void)
{
    int mf, fm, mm, ff;
    do {
    printf("M spotting F: ");
    mf = GetInt();
    }
    while (mf<0);

    do {
    printf("F spotting M: ");
    fm = GetInt();
    }
    while (fm<0);

    do {
    printf("M spotting M: ");
    mm = GetInt();
    }
    while (mm<0);

    do {
    printf("F spotting F: ");
    ff = GetInt();
    }
    while (ff<0);

    int ti = 80 / ((mf+fm+mm+ff);
    printf("Floating Point Test: %f \n ", ti);

    //charts
    printf("M spotting F: \n");
    for (int i = 0; i<mf*ti;i++)
    {
    printf("#");
    }

    printf("\nF spotting M: \n");
    for (int i = 0; i<fm*ti;i++)
    {
    printf("#");
    }

    printf("\nM spotting M: \n");
    for (int i = 0; i<mm*ti;i++)
    {
    printf("#");
    }

    printf("\nF spotting F: \n");
    for (int i = 0; i<ff*(int)ti;i++)
    {
    printf("#");
    }
    printf("\n\n Ratio: 1:%.2f \n", (float)ti);

}
