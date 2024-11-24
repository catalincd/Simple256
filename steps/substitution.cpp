#include "substitution.h"

void encrypt_substitution(uchar* data, uchar* key)
{
    uchar subTable[256];
    int sum = 0;
    for(int i=0;i<SIZE;i++)
        sum += key[i];

    for(int i=0;i<256;i++)
    {
        subTable[i] = (i + sum) % 256;
    }

    for(int i=0;i<SIZE;i++)
    {
        data[i] = subTable[data[i]];
    }
}

void decrypt_substitution(uchar* data, uchar* key)
{
        uchar subTable[256];
    int sum = 0;
    for(int i=0;i<SIZE;i++)
        sum += key[i];

    for(int i=0;i<256;i++)
    {
        subTable[(i + sum) % 256] = i;
    }

    for(int i=0;i<SIZE;i++)
    {
        data[i] = subTable[data[i]];
    }
}