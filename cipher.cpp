//
// Created by ignat on 17.06.2026.
//

#include "cipher.h"
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
    return text;
}

std::string VigenereCipher::decrypt(const std::string& text){
    return text;
};