#include <iostream>
#include "include/cipher_api.h"
int main() {
    std::cout << "Encryption library test\n";
    const char* message = "Hello, World!";

    int caesar_key = 3;
    cipher_t* caesar = cipher_create_caesar(caesar_key);

    char* enc_caesar = cipher_encrypt(caesar, message);
    char* dec_caesar = cipher_decrypt(caesar, enc_caesar);

    std::cout << "caesar cipher - key: " << caesar_key << "\n";
    std::cout << "original:  " << message << "\n";
    std::cout << "encrypted: " << enc_caesar << "\n";
    std::cout << "decrypted: " << dec_caesar << "\n";

    cipher_free(enc_caesar);
    cipher_free(dec_caesar);
    cipher_destroy(caesar);


    const char* vigenere_key = "KEY";
    cipher_t* vigenere = cipher_create_vigenere(vigenere_key);

    char* enc_vig = cipher_encrypt(vigenere, message);
    char* dec_vig = cipher_decrypt(vigenere, enc_vig);

    std::cout << "vigenere cipher - key: " << vigenere_key << "\n";
    std::cout << "original:  " << message << "\n";
    std::cout << "encrypted: " << enc_vig << "\n";
    std::cout << "decrypted: " << dec_vig << "\n";

    cipher_free(enc_vig);
    cipher_free(dec_vig);
    cipher_destroy(vigenere);


    cipher_t* atbash = cipher_create_atbash();

    char* enc_atbash = cipher_encrypt(atbash, message);
    char* dec_atbash = cipher_decrypt(atbash, enc_atbash);

    std::cout << "atbash cipher - bonus ball\n";
    std::cout << "original:  " << message << "\n";
    std::cout << "encrypted: " << enc_atbash << "\n";
    std::cout << "decrypted: " << dec_atbash << "\n\n";

    cipher_free(enc_atbash);
    cipher_free(dec_atbash);
    cipher_destroy(atbash);

    return 0;

}