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