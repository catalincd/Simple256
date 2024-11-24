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