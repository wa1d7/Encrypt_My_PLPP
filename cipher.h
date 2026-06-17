//
// Created by ignat on 17.06.2026.
//

#ifndef CIPHER_H
#define CIPHER_H

#include <string>

class Cipher {
public:
    virtual std::string encrypt(const std::string& text) = 0;
    virtual std::string decrypt(const std::string& text) = 0;
    virtual ~Cipher() = default;
};

class CaesarCipher : public Cipher {
    int key_;
public:
    CaesarCipher(int key);
    std::string encrypt(const std::string& text) override;
    std::string decrypt(const std::string& text) override;
};

class VigenereCipher : public Cipher {
    std::string key_;
public:
    VigenereCipher(const std::string& key);
    std::string encrypt(const std::string& text) override;
    std::string decrypt(const std::string& text) override;
};
class AtbashCipher : public Cipher {
public:
    AtbashCipher();
    std::string encrypt(const std::string& text) override;
    std::string decrypt(const std::string& text) override;
};

#endif // CIPHER_H
