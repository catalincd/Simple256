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
    if(argc < 4)
    {
        std::cout << "Encrypt:\n";
        std::cout << "simple256 -e <data> <key>\n";
        std::cout << "Decrypt:\n";
        std::cout << "simple256 -d <data> <key>\n";
    }
}