#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdint>
#include <cstdio>

#include "../utils/types.h"

void encrypt_substitution(uchar* data, uchar* key);
void decrypt_substitution(uchar* data, uchar* key);