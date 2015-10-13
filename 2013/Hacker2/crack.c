#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define LENGTH 45

#define _XOPEN_SOURCE
#include <unistd.h>

//prototypes
char *crypt(const char *key, const char *salt);
bool crack(const char *key, const char *hash, const char *salt);
bool dic_attk(const char *hash, const char *salt);
bool bruteforce(const char *hash, const char *salt);

int main(int argc, char* argv[])
{
    
    if(argc != 2)
    {
        printf("Usage: ./crack password\n");
        return 1;
    }
    
    const char* hash = argv[1];
    char *salt = malloc(sizeof(char*)*2);
    *salt = (char){ 0 };
    memcpy(salt,hash,2);
    *(salt+2) = '\0';

    printf("Hash: %s\nSalt: %s\n", hash,salt);
    
    printf("Starting to crack...\n");
     
    if(dic_attk(hash,salt)||bruteforce(hash,salt))
        printf("Success!\n");
    else
        printf("Failed to crack password\n");

    free(salt);

    return 0;
}


bool crack(const char *key, const char *hash, const char *salt)
{
    if(strcmp(crypt(key,salt),hash) == 0)
        {
            printf("\nThe plaintext is: %s\n", key);
            return true;
        }
    return false;
}

bool dic_attk(const char *hash, const char *salt)
{
    printf("Starting dictionary attack...\n");
    
    FILE *dic = fopen("/usr/share/dict/words","r");
    if (dic == NULL)
    {
        printf("Couldn't open dictinoary\n");
    }
    else
    {
        char buffer[LENGTH+2];
        char *cipher = NULL;
        while (fgets(buffer, LENGTH+2, dic))
        {
            if(strlen(buffer) < 8)
            {
                if(crack(buffer,hash,salt))
                    return true;
            }
        }
        fclose(dic);
        free(cipher);
    }
    
    printf("Dictionary attack failed\n");
    return false;
}

bool bruteforce(const char *hash, const char *salt)
{
    printf("Starting Bruteforce attack...\n");
    
    const char values[] = { 'a','A','b','B','c','C','d','D','e',
                            'E','f','F','g','G','h','H','i','I',
                            'j','J','k','K','l','L','m','M','n',
                            'N','o','O','p','P','q','Q','r','R',
                            's','S','t','T','u','U','v','V','w',
                            'W','x','X','y','Y','z','Z','0','1',
                            '2','3','4','5','6','7','8','9','$'};    //size 62
    
    char cipher[] = {'a','a','a','a','a','a','a','a'};
    char *module = malloc(sizeof(char*)*8);
    *module = (char){ 0 };
    int pos[] =   {0,0,0,0,0,0,0,0};
    
    while(cipher[7] != '$')
    {
        for(int i=1; i<=8;i++)
        {
            memcpy(module,cipher,i);
            if(i != 7)
                module[i+1] = '\0';
           //printf("%s\n",module);
            if(crack(module,hash,salt))
            {
                free(module);
                return true;
            }
        }
        
        pos[0]++;
        
        if(cipher[0] == '$')
        {    
            for(int i=0; i<8; i++)
            {
                if(cipher[i] == '$')
                {
                    pos[i] = 0;
                    pos[i+1]++;
                    cipher[i] = values[pos[i]];
                    cipher[i+1] = values[pos[i+1]];
                }
            }
        }
        cipher[0] = values[pos[0]];
    }
    
    printf("Bruteforce failed\n");
    free(module);
    
    return false;
    
}
