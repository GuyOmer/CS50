#include <stdio.h>
#include <string.h>

#define PRECISON 150000

int main (int argc,char* argv[])
{
    if(argc == 1)
        return 1;
    const char* str = argv[1];
    int hashValue = 0;
    for (int Pos = 0, len = strlen(str); Pos < len; Pos++)
    {
        // use all elements
        hashValue = (hashValue << 4) + str[Pos]; // shift/mix
        int hiBits = hashValue & 0xF0000000; // get high nybble
        
        if (hiBits != 0)
            hashValue ^= hiBits >> 24;    //xor high nybble with second nybble
        
        hashValue &= ~hiBits; // clear high nybble
    }
    printf("%s --> %d\n", str, hashValue%PRECISON);
    
    return 0;
}
