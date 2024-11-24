#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdint>
#include <cstdio>

#include "../steps/cipher.h"
#include "../utils/types.h"


std::string keygen(int length)
{
    static int RAND_INT = 0;
    std::string uchars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string key;
    key.reserve(length);
    
    std::srand((RAND_INT++) * 10000);

    for (int i = 0; i < length; i++)
    {
        key += uchars[std::rand() % uchars.size()];
    }
    return key;
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



int main()
{
    std::string _key = keygen(SIZE);
    std::string _text = keygen(SIZE);

    uchar* key = new uchar[SIZE];
    uchar* text = new uchar[SIZE];

    memcpy(key, _key.c_str(), SIZE);
    memcpy(text, _text.c_str(), SIZE);

    printBytes(key, "KEY:");
    std::cout<<key<<std::endl<<std::endl;

    printBytes(text, "TEXT:");
    std::cout<<text<<std::endl<<std::endl;

    encrypt(text, key);
    printBytes(text, "ENC:");
    std::cout<<text<<std::endl<<std::endl;

    
    decrypt(text, key);
    printBytes(text, "DEC:");
    std::cout<<text<<std::endl;
}