#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage: cat filename [filename ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        // TODO: open argv[i] and print its contents to stdout
        int* ending;
        int i = 0;
        FILE *fp = fopen(argv[i], "r");
        if (fp!=NULL)
            {   char buffer[512];
                char data[512];
                //fgets(buffer,512,fp);
                while(1)
                {
                    buffer[i] = fread(data,sizeof(buffer),1,fp);
                    if(buffer[i]==0)
                    {
                        //int* ending;
                        ending = malloc(sizeof(int));
                        *ending = i;
                        break;
                    }
                }
                for(int j = 0; j < *ending; j++)
                    printf("%c" , buffer[j]);
               i++;
            }
    fclose(fp);
    free(ending);
    printf("\n");
    }

    return 0;
}
