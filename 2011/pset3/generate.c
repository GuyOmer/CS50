/***************************************************************************
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 ***************************************************************************/
       
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT 65536

int
main(int argc, char *argv[])
{
    // TODO: Checks for vaild cl input
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    /** TODO: transform+initlize "n" (number of pseudorandom numbers)
    from the argv array to int from char
    **/
    int n = atoi(argv[1]);

    /** TODO: gets seed
    if:if seed [s] is provided than program seed will be it
    else: if no seed [s] is provided number of seconds 
    from jan 1 1970 will be the seed
    both as ints (transform from char to int)
    **/
    if (argc == 3)
        srand((unsigned int) atoi(argv[2]));
    else
        srand((unsigned int) time(NULL));

    /** TODO: loop to print out psudorandom numbers
    incase created psudorandom number is too big for unsigned int range
    **/
    for (int i = 0; i < n; i++)
        printf("%d\n", rand() % LIMIT);

    // that's all folks
    return 0;
}
