#include <stdio.h>
#include <stdbool.h>

#include "forest.h"
#include "huffile.h"
#include "tree.h"

//prototypes
Tree* combine(Tree* a, Tree* b);

int main (int argc, char* argv[])
{
    //check command
    if(argc !=3)
    {
        printf("Usage: ./puff input output\n");
        return 1;
    }
    //open input
    Huffile* hf = hfopen(argv[1], "r");
    if (hf == NULL)
    {
        printf("Couldn't open Huffed file!\n");
        return 1;
    }
    //read header
    Huffeader header;
    if(!hread(&header, hf))
    {
        printf("Couldn't read Huff file header!\n");
        return 1;
    }
    
    //verify MAGIC
    if(header.magic != MAGIC)
    {
        printf("Not a Huffed File!\n");
        return 1;
    }
    
    
    //validate checksum
    int checksum = header.checksum;
    
    for(int i = 0; i< SYMBOLS; i++)
        checksum-=header.frequencies[i];
    
    if(checksum!=0)
    {
        printf("Bad checksum! Bad huffing.\n");
        return 1;
    }
    
    //define forset
    Forest* forest = mkforest();
    
    
    //plant all "non 0 frequency" symbols
    for(int i = 0; i < SYMBOLS; i++)
    {
       Tree* new = mktree();                   //allocate tree
       new->frequency = header.frequencies[i]; //set frequency
       new->symbol = i;                        //set symbol
       
       plant(forest,new);                      //place in forest
    }

    FILE* output = fopen(argv[2],"w");         //create output file
    if (output == NULL)
    {
        printf("couldn't open %s.\n", argv[2]);
        return 1;
    }

    bool run = true;
    Tree* root = NULL;
    while(run)
    {
        Tree* first = pick(forest);
        Tree* second = pick(forest);
        
        //if only one tree left in forest (all others were already combined)
        if(second == NULL)
        {
            run = false;
            root = first;
        }
        else
            plant(forest, combine(first,second));
    }
    
    Tree* seek = root;
    int bit = bread(hf);
    
    //run till EOF
    while(bit != EOF)
    {
        if (bit == 0)
            seek = seek->left;   //go left (bit 0)
        else
            seek = seek->right;  //go right (bit 1)
            
        if (seek->right == NULL && seek->left == NULL) //got to a leaf, print symbol
        {
            fprintf(output,"%c",seek->symbol);
            seek = root;                               //reset root for next run
        }
        bit = bread(hf);                               //read next bit for
    }
    
    //free root
    rmtree(root);
    //free the forest
    rmforest(forest);
    //close input
    hfclose(hf);
    //close output
    fclose(output);
    
    return 0;
}

Tree* combine(Tree* a, Tree* b)
{
    Tree* combined = mktree();
    
    combined->frequency = a->frequency + b->frequency;
    combined->left = a;
    combined->right = b;
    
    return combined;
}
