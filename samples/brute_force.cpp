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

void test_keyspace()
{
    // 31 cuz for some fking reason it dies after 10 seconds when using 32
    std::string _text = keygen(31);
    uchar* text = new uchar[31];
    memcpy(text, _text.c_str(), 31);
    std::string _key = keygen(31);

    std::string _test = keygen(31);
    uchar* test = new uchar[31];
    memcpy(test, _test.c_str(), 31);

    std::string _once = keygen(31);
    uchar* once = new uchar[31];

    memcpy(once, _once.c_str(), 31);

    encrypt(test, once);

    while(1) {
        std::string _key = keygen(31);

        uchar* key = new uchar[31];

        memcpy(key, _key.c_str(), 31);

        encrypt(text, key);
        
        if (std::strcmp(reinterpret_cast<char *>(text), reinterpret_cast<char *>(test)) == 0) {
            std::cout << "Found matching key: " << std::hex << key << std::endl;
            break;
        }
        else
        {
            std::cout << "Wrong key: " << std::hex << key << std::endl;
        }
    }   
}

int main()
{
    test_keyspace();

    return 0;
}