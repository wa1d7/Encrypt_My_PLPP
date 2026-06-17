//
// Created by ignat on 17.06.2026.
//

#include "cipher.h"
#include <cctype>
CaesarCipher::CaesarCipher(int key) {
    key_ = key;
}
std::string CaesarCipher::encrypt(const std::string& text) {
    std::string result = "";

    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';

            int shift = (c - base + key_) % 26;
            if (shift < 0) {
                shift += 26;
            }

            result += (char)(base + shift);
        } else {
            result += c;
        }
    }
    return result;
}
std::string CaesarCipher::decrypt(const std::string& text) {
    CaesarCipher reverseCipher(-key_);
    return reverseCipher.encrypt(text);
}

VigenereCipher::VigenereCipher(const std::string& key) {
    key_ = key;
}
std::string VigenereCipher::encrypt(const std::string& text) {
    std::string result = "";
    int keyIndex = 0;
    int keyLength = key_.length();

    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';

            char keyChar = key_[keyIndex % keyLength];

            int shift = tolower(keyChar) - 'a';

            int newCharOffset = (c - base + shift) % 26;
            result += (char)(base + newCharOffset);

            keyIndex++;
        } else {
            result += c;
        }
    }
    return result;
}

std::string VigenereCipher::decrypt(const std::string& text){
    std::string result = "";
    int keyIndex = 0;
    int keyLength = key_.length();

    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';

            char keyChar = key_[keyIndex % keyLength];
            int shift = tolower(keyChar) - 'a';

            int newCharOffset = (c - base - shift) % 26;

            if (newCharOffset < 0) {
                newCharOffset += 26;
            }

            result += (char)(base + newCharOffset);
            keyIndex++;
        } else {
            result += c;
        }
    }
    return result;
};
AtbashCipher::AtbashCipher() {
}

std::string AtbashCipher::encrypt(const std::string& text) {
    std::string result = "";

    for (char c : text) {
        if (isalpha(c)) {
            if (islower(c)) {
                result += (char)('z' - (c - 'a'));
            } else {
                result += (char)('Z' - (c - 'A'));
            }
        } else {
            result += c;
        }
    }
    return result;
}

std::string AtbashCipher::decrypt(const std::string& text) {
    return encrypt(text);
}

#include "include/cipher_api.h"
#include <cstring>

extern "C" {

EXPORT cipher_t* cipher_create_caesar(int key) {
    return (cipher_t*) new CaesarCipher(key);
}

EXPORT cipher_t* cipher_create_vigenere(const char* key) {
    return (cipher_t*) new VigenereCipher(std::string(key));
}
EXPORT cipher_t* cipher_create_atbash() {
    return (cipher_t*) new AtbashCipher();
}

EXPORT char* cipher_encrypt(cipher_t* cipher, const char* text) {

    Cipher* c = (Cipher*) cipher;

    std::string result = c->encrypt(std::string(text));

    char* c_str = new char[result.length() + 1];
    std::strcpy(c_str, result.c_str());
    return c_str;
}

EXPORT char* cipher_decrypt(cipher_t* cipher, const char* text) {
    Cipher* c = (Cipher*) cipher;
    std::string result = c->decrypt(std::string(text));

    char* c_str = new char[result.length() + 1];
    std::strcpy(c_str, result.c_str());
    return c_str;
}

EXPORT void cipher_destroy(cipher_t* cipher) {
    Cipher* c = (Cipher*) cipher;
    delete c;
}

EXPORT void cipher_free(char* str) {
    delete[] str;
}

}