#include "types.h"

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