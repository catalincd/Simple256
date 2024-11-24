#pragma once
#include "substitution.h"
#include "permutation.h"
#include "vigenere.h"
#include "../utils/types.h"

void encrypt(uchar* data, uchar* key);
void decrypt(uchar* data, uchar* key);

void encrypt(char* data, char* key);
void decrypt(char* data, char* key);

std::string encrypt_cbc(char* data, char* key, int len);
std::string decrypt_cbc(char* data, char* key, int len);