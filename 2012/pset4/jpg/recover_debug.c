/****************************************************************************
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 ***************************************************************************/
 
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void find_start(FILE* card);
int new(FILE* card, int fname, FILE* pic);
void create(FILE* card, FILE* pic);

typedef uint8_t  BYTE;

typedef struct 
{ 
    BYTE  firstB; 
    BYTE  secondB; 
    BYTE  thirdB; 
    BYTE  fourthB; 
} __attribute__((__packed__)) 
SIGNTURE; 

int main (void)
{
    FILE* card = fopen("card.raw","r");
    if (card==NULL)
        {
        printf("Could not open \"card.raw\"");
        return 1;
        }
    int fname =-1;
    
    find_start(card);
    FILE* pic = fopen("recover.c","r");
    new(card, fname, pic);
    
    fclose(card);
    if(fname != 0)
     return fname;
    else
     return 0;
}

    void find_start(FILE* card)
{   
    SIGNTURE sign;
    printf("%ld ", ftell(card));
    fread(&sign,sizeof(SIGNTURE),1,card);
    if (sign.firstB == 0xff && sign.secondB == 0xd8 && sign.thirdB == 0xff && (sign.fourthB == 0xe0 || sign.fourthB == 0xe1))
        {
        fseek(card, -1*sizeof(SIGNTURE), SEEK_CUR);
        printf("\nGot It!!! At location: %ld \n", ftell(card));
        return;
        }
    else
    {
        fseek(card,sizeof(BYTE)*512-sizeof(SIGNTURE), SEEK_CUR);
        find_start(card);
    }
}

    int new(FILE* card, int fname, FILE* pic)
{
    SIGNTURE sign;
    if (fread(&sign,sizeof(SIGNTURE),1,card) != 0)
        if (sign.firstB == 0xff && sign.secondB == 0xd8 && sign.thirdB == 0xff && (sign.fourthB == 0xe0 || sign.fourthB == 0xe1))
         {
            fclose(pic);
            fname++;
            char picn[50];
            sprintf(picn, "%03d.jpg", fname);
            FILE* pic = fopen(picn,"a+");
            if (pic == NULL)
                 {
                  printf("Could not new %03d.jpg\n", fname);
                  return fname;
                 }
            fseek(card,-1*(sizeof(SIGNTURE)), SEEK_CUR);
            printf("\nCreated %03d.jpg:\n%ld ", fname, ftell(card));
            create(card,pic);
            return new(card, fname, pic);
         }
         else
         {
           fseek(card,-1*(sizeof(SIGNTURE)), SEEK_CUR);
           create(card,pic);
           return new(card, fname, pic);
         }
    else
         return 0;
}

    void create (FILE* card, FILE* pic)
{
           BYTE* part[512];
           fread(&part,sizeof(BYTE),512,card);
           fwrite(&part,sizeof(BYTE),512,pic);
           printf("%ld ", ftell(card));
           return;
}
