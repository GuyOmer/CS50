#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h> //aux lib for check segment. NOT REQUIRED FOR dicitonary.c

#define LENGTH 45 //length needs to be +1

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
void check(void);           //Delete, debug purposes only

//Trie's Root
node* root;

//Words counter
int count = 0;

int main (void)

{    
    count = 0;
    root = NewNode();
    FILE *dic = fopen("large","r"); //opens dictionary
    if (dic == NULL)
    {
        printf("Failed to open Dic!");
        return -1;
    }
    
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
    printf("\n");
    }
    
    check();
    
    
    return 0;
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
    return new;
}


void check(void)
{
    node* watch = root;
    do
    {
    printf("Go to letter: ");
    char to = GetChar();
    watch = watch->link[((int)to)-97];
    }
    while(watch != NULL);
    return;
}
