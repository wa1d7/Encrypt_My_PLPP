
#ifndef ENCRYPT_CIPHER_LOADER_H
#define ENCRYPT_CIPHER_LOADER_H
#include <string>

enum class CipherType {
    CAESAR,
    VIGENERE,
    ATBASH
};

class CipherLoader {
    std::string lib_path;

public:
    CipherLoader(const std::string& library_path);
    std::string encryptText(const std::string& text, const std::string& key, CipherType type = CipherType::VIGENERE) const;
    std::string decryptText(const std::string& text, const std::string& key, CipherType type = CipherType::VIGENERE) const;
};

#endif //ENCRYPT_CIPHER_LOADER_H
