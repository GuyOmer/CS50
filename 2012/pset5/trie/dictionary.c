/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 *
 *
 * Notes:
 * Load() segfaults on the second not-exsisting value, not first! check if node == NULL
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

/**
 * typedef for nodes
 */

typedef struct node
{
    char letter;
    struct node* link[27];    //  0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|26
                              //  a|b|c|d|e|f|g|h|i|j|k |l |m |n |o |p |q |r |s |t |u |v |w |x |y |z | '
    bool fullword;
}
node;

//Prototypes
node* NewNode(void);

//Trie's Root
node* root;

//Words counter
int count = 0;
int lcount = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* watch = root;
    int i = 0;
        
    for(;watch != NULL && word[i]!='\0'; i++)
        {
        if((int)word[i] == 39)
        {
            if(watch->link[26]==NULL)
                return false;
            watch = watch->link[26];
        }
            
        else
            watch = watch->link[(int)tolower(word[i])-97];        
        }        
        
    if (watch == NULL) return false;                                //fail safe
    
    if(watch->fullword)
    {
            
        for(int i = 0; word[i]!='\0';i++)
            printf("%c",word[i]);
         printf("\n");
        return true;
    }
    else
        return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    count = 0;
    root = NewNode();
    FILE *dic = fopen(dictionary,"r"); //opens dictionary
    if (dic == NULL)
        return false;
          
    char buffer[LENGTH+2];  //last char of every string is NULL
    
    while (fgets(buffer, LENGTH+2, dic)) //reads word from dictionary
    {
    count++;
    
    node *ptr = root;
    for (int i = 0; (int)buffer[i] != 10; i++) //run while current char isnt NULL
        {
        if ((int)buffer[i] == 39) // if apostrophe
            {
             if(ptr->link[26] == NULL)  //emptey link
             {
                 node* node = NewNode();
                 node->letter = buffer[i];
                 ptr->link[26] = node;
             }
             ptr = ptr->link[26];       //move forward in tree
            }
        else 
         {
            if(ptr->link[(int)buffer[i]-97] ==  NULL)  //emptey link
            {
                 node* node = NewNode();
                 node->letter = buffer[i];
                 ptr->link[(int)buffer[i]-97] = node;
             }
            ptr = ptr->link[(int)buffer[i]-97];        //move forward in tree
         }
        }
    ptr->fullword = true;
    }
    
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
bool unload(void)             //Seg faults here, code supposed to work (see test.c), debug and find problems
{
/*    int delc = 0, depth = 0;*/
/*    int bi = 0;*/
/*    node* before;*/
/*    */
/*    FILE *log = fopen("log.txt","w"); //opens dictionary*/
/*    if (log == NULL)*/
/*        return false;*/
/*    */
/*    before = root;*/
/*    */
/*    while(root!=NULL)*/
/*    {*/
/*        node* fin = before;*/
/*        */
/*        for(int i =0; i<27;i++)*/
/*        {*/
/*            //if(fin->link[i] != NULL && fin->link[i]->letter != '#')*/
/*            if(fin->link[i] != NULL)*/
/*                {*/
/*                before = fin;*/
/*                bi = i;*/
/*                depth++;*/
/*                fin=fin->link[i];*/
/*                i=0;*/
/*                }*/
/*        }*/
/*        delc++;lcount--;*/
/*        //fprintf(log,"Freed: %c\nDepth: %d\nNodes freed: %d\nNodes to free: %d\n\n",fin->letter,depth,delc, lcount);*/
/*        printf("Freed: %c\nDepth: %d\nNodes freed: %d\nNodes to free: %d\n\n",fin->letter,depth,delc, lcount);*/
/*        depth--;*/
/*        fin->letter = '#';*/
/*        before->link[bi] = NULL;*/

/*        free(fin);*/
/*    }*/
    return true;
}

/**
 * Creates new node.
 */
node* NewNode(void)
{
    node* new = malloc(sizeof(node));
    new->letter = '#';
    for( int i = 0; i < 27; i++)
        new->link[i] = NULL;
    new->fullword = false;
    
    lcount++;
    return new;
}
