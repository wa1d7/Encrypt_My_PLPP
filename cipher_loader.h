
#ifndef ENCRYPT_CIPHER_LOADER_H
#define ENCRYPT_CIPHER_LOADER_H
#include <string>

class CipherLoader {
    std::string lib_path;

public:
    explicit CipherLoader(const std::string& library_path);

    std::string encryptText(const std::string& text, const std::string& key) const;
    std::string decryptText(const std::string& text, const std::string& key) const;
};
#endif //ENCRYPT_CIPHER_LOADER_H
