#include <iomanip>
#include <vector>
#include <string>


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