#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cs50.h>

typedef struct node
{
    int value;
    struct node* left;
    struct node* right;
}
node;

node* newnode(int val);
bool contain(int value);
bool insert(int value);

node* root;

int main(void)

{
    int arr[] = {1,2,3,4,5,6,7,8,9,-1};
    
    root = newnode(7);
    
    for(int i = 0; arr[i] != -1; i++)
        {
            if(insert(arr[i]))
                printf("Good Insert!\n");
            else
                printf("Bad Insert!\n");
        }
    
    while(1)
    {
        printf("Enter Number to look for:\n");
        if(contain(GetInt()))
            printf("Found!\n");
        else
            printf("Not Found!\n");
    }
    return 0;
}

node* newnode(int val)
{
    node* new = malloc(sizeof(node));
    new->value = val;
    new->left = NULL;
    new->right = NULL;
    
    return new;
}

bool contain(int value)
{
    node* look = root;
    while(look != NULL)
    {
        if(look->value == value)
            return true;
        else if (value > look->value)
            look = look->right;
        else
            look = look->left;
    }
    return false;
}

bool insert(int value)
{
    node* ptr = root;
    node* prv;;
    while(ptr != NULL)
    {
        prv = ptr;
        if(ptr->value == value)
            return false;
        else if (value > ptr->value)
            ptr = ptr->right;
        else
            ptr = ptr->left;
    }
    if(value > prv->value)
        prv->right = newnode(value);
    else
        prv->left = newnode(value);
    return true;
    
}

