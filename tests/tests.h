#pragma once
#include <vector>
#include <string>

std::string char2Hex(const char* data, size_t length);
std::vector<char> hex2Char(const std::string& hex);