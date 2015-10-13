#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ADIM 108


int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage: cat filename [filename ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp!=NULL)
            {
                char filec[ADIM];
                if (fgets(filec,ADIM,fp)!=NULL)
                    printf("%s" , filec);
                fclose(fp);
            }
        else
            {
            printf("Error opening %s.\n" , argv[i]);
            return 1;
            }
    }
    return 0;
}
