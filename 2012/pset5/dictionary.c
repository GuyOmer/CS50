/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

#define SIZE 1500000

typedef struct node
{
    char* word;
    struct node* next;
}
node;


int hash (const char* str);
bool place (const char* str,int key);
node* NewNode(const char* str);
bool cmp (const char* a, const char* b);
char *strdup(const char *str);


node* table[SIZE];
int count = 0;


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int key = hash(word);
    
    node* ptr = table[key];
    while(ptr != NULL)
        {
            if(cmp(word,ptr->word))
                return true;
            ptr = ptr->next;
        }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{

    int value = 0;
    
    FILE *dic = fopen(dictionary,"r"); //opens dictionary
    if (dic == NULL)
        return false;
    
    char buffer[LENGTH+2];    
    while (fgets(buffer, LENGTH+2, dic))   //reads the word + \0 and \n
    {
        count++;
        buffer[strlen(buffer)-1] = '\0';
        value = hash(buffer);
        
        if(!place(buffer,value))
            return false;
    }
    
    fclose(dic);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for(int i = 0; i < SIZE; i++)
    {
        node* ptr = table[i];
        while(ptr != NULL)
            {
                node *temp = ptr;
                ptr = ptr->next;
                free(temp->word);
                free(temp);
            }
    }
    return true;
}

int hash(const char* str)
{
/*    int hashValue = 0;*/
/*    for (int Pos = 0, len = strlen(str); Pos < len; Pos++)*/
/*    {*/
/*        // use all elements*/
/*        hashValue = (hashValue << 4) + tolower(str[Pos]); // shift/mix*/
/*        int hiBits = hashValue & 0xF0000000; // get high nybble*/
/*        */
/*        if (hiBits != 0)*/
/*            hashValue ^= hiBits >> 24;    //xor high nybble with second nybble*/
/*        */
/*        hashValue &= ~hiBits; // clear high nybble*/
/*    }*/
/*    return hashValue % SIZE;*/

    unsigned h = 5684;
    while (*str)
        h = h * 101 + tolower((unsigned char) *str++);
    return h%SIZE;

}

bool place(const char* str, int key)
{
    if (table[key] == NULL)         //free space on mian chain
        {
            table[key] = NewNode(str);
            strcpy(table[key]->word, str);
        }  
    else                           //not free
        {
            node* ptr = table[key];
            while(ptr->next != NULL)
                ptr = ptr->next;
                
            node* new = NewNode(str);
            strcpy(new->word,str);
            ptr->next = new;
            
        }
        
    return true;
}

node* NewNode (const char* str)
{
    node* new = malloc(sizeof(node));
    new->next = NULL;
    new->word = strdup((char*)str);
    
    return new;
}

bool cmp (const char* a, const char* b)
{
   int la = strlen(a), lb = strlen(b);
   la+=lb;
    if (strlen(a) != strlen(b))
        return false;

    for(int i = 0, len = strlen(a); i < len; i++)
        {
            if (tolower(a[i]) != tolower(b[i]))
                return false;
        }
    return true;
}

char *strdup(const char *str)
{
    int n = strlen(str) + 1;
    char *dup = malloc(n);
    if(dup)
    {
        strcpy(dup, str);
    }
    return dup;
}
