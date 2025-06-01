#include <gtest/gtest.h>

#include "utils.h"
#include "../src/steps/cipher.h"

TEST(IntegrationTesting, IVTest) {
    RAND_SEED = 9999;
    const std::string target_iv = "evP53NkJC0ETeMZfvnhFB2LGmmvDxZHR";

    const std::string data = "8d777f385d3dfec8815d20f7496026dc";
    const std::string key = "3c6e0b8a9c15224a8228b9a98ca1531d";
    
    const auto hash = reinterpret_cast<char*>(encrypt_cbc(data.c_str(), key.c_str(), 32));
    EXPECT_EQ(0, strncmp(hash, target_iv.c_str(), 32));
}

TEST(IntegrationTesting, EncryptionTest) {
    const std::string target_hex = "706b444854786d4d5231384e326c396b3838456d4c674e3763434354743972571e750ae53d13c157b1395ed98964f0a1eb645c6aada1e2eca0a957dfce450a02";

    const std::string data = "8d777f385d3dfec8815d20f7496026dc";
    const std::string key = "3c6e0b8a9c15224a8228b9a98ca1531d";
    const std::string iv = "pkDHTxmMR18N2l9k88EmLgN7cCCTt9rWu";

    const auto hash = reinterpret_cast<char*>(encrypt_cbc(data.c_str(), key.c_str(), iv.c_str(), 32));
    EXPECT_EQ(0, strncmp(hash, &(hex2Char(target_hex)[0]), 64));
}

TEST(IntegrationTesting, DecryptionTest) {
    const std::string target_data = "8d777f385d3dfec8815d20f7496026dc";

    const std::string hash = "706b444854786d4d5231384e326c396b3838456d4c674e3763434354743972571e750ae53d13c157b1395ed98964f0a1eb645c6aada1e2eca0a957dfce450a02";
    const std::string key = "3c6e0b8a9c15224a8228b9a98ca1531d";

    const auto data = reinterpret_cast<char*>(decrypt_cbc(&(hex2Char(hash))[0], key.c_str(), 64));
    EXPECT_EQ(0, strncmp(target_data.c_str(), data, 32));
}
