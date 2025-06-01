#include <gtest/gtest.h>
#include <iomanip>
#include "tests.h"
#include "../src/steps/cipher.h"

TEST(SimpleTests, IVTest) {
    RAND_SEED = 9999;
    const std::string target_iv = "evP53NkJC0ETeMZfvnhFB2LGmmvDxZHR";

    const std::string data = "8d777f385d3dfec8815d20f7496026dc";
    const std::string key = "3c6e0b8a9c15224a8228b9a98ca1531d";
    
    const auto hash = reinterpret_cast<char*>(encrypt_cbc(data.c_str(), key.c_str(), 32));
    EXPECT_EQ(0, strncmp(hash, target_iv.c_str(), 32));
}

TEST(SimpleTests, EncryptionTest) {
    const std::string target_hex = "706b444854786d4d5231384e326c396b3838456d4c674e3763434354743972571e750ae53d13c157b1395ed98964f0a1eb645c6aada1e2eca0a957dfce450a02";

    const std::string data = "8d777f385d3dfec8815d20f7496026dc";
    const std::string key = "3c6e0b8a9c15224a8228b9a98ca1531d";
    const std::string iv = "pkDHTxmMR18N2l9k88EmLgN7cCCTt9rWu";

    const auto hash = reinterpret_cast<char*>(encrypt_cbc(data.c_str(), key.c_str(), iv.c_str(), 32));
    EXPECT_EQ(0, strncmp(hash, &(hex2Char(target_hex)[0]), 64));
}

TEST(SimpleTests, DecryptionTest) {
    const std::string target_data = "8d777f385d3dfec8815d20f7496026dc";

    const std::string hash = "706b444854786d4d5231384e326c396b3838456d4c674e3763434354743972571e750ae53d13c157b1395ed98964f0a1eb645c6aada1e2eca0a957dfce450a02";
    const std::string key = "3c6e0b8a9c15224a8228b9a98ca1531d";

    const auto data = reinterpret_cast<char*>(decrypt_cbc(&(hex2Char(hash))[0], key.c_str(), 64));
    EXPECT_EQ(0, strncmp(target_data.c_str(), data, 32));
}


std::vector<char> hex2Char(const std::string& hex) {
    std::vector<char> result;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteStr = hex.substr(i, 2);
        char byte = static_cast<char>(std::stoi(byteStr, nullptr, 16));
        result.push_back(byte);
    }
    return result;
}

std::string char2Hex(const char* data, size_t length) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (size_t i = 0; i < length; ++i) {
        oss << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(data[i]));
    }
    return oss.str();
}