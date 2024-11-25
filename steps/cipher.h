#pragma once
#include "substitution.h"
#include "permutation.h"
#include "vigenere.h"
#include "../utils/types.h"

void encrypt(uchar* data, uchar* key);
void decrypt(uchar* data, uchar* key);

void encrypt(char* data, char* key);
void decrypt(char* data, char* key);

uchar* _encrypt_cbc(uchar* data, uchar* key, int len);
uchar* _decrypt_cbc(uchar* data, uchar* key, int len);


template <typename T, typename K>
uchar* encrypt_cbc(T* data, K* key, int len)
{
    uchar* p_data = reinterpret_cast<uchar*>(data);
    uchar* p_key = reinterpret_cast<uchar*>(key);
    return _encrypt_cbc(p_data, p_key, len);
}

template <typename T, typename K>
uchar* decrypt_cbc(T* data, K* key, int len)
{
    return _decrypt_cbc(reinterpret_cast<uchar*>(data), reinterpret_cast<uchar*>(key), len);
}