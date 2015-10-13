#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


/****************************************
 * vigenere.c
 *
 * edx CS50x
 * Guy O. Israel
 *
 * Encrypts given text, by given key,
 * using Vignere cipher.
 *
 * Usage: ./vigenere <key>
 *
 ****************************************/


int encrypt(string p,int i,int j,int lenp,int lenc,int key);
int findkey(int key);
int jrev(int j, int na, int lenc);

int i;

int
main (int argc, char *argv[])
{
    if (argc !=2) //verify input 1
        {printf("Missing key. Correct usage: ./vigenere <key>");
        return 1;
        }
        
    int lenc = strlen(argv[1]);
    
    for (i=0; i<lenc;)  //verify input 2
        if ( isalnum(argv[1][i]))
            i++;
        else
        {
        printf("Key must contain only letters and numbers (\"%c\" is invaild)", argv[1][i]);
        return 1;
        }
        
    string p = GetString();
    int key;
    int j = 0;
    int j1 = 0;
    int j2 = 0;
    int lenp = strlen(p);
    for (int i = 0; i<lenp; i++)  //run all "to encrypt text"
        {
            j = j1+j2;
             key = (int)argv[1][j];
             j2 = encrypt(p,i,j,lenp,lenc,key);
        }
    printf("\n");
    return  0;
}

    int encrypt(string p,int i,int j,int lenp,int lenc,int key)
    {
        int k = findkey(key);
        int na = 0;
        if (p[i]>=65 && p[i]<=90) //upper case
                {
                    if ((char)p[i]+k>90) //wrap around
                        printf("%c", ((char)p[i]+k)-26);
                    else 
                        printf("%c", (char)(p[i]+k));
                j= jrev(j,na,lenc);
                }
                else if (p[i]>=95 && p[i]<=122) //lower case
                {
                    if ((char)p[i]+k>122) //wrap around
                    printf("%c", ((char)p[i]+k)-26);
                    else
                    printf("%c", (char)(p[i]+k));
                j = jrev(j,na,lenc);
                }
                else  //none letters
                    {
                    printf("%c", (char)p[i]);
                    na=1;
                    j = jrev(j,na,lenc);
                    }
        return j;
    }
    
    int findkey(int key)
    {
    int k;
    if (key <= 90)
        k = key-65;
    else 
        k = key-97;
    return k;
    }
    
    int jrev(int j, int na, int lenc)
    {
        if (j+1==lenc && na==0)
            j=0;
        else if (j+1==lenc && na==1)
        {}
        else
            j++;
        return j;
    }
