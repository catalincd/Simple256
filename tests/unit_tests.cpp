#include <gtest/gtest.h>

#include "utils.h"
#include "../src/steps/cipher.h"
#include "../src/steps/permutation.h"
#include "../src/steps/substitution.h"
#include "../src/steps/vigenere.h"

TEST(UnitTesting, PermutationTest) {
    std::string target_permutation = "5829cdcdcd2dcc58c929cc292da9ac5858c8c9294c482dcd49d84d484c4d29ac";
    uchar initial[] = "8d777f385d3dfec8815d20f7496026dc";
    uchar key[] = "3c6e0b8a9c15224a8228b9a98ca1531d";

    encrypt_permutation(initial, key);    
    EXPECT_EQ(target_permutation, char2Hex(reinterpret_cast<char*>(initial), 32));
}

TEST(UnitTesting, SubstitutionTest) {
    std::string target_substitution = "c2eec1c1c1f0bdc2bfeebdeef0efedc2c2bbbfeebcbaf0c1bec3c0babcc0eeed";
    uchar initial[] = "8d777f385d3dfec8815d20f7496026dc";
    uchar key[] = "3c6e0b8a9c15224a8228b9a98ca1531d";

    encrypt_substitution(initial, key);    
    EXPECT_EQ(target_substitution, char2Hex(reinterpret_cast<char*>(initial), 32));
}

TEST(UnitTesting, VigenereTest) {
    std::string target_vigenere = "6bc76d9c67c86b996ec76499989797997063679c9469c7706c9c9761676995c7";
    uchar initial[] = "8d777f385d3dfec8815d20f7496026dc";
    uchar key[] = "3c6e0b8a9c15224a8228b9a98ca1531d";

    encrypt_vigenere(initial, key);    
    EXPECT_EQ(target_vigenere, char2Hex(reinterpret_cast<char*>(initial), 32));
}

TEST(UnitTesting, RoundsTest) {
    std::string target_rounds = "7c00373737e5127cac001200e521297c7c3eac00bacbe537872622cbba220029";
    uchar initial[] = "8d777f385d3dfec8815d20f7496026dc";
    uchar key[] = "3c6e0b8a9c15224a8228b9a98ca1531d";

    for(int i=0;i<100;i++)
    {
        encrypt_permutation(initial, key);    
        encrypt_substitution(initial, key);    
    }
    EXPECT_EQ(target_rounds, char2Hex(reinterpret_cast<char*>(initial), 32));
}