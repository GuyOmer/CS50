#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    // the value to store in this node
    int i;

    // the link to the next node in the list
    struct node* next;
}
node;

// declare the first node of our list (as a global variable)
node* first = NULL;


node* new(void)
{
    node* newptr = malloc(sizeof(node));
    return newptr;
}


int main(void)
{
    node* i = new();
    //node* newptr = malloc(sizeof(node));
    printf("%d\n", *i);
    
    return 0;

}
