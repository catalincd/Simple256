#include "cipher.h"

#define ROUNDS 4

void encrypt(uchar* data, uchar* key)
{
    for(int i=0;i<ROUNDS;i++)
    {
        encrypt_substitution(data, key);
        encrypt_permutation(data, key);
    }

    encrypt_vigenere(data, key);
}

void decrypt(uchar* data, uchar* key)
{
    decrypt_vigenere(data, key);

    for(int i=0;i<ROUNDS;i++)
    {
        decrypt_permutation(data, key);
        decrypt_substitution(data, key);
    }
}

void encrypt(char* data, char* key)
{
    encrypt(reinterpret_cast<uchar*>(data), reinterpret_cast<uchar*>(key));
}

void decrypt(char* data, char* key)
{
    decrypt(reinterpret_cast<uchar*>(data), reinterpret_cast<uchar*>(key));
}

void printBytes(uchar* c, std::string msg = "", int _size = SIZE)
{
    std::cout << msg << std::hex;
    for(int i=0;i<_size;i++)
    {
        std::cout << std::uppercase << std::hex << (int)c[i] << std::dec << ' ';
    }
    std::cout << '\n';
}

uchar* _encrypt_cbc(uchar* data, uchar* key, int len)
{
    std::string iv = keygen(32);

    uchar* result = new uchar[len + 32];
    uchar* last = new uchar[32]; 

    memcpy(last, iv.c_str(), 32);
    memcpy(result, iv.c_str(), 32);

    int current = 32;

    while(current < len + 32)
    {
        for(int i=0;i<32;i++)
        {
            last[i] ^= data[i + current - 32];
        }
        
        encrypt(last, key);
        memcpy(result + current, last, 32);
        current += 32;
    }

    delete[] last;
    return result;
}

uchar* _decrypt_cbc(uchar* data, uchar* key, int len)
{
    uchar* result = new uchar[len - 32];
    uchar* last = new uchar[32]; 
    uchar* block = new uchar[32]; 

    memcpy(last, data, 32); // iv
    int current = 32;

    while(current < len)
    {
        memcpy(block, data + current, 32);
        decrypt(block, key);

        for(int i=0;i<32;i++)
        {
            block[i] ^= last[i];
        }

        memcpy(last, data + current, 32);
        memcpy(result + current - 32, block, 32);
        current += 32;
    }

    delete[] last;
    delete[] block;
    return result;
}
