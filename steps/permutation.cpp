#include "permutation.h"



uchar permute_bytes(uchar data, uint8_t* permTable)
{
    uchar output = 0;
    for (int i=0;i<8;i++)
    {
        int bit = (data >> permTable[i]) & 1;
        output |= (bit << i);
    }
    return output;
}



void encrypt_permutation(uchar* data, uchar* key)
{
    uint8_t permTable[8];
    for(int i=0;i<8;i++)
    {
        permTable[i] = i;
    }

    for(int i=0;i<8;i++)
    {
        int temp = permTable[i];
        permTable[i] = permTable[key[i] % 8];
        permTable[key[i] % 8] = temp;
    }

    for(int i=0;i<SIZE;i++)
    {
        data[i] = permute_bytes(data[i], permTable);
    }
}

void decrypt_permutation(uchar* data, uchar* key)
{
    uint8_t permTable[8];
    uint8_t revPermTable[8];
    for(int i=0;i<8;i++)
    {
        permTable[i] = i;
    }

    for(int i=0;i<8;i++)
    {
        int temp = permTable[i];
        permTable[i] = permTable[key[i] % 8];
        permTable[key[i] % 8] = temp;
    }

    for(int i=0;i<8;i++)
    {
        revPermTable[permTable[i]] = i;
    }

    for(int i=0;i<SIZE;i++)
    {
        data[i] = permute_bytes(data[i], revPermTable);
    }
}