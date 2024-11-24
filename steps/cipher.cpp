#include "cipher.h"

void encrypt(uchar* data, uchar* key)
{
    encrypt_substitution(data, key);
    encrypt_permutation(data, key);
    encrypt_vigenere(data, key);
}

void decrypt(uchar* data, uchar* key)
{
    decrypt_vigenere(data, key);
    decrypt_permutation(data, key);
    decrypt_substitution(data, key);
}

void encrypt(char* data, char* key)
{
    encrypt(reinterpret_cast<uchar*>(data), reinterpret_cast<uchar*>(key));
}

void decrypt(char* data, char* key)
{
    decrypt(reinterpret_cast<uchar*>(data), reinterpret_cast<uchar*>(key));
}


// TO DO: PADDING

std::string encrypt_cbc(char* data, char* key, int len)
{
    int current = 0;
    std::string result = keygen(32);
    std::string last = result; //iv
    
    std::string temp;
    temp.reserve(32);

    while(len > 0)
    {
        int target = (len < 32? len : 32);
        for(int i=0;i<target;i++)
        {
            temp = data[current + i] ^ last[i];
        }

        char payload[32];
        strcpy(payload, temp.c_str());
        encrypt(payload, key);
        result += std::string(payload);
        
        last = temp;
        current += 32;
        len -= 32;
    }

    return result;
}

std::string decrypt_cbc(char* data, char* key, int len)
{
    int current = 32;
    len -= 32;
    std::string tempData(data);

    std::string result = "";
    std::string last = tempData.substr(0, 32); //iv
   
    while(len > 0)
    {
        int target = (len < 32? len : 32);

        std::string temp = tempData.substr(current, current + 32);
        
        char* payload = new char[32];
        memcpy(payload, temp.c_str(), 32);
        decrypt(payload, key);
        temp = std::string(payload);

        

        for(int i=0;i<32;i++)
        {
            temp[i] ^= last[i];
        }

        result += temp;
        
        last = temp; // to do
        current += 32;
        len -= 32;
        delete[] payload;
    }

    return result;
}