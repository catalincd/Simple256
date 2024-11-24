#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdint>
#include <cstdio>

#include "steps/cipher.h"
#include "utils/types.h"


int main(int argc, char** argv)
{
    std::string enced = encrypt_cbc("aea46ae075e34edf3d2aac5faa41a6d5", "aea46ae075e34edf3d2aac5faa41a6d5", 32);

    char* outDec = new char[enced.length()];
    memcpy(outDec, enced.c_str(), enced.length());

    std::string deced = decrypt_cbc(outDec, "aea46ae075e34edf3d2aac5faa41a6d5", enced.length());
    std::cout << enced << std::endl;
    std::cout << deced << std::endl;

    // This is really not what it should be, has to be rewritten sometime
    if(argc < 4)
    {
        std::cout << "Encrypt:\n";
        std::cout << "simple256 -e <data> <key>\n";
        std::cout << "Decrypt:\n";
        std::cout << "simple256 -d <data> <key>\n";
        exit(0);
    }

    if(!strcmp(argv[1], "-e"))
    {
        char data[strlen(argv[2])];
        memcpy(data, argv[2], strlen(argv[2]));

        char key[strlen(argv[3])];
        memcpy(key, argv[3], strlen(argv[3]));

        if(strlen(argv[2]) != 32)
        {
            std::cout << "Key length must be 32\n";
            exit(0);
        }

        if(strlen(argv[3]) != 32)
        {
            std::cout << "Data length must be greater than 32\n";
            exit(0);
        }

        std::cout << encrypt_cbc(data, key, strlen(argv[2])) << std::endl;
    }

    if(!strcmp(argv[1], "-d"))
    {
        char data[strlen(argv[2])];
        memcpy(data, argv[2], strlen(argv[2]));

        char key[strlen(argv[3])];
        memcpy(key, argv[3], strlen(argv[3]));

        if(strlen(argv[2]) != 32)
        {
            std::cout << "Key length must be 32\n";
            exit(0);
        }

        if(strlen(argv[3]) != 32)
        {
            std::cout << "Data length must be greater than 32\n";
            exit(0);
        }

        std::cout << decrypt_cbc(data, key, strlen(argv[2])) << std::endl;
    }

    return 0;
}