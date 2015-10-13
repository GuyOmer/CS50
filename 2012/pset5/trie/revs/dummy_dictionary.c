/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"


//Prototypes
node* new(void);


typedef struct node
{
    char letter;
    node* link[28];
    bool fullword;
}
node;

typedef struct watch
{
    node* point;
}
watch;

//Trie's Root
node* root;

//Words counter
int count = 0;


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    root = new();
    FILE *dic = fopen(dictionary,"r"); //Opens dictionary
    if (dic == NULL)
    {
        printf("Could not open \"%s\".\n",dictionary);
        return false;
    }
    
    char buffer[LENGTH+2];
    watch *ptr;
    while (fgets(buffer, LENGTH + 2, dic)) //Reads from dictionary
    {
    count++;
    ptr->point = NULL
    int len = strlen(buffer);
    for(int i = 0; i < len; i++)
    {
        if ((int)buffer[i] == 10)  //If NULL
        {
            printf("%d: 0 - NULL\n\n",i);
            continue;
        }
        node* cur = new();
        cur->letter = buffer[i];
        if (root->link[(int)cur->letter-96] == NULL) //If first time in trie root's.   ***BROKEN: USES EACH LETTER AS IF ITS THE FIRST LETTER OF THE WORD
            {
            root->link[(int)cur->letter-96] = cur;
            ptr->point = cur;
            //continue;
            }
        else
        {
            if (ptr->point != NULL)
                {
                node* trav = ptr->point;
                if (trav->link[int)cur->letter-96] == NULL) //If no link exists
                {
                    trav->link[(int)cur->letter-96] = cur;
                    ptr->point = cur;
                }
                else //If link exists
                    ptr->point = trav->link[int)cur->letter-96];
                }
            else
                {
                
                }
        }
        
    }
    }
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}

/**
* Creates new node.
*/
node* new(void)
{
    node* new = malloc(sizeof(node));
    new->letter = NULL;
    new->links[] = NULL;
    new->fullword = false;
    return new;
}
