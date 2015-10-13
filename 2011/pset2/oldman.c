#include <stdio.h>
#include <cs50.h>

int
main(void)
{
const char *num[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};	
const char *sen[] = { "on my thumb", "on my shoe", "on my knee", "on my door", "on my hive", "on my sticks", "up in heaven", "on my gate", "on my spine", "once again" };
 
for (int i= 0; i<10;i++)
{
printf("This old man, he played %s\nHe played knick-knack %s\nKnick-knack paddywhack, give your dog a bone \n This old man came rolling home", num[i], sen[i]);
}
}
