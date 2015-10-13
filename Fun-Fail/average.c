#include <stdio.h>
#include <cs50.h>



typedef struct node
{
    // the value to store in this node
    int i;
    // the % to store in this node
    int p;

    // the link to the next node in the list
    struct node* next;
}
node;

node* new();
void append(int i, int p);
void puller(int count, int total, float points[]);
void score(int total, float points[]);
void new_grade();
void clear();

// declare the first node of our list (as a global variable)
node* first = NULL;

int main (void)

{
    //clear();
    int total_p = 0;
    printf("Average Cacluator:\n"); 
    while(true)
    {
    printf("Enter Grade: ");                     //Get inputs
    int i = GetInt();
    int p;
    if (i !=-1)                                  //Kill Switche #2 (-1)
     {
        printf("Enter Prcentage: ");
        p = GetInt();
        while (p == 0 || total_p + p > 100)     //Verfaction 
           {
            printf("Invaild prcentage Enterd!\n");
            printf("Enter Prcentage: ");
            p = GetInt();
           }
        printf("\n");
    total_p += p;
    if (total_p == 100)
        break;
    append(i,p);
     }
    else
        break;
    }
    
    printf("Grades Summary:\n");
    int total = 1;
    node * ptr = first;
    while (ptr != NULL) //Counts how many grades entered
        {
         total += 1;
         ptr = ptr->next;
        }
    printf("Total: %d.\n" , total);
    /**if (total != 2)
        total++;**/
    float points[total];
    puller(0, total, points);
    score(total, points);
    return 0;
}

/**
 * Creates a new node.
**/

node* new(void)
{
    node* new = malloc(sizeof(node));
    new->i = 0;
    new->p = 0;
    new->next = NULL;
    return new;
}

/**
 * Adds nodes to the tail.
**/

void append(i,p)
{
    node* newptr = new();
    newptr->i = i;
    newptr->p = p;
    if(first == NULL)
        {
        first = newptr;
        return;
        }
    node* ptr = first;
    while (ptr->next != NULL)
        ptr = ptr->next;
    ptr->next = newptr;
    return;   
}


void clear()
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Prints Grades sum up + insert sums into points[].
**/

void puller(int count, int total, float points[])
{
    //Diagnostics
    printf("Count: %d, Total: %d\n", count, total);
    //*Diagnostics
    node* ptr = first;
    for (int j = 0; j < count; j++) //Goes to the correct node.
        {ptr = ptr->next;
        printf("ptr i = %d , p = %d\n", ptr->i, ptr->p);}
    printf("\nExit ptr i = %d , p = %d", ptr->i, ptr->p);
    if (ptr->next == NULL)
        printf(" NULL.\n");
    printf("Grade #%d: %d  %d%c.\n", count+1, ptr->i, ptr->p, 37);
    if ((ptr->next) == NULL)  //If last node the list.
         {
            points[total-count] =((float)(ptr->p)/100)*(ptr->i);
            return;
         }
    else
         {
            points[count] = ((float)(ptr->p)/100)*(ptr->i);
            puller(count+1,total, points);
         }
    
}

/**
 * Calculates the average and prints it.
**/ 

void score(int total, float points[])
{
    float average = 0;
    for (int i = 0; i < total; i++)
        average += points[i];
    printf("Average Score: %.2f\n", average);
    return;
}
