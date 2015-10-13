#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int
main(int argc, char	*argv[])
{
    if (argc!=2)
    {
        printf("Invaild input\n");
        return 1;
    }
    else
    {
         int k = (atoi(argv[1]))%26;  //% in case input >26
        printf("Enter Plain-text for encryptions:\n");
        string p = GetString();
        printf("Encrypted Text:\n");
        for (int i = 0, n = strlen(p); i < n; i++)  //create to wrap around, and asci cal!
            {
                if (p[i]>65&&p[i]<90) //upper case
                {
                    if ((char)p[i]+k>90) //wrap around
                    {
                    printf("%c", 65+(((char)p[i]+k)-91));
                    }
                    else 
                    printf("%c", (char)(p[i]+k));
                }
                else if (p[i]>97&&p[i]<122) //lower case
                {
                    if ((char)p[i]+k>122) //wrap around
                {
                    printf("%c", 97+(((char)p[i]+k)-123));
                }
                    else
                {
                    printf("%c", (char)(p[i]+k));
                }
                }
                else  //none letters
                    printf("%c", (char)p[i]);
            }
    printf("\n");
    }
}
