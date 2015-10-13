/*************************************************************************
 * sll.c
 *
 * Implements a simple singly-linked list structure for ints.
 ************************************************************************/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// the size of our test list: feel free to adjust as you wish!
#define TEST_SIZE 10

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

/**
* Creates new node.
*/
node* new(void)
{
    node* new = malloc(sizeof(node));
    new->i = 0;
    new->next = NULL;
    return new;
}

/**
 * Returns the length of the list.
 */
int length(void)
{
    int len = 0;
    node* ptr = first;
    while (ptr->next != NULL)
        {
        len++;
        ptr = ptr->next;
        }
    return len;
}

/**
 * Returns true if a node in the list contains the value i and false
 * otherwise.
 */
bool contains(int i)
{
    node* ptr = new();
    while (ptr->next != NULL)
        {
        if ( ptr->i == i)
            return true;
        ptr = ptr->next;
        }
    return false;
}

/**
 * Puts a new node containing i at the front (head) of the list.
 */
void prepend(int i)
{
    node* newptr = new();
    newptr->i = i;
    if (first->next == NULL)
        {
        first->next = newptr;
        newptr->next = NULL;
        return;
        }
    newptr->next = first->next;
    first->next = newptr;
}

/**
 * Puts a new node containing i at the end (tail) of the list.
 */
void append(int i)
{
    node* newptr = new();
    newptr->i = i;
    if(first == NULL)
        {
        first = new();
        first->next = newptr;
        return;
        }
    node* ptr = first;
    while (ptr->next != NULL)
        ptr = ptr->next;
    ptr->next = newptr;
    return;   
}

/**
 * Puts a new node containing i at the appropriate position in a list
 * sorted in ascending order.
 */
void insert_sorted(int i)
{
    node* newptr = new();
    newptr->i = i;
    if (first == NULL)  //If list is empty.
        {
        first = new();
        first->next = newptr;
        return;
        }
    node* preptr = first;
    node* aftptr = first->next;
    if ((preptr->i) > i)                       //Incase new node is smaller than the first node.
            prepend(i);
    while ((preptr->i) > i || i > (aftptr->i)) //Checks wheter new node belongs
        {                                      //Between 2 existing nodes.
        if (aftptr->next == NULL)              //Incase new node belongs to the end.
            {
            append(i);
            return;
            }
        preptr = preptr->next;
        aftptr = aftptr->next;
        }
    newptr->next = preptr->next;
    preptr->next = newptr;
    return;
}

/**
 * Implements some simple test code for our singly-linked list.
 */
int main(void)
{
    first = new();
    printf("Prepending ints 0-%d onto the list...", TEST_SIZE);
    for (int i = 0; i < TEST_SIZE; i++)
    {
        prepend(i);
    }
    printf("done!\n");

    printf("Making sure that the list length is indeed %d...", TEST_SIZE);
    assert(length() == TEST_SIZE);
    printf("good!\n");

    printf("Making sure that values are arranged in descending order...");
    node* n = first;
    first->i = 10;
    for (int i = 0; i < TEST_SIZE; i++)
    {
        assert(n != NULL);
        assert((n->i)-1 == TEST_SIZE - i - 1);
        n = n->next;
    }
    printf("good!\n");

    printf("Freeing the list...");
    while (first != NULL)
    {
        node* next = first->next;
        free(first);
        first = next;
    }
    printf("done!\n");

    printf("Appending ints 0-%d to the list...", TEST_SIZE);
    for (int i = 0; i < TEST_SIZE; i++)
    {
        append(i);
    }
    printf("done!\n");

    printf("Making sure that the list length is indeed %d...", TEST_SIZE);
    assert(length() == TEST_SIZE);
    printf("good!\n");

    printf("Making sure that values are arranged in ascending order...");
    n = first->next;
    for (int i = 0; i < TEST_SIZE; i++)
    {
        assert(n != NULL);
        assert(n->i == i);
        n = n->next;
    }
    printf("good!\n");

    printf("Freeing the list...");
    while (first != NULL)
    {
        node* next = first->next;
        free(first);
        first = next;
    }
    printf("done!\n");

    printf("Inserting %d random ints to the list...", TEST_SIZE);
    for (int i = 0; i < TEST_SIZE; i++)
    {
        insert_sorted(rand() % TEST_SIZE);
    }
    printf("done!\n");

    printf("Making sure that the list length is indeed %d...", TEST_SIZE);
    assert(length() == TEST_SIZE);
    printf("good!\n");

    printf("Making sure that values are arranged in sorted order...");
    n = first;
    int prev = 0;
    for (int i = 0; i < TEST_SIZE; i++)
    {
        assert(n != NULL);
        assert(n->i >= prev);
        prev = n->i;
        n = n->next;
    }
    printf("good!\n");

    printf("Freeing the list...");
    while (first != NULL)
    {
        node* next = first->next;
        free(first);
        first = next;
    }
    printf("done!\n");

    printf("\n********\nSuccess!\n********\n");

    return 0;
}
