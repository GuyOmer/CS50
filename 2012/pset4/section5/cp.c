#include <stdio.h>

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage: cp source destination\n");
        return 1;
    }

    // TODO: copy the contents of argv[1] to argv[2]
    
    FILE *rffp = fopen(argv[1],"r");
    FILE *wtfp = fopen(argv[2],"w");
    if( wtfp!=NULL && rffp!=NULL)
        {
        char readc[106];
        fputs(fgets(readc,106,rffp), wtfp);
        }
    fclose(wtfp);
    fclose(rffp);
    return 0;
}

