#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h> //aux lib for check segment. NOT REQUIRED FOR dicitonary.c

#define LENGTH 45

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

int main (void)

{    
    root = NewNode();
    int count = 0;
    node* mark = root;
    
    FILE *dic = fopen("small","r"); //Opens dictionary
    if (dic == NULL)
    {
        printf("Failed to open Dic!");
        return -1;
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
    
    //Check
    string word = "roger";
    node *ptr = root;
    int index = 0;
    int WordLength = strlen(word);
    int Director[WordLength];
    for (int i = 0; i < WordLength; i++) //Fills array with word's letters
        Director[i] = word[i]-97;
    do
    {
        ptr=ptr->link[Director[index]];
        index++;
    }
    while (index != WordLength || ptr == NULL);
    if (index == WordLength)
        return 0;
    else
        return -1;

    return 0;
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
