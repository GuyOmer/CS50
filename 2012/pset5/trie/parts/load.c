/****************************************************************************
 * load.c
 *
 * Bugs:
 * 1. 45 letters long words causes seg fault (try "small1").
 *
 * Implemention of the load func. DONE!
 ***************************************************************************/

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>  //DEBUG PURPOSE ONLY! delete at dictionary.c

#define LENGTH 45

typedef struct node
{
    char letter;
    struct node* link[27];
    bool fullword;
}
node;

//Prototypes
node* NewNode(void);

int main (void)

{

    //Log 1
    remove("log.txt");
    FILE *log;
    log = fopen("log.txt","a");
    if(log == NULL)
        printf("Couldn't create log.txt.");
    //End of Log 1
    
    node* root = NewNode();
    int count = 0;
    node* mark = root;
    FILE *dic = fopen("penu","r"); //Opens dictionary
    if (dic == NULL)
    {
        printf("Failed to open Dic!");
        return -1;
    }
    
    char buffer[LENGTH+2];
    buffer[0] = '0';        //for debugging only!
        
    while (fgets(buffer, LENGTH + 2, dic)) //Reads from dictionary
    {
    count++;
    mark->fullword = true;
    mark = root;
    int len = strlen(buffer)-1;   // (-1) cuz of \n (A in hex) ***SEE xxd
    
    //Log 2
    
    fprintf(log,"%d# ", count);
    
    printf("\nCurrent Word: %d ",count);
    for (int dig1 = 0; dig1 < len; dig1++)
    {
        printf("%c", buffer[dig1]);
        fprintf(log,"%c", buffer[dig1]);
    }
    printf("\n");
    fprintf(log,"\n");
    
    // End of log 2
   
    for(int i = 0; i < len; i++)  
    {
    node* new = NewNode();
    new->letter = buffer[i];
    //Log 3
    printf("%c", new->letter);
    fprintf(log,"%d: %c --> %d\n",i,new->letter,(int)new->letter);
    //End of Log 3
    
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
    //Log 4
    printf("   ...Check.\n");
    fprintf(log,"\n");
    fflush(log);
    }
    
    
    
    //Check
    printf("\nDONE!\n\n");
    node *ptr = root;
    int c = 0;
    //int loc[6] = {17,14,6,4,17}; //Manual loc input
    string word = "guy";
    int len = strlen(word);
    int loc[len];
    for(int i=0; i < len;i++)
        {
            loc[i] = (int)word[i]-97;
        }
    do
    {
        ptr=ptr->link[loc[c]];
        c++;
        printf("%d Check!\n", c);
    }
    while ((c!=(len) && ptr->fullword != true) && ptr != NULL);
    if (c == len)
        printf("Success!\n");
    else
        printf("Fail!\n");

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
