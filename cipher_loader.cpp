#include "cipher_loader.h"
#include <windows.h>
#include <stdexcept>

using namespace std;

typedef void* (*CreateCaesarFunc)(int);
typedef void* (*CreateVigenereFunc)(const char*);
typedef void* (*CreateAtbashFunc)();

typedef char* (*EncryptFunc)(void*, const char*);
typedef char* (*DecryptFunc)(void*, const char*);
typedef void (*DestroyFunc)(void*);
typedef void (*FreeFunc)(char*);

CipherLoader::CipherLoader(const string& library_path) : lib_path(library_path) {}

string CipherLoader::encryptText(const string& text, const string& key, CipherType type) const {
    HMODULE handle = LoadLibraryA(lib_path.c_str());
    if (!handle) throw runtime_error("failed to load DLL. Error code: " + to_string(GetLastError()));

    EncryptFunc encrypt = (EncryptFunc)GetProcAddress(handle, "cipher_encrypt");
    DestroyFunc destroy = (DestroyFunc)GetProcAddress(handle, "cipher_destroy");
    FreeFunc free_func = (FreeFunc)GetProcAddress(handle, "cipher_free");

    if (!encrypt || !destroy || !free_func) {
        FreeLibrary(handle);
        throw runtime_error("failed to get base functions");
    }

    void* cipher = nullptr;
    if (type == CipherType::CAESAR) {
        CreateCaesarFunc create = (CreateCaesarFunc)GetProcAddress(handle, "cipher_create_caesar");
        int int_key = 0;
        try { int_key = stoi(key); } catch(...) {}
        cipher = create(int_key);
    }
    else if (type == CipherType::ATBASH) {
        CreateAtbashFunc create = (CreateAtbashFunc)GetProcAddress(handle, "cipher_create_atbash");
        cipher = create();
    }
    else {
        CreateVigenereFunc create = (CreateVigenereFunc)GetProcAddress(handle, "cipher_create_vigenere");
        cipher = create(key.c_str());
    }

    if (!cipher) {
        FreeLibrary(handle);
        throw runtime_error("failed to create cipher");
    }

    char* res_cstr = encrypt(cipher, text.c_str());
    string result(res_cstr);

    free_func(res_cstr);
    destroy(cipher);
    FreeLibrary(handle);

    return result;
}

string CipherLoader::decryptText(const string& text, const string& key, CipherType type) const {
    HMODULE handle = LoadLibraryA(lib_path.c_str());
    if (!handle) throw runtime_error("failed to load DLL. Error code: " + to_string(GetLastError()));

    DecryptFunc decrypt = (DecryptFunc)GetProcAddress(handle, "cipher_decrypt");
    DestroyFunc destroy = (DestroyFunc)GetProcAddress(handle, "cipher_destroy");
    FreeFunc free_func = (FreeFunc)GetProcAddress(handle, "cipher_free");

    if (!decrypt || !destroy || !free_func) {
        FreeLibrary(handle);
        throw runtime_error("failed to get base functions");
    }

    void* cipher = nullptr;
    if (type == CipherType::CAESAR) {
        CreateCaesarFunc create = (CreateCaesarFunc)GetProcAddress(handle, "cipher_create_caesar");
        int int_key = 0;
        try { int_key = stoi(key); } catch(...) {}
        cipher = create(int_key);
    }
    else if (type == CipherType::ATBASH) {
        CreateAtbashFunc create = (CreateAtbashFunc)GetProcAddress(handle, "cipher_create_atbash");
        cipher = create();
    }
    else {
        CreateVigenereFunc create = (CreateVigenereFunc)GetProcAddress(handle, "cipher_create_vigenere");
        cipher = create(key.c_str());
    }

    if (!cipher) {
        FreeLibrary(handle);
        throw runtime_error("failed to create cipher");
    }

    char* res_cstr = decrypt(cipher, text.c_str());
    string result(res_cstr);

    free_func(res_cstr);
    destroy(cipher);
    FreeLibrary(handle);

    return result;
}