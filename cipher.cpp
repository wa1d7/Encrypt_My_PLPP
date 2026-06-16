//
// Created by ignat on 17.06.2026.
//

#include "cipher.h"
CaesarCipher::CaesarCipher(int key) {
    key_ = key;
}
std::string CaesarCipher::encrypt(const std::string& text) {
    return text;
}
std::string CaesarCipher::decrypt(const std::string& text) {
    return text;
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