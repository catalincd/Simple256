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

void printBytes(uchar* c, std::string msg = "", int _size = SIZE)
{
    std::cout << msg << std::hex;
    for(int i=0;i<_size;i++)
    {
        std::cout << std::uppercase << std::hex << (int)c[i] << std::dec << ' ';
    }
    std::cout << '\n';
}

template <typename Func>
long long measureExecutionTime(Func&& func)
{
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<long long, std::nano> duration = end - start;
    return duration.count();
}

void encryptAndMeasure(uchar* text, uchar* key)
{
    auto encryptFunc = [&]() {
        encrypt(text, key);
    };

    long long execTime = measureExecutionTime(encryptFunc);
    std::cout << "Encryption execution time: " << execTime << " ns\n";
}

void decryptAndMeasure(uchar* text, uchar* key)
{
    auto decryptFunc = [&]() {
        decrypt(text, key);
    };

    long long execTime = measureExecutionTime(decryptFunc);
    std::cout << "Decryption execution time: " << execTime << " ns\n";
}

void measureTimeOfEncrypt(uchar *text, uchar *key)
{
    auto start = std::chrono::high_resolution_clock::now();

    encrypt(text, key);
    printBytes(text, "ENC:");

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    std::cout << "Encryption time: " << duration.count() << " seconds" << std::endl;
}

void measureTimeOfDecrypt(uchar *text, uchar *key)
{
    auto start = std::chrono::high_resolution_clock::now();

    decrypt(text, key);
    printBytes(text, "DEC:");

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    std::cout << "Decryption time: " << duration.count() << " seconds" << std::endl;
}

int main()
{
    for(int i = 0; i < 10; i++)
    {
        std::string _key = keygen(SIZE);
        std::string _text = keygen(SIZE);

        uchar* key = new uchar[SIZE];
        uchar* text = new uchar[SIZE];

        memcpy(key, _key.c_str(), SIZE);
        memcpy(text, _text.c_str(), SIZE);

        printBytes(key, "KEY:");
        printBytes(text, "TEXT:");

        measureTimeOfEncrypt(text, key);
        measureTimeOfDecrypt(text, key);

        delete key;
        delete text;
    }
    
    return 0;
}