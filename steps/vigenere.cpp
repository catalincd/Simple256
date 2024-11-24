#include "vigenere.h"

void encrypt_vigenere(uchar* data, uchar* key)
{
    for(int i=0;i<SIZE;i++)
    {
        data[i] += key[i];
    }
}

void decrypt_vigenere(uchar* data, uchar* key)
{
    for(int i=0;i<SIZE;i++)
    {
        data[i] -= key[i];
    }
}