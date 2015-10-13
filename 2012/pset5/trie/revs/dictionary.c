/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

//TODO: load\check is broken! test word = AUSTIN

typedef struct node
{
    char letter;
    struct node* link[27];
    bool fullword;
}
node;

typedef struct watch
{
    node* point;
}
watch;

//Prototypes
node* NewNode(void);

//Trie's Root
node* root;

//Words counter
int count = 0;


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node *ptr = root;
    int index = 0;
    int WordLength = strlen(word);
    int Director[WordLength];
    for (int i = 0; i < WordLength; i++) //Fills array with word's letters
    {
        Director[i] = (word[i] > 97) ? word[i]-97 : word[i]-65;  //incase upper\lower case letters
        //Director[i] = word[i]-97;
    }
    do
    {
        ptr=ptr->link[Director[index]];
        index++;
    }
    while (index != WordLength || ptr->letter == word[index] || ptr != NULL);
    if (index == WordLength)
        return true;
    else
        return false;

}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    node* root = NewNode();
    int count = 0;
    node* mark = root;
    FILE *dic = fopen("small","r"); //Opens dictionary
    if (dic == NULL)
    {
        printf("Failed to open Dic!");
        return false;
    }
    char buffer[LENGTH+2];
    while (fgets(buffer, LENGTH + 2, dic)) //Reads from dictionary
    {
        count++;
        mark->fullword = true;
        node* mark = root;
        int len = strlen(buffer)-1;   // (-1) cuz of \n (A in hex-SEE xxd)
        for(int i = 0; i < len; i++)
        {
            node* new = NewNode();
            new->letter = buffer[i];
            if ((int)buffer[i] == 39) //If '
            {
             mark->link[26] = new;
             mark = new;
            }
            else if (mark->link[(int)buffer[i]-97]== NULL)  //If the link doesn't already exists
            {
             mark->link[(int)buffer[i]-97] = new;
             mark = new;
            }
            else // If Link exists
             mark = mark->link[(int)buffer[i]-97];
        }
        mark->fullword = true;
        buffer[0] = '0';
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
bool unload(void)
{
    node* killer = root;
    do 
    {
    //node* killer = root;
    for (int i = 0; i < 27; i++)
        {
        if (killer->link[i] != NULL)
            {
            killer = killer->link[i];
            i =0;
            }
        }
        free(killer);
    }
    while (root != killer);
    free(killer);
    return true;
}

/**
* Creates new node.
*/
node* NewNode(void)
{
    node* new = malloc(sizeof(node));
    new->letter = '#';
    new->link[0] = 0;
    new->fullword = false;
    return new;
}
