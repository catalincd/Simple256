#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdint>
#include <cstdio>
#include <chrono>

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

void calculate_difference(uchar* block1, uchar* block2, uchar* difference) {
    for (int i = 0; i < SIZE; i++) {
        difference[i] = block1[i] ^ block2[i];
    }
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

void differential_attack() {
    uchar difference_input[SIZE];
    uchar difference_output[SIZE];
    uchar* text1 = new uchar[SIZE];
    uchar* key1 = new uchar[SIZE];
    uchar* ctext1 = new uchar[SIZE];
    uchar* text2 = new uchar[SIZE];
    uchar* key2 = new uchar[SIZE];
    uchar* ctext2 = new uchar[SIZE];

    std::string _key1 = keygen(SIZE);
    std::string _key2 = keygen(SIZE);
    std::string _text1 = keygen(SIZE);
    std::string _text2 = keygen(SIZE);

    memcpy(text1, _text1.c_str(), SIZE);
    memcpy(text2, _text2.c_str(), SIZE);

    memcpy(ctext1, text1, SIZE);
    memcpy(ctext2, text2, SIZE);
    memcpy(key1, _key1.c_str(), SIZE);
    memcpy(key2, _key2.c_str(), SIZE);

    encrypt(text1, key1);
    encrypt(text2, key2);

    calculate_difference(text1, text2, difference_input); 
    calculate_difference(ctext1, ctext2, difference_output);

    std::cout << "Plaintext 1: ";
    printBytes(text1);
    std::cout << "Plaintext 2: ";
    printBytes(text2);
    std::cout << "Ciphertext 1: ";
    printBytes(ctext1);
    std::cout << "Ciphertext 2: ";
    printBytes(ctext2);

    std::cout << "Input Difference: ";
    printBytes(difference_input);
    
    std::cout << "Output Difference: ";
    printBytes(difference_output);
}

int main()
{
    
    differential_attack();
    
    return 0;
}