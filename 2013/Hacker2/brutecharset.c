#include <stdio.h>

int main(void)
{
    int a = 97;
    for(;a<('z'+1);a++)
    {
        printf("\"%c\",\"%c\",",a,a^32);
    }
    for(int i=0; i<10;i++)
        printf("\"%d\",",i);
    return 0;
}
