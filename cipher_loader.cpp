#include "cipher_loader.h"
#include <windows.h>
#include <stdexcept>

using namespace std;

typedef void* (*CreateVigenereFunc)(const char*);
typedef char* (*EncryptFunc)(void*, const char*);
typedef char* (*DecryptFunc)(void*, const char*);
typedef void (*DestroyFunc)(void*);
typedef void (*FreeFunc)(char*);

CipherLoader::CipherLoader(const string& library_path) : lib_path(library_path) {}

string CipherLoader::encryptText(const string& text, const string& key) const {
    HMODULE handle = LoadLibraryA(lib_path.c_str());
    if (!handle) throw runtime_error("Failed to load DLL");

    CreateVigenereFunc create = (CreateVigenereFunc)GetProcAddress(handle, "cipher_create_vigenere");
    EncryptFunc encrypt = (EncryptFunc)GetProcAddress(handle, "cipher_encrypt");
    DestroyFunc destroy = (DestroyFunc)GetProcAddress(handle, "cipher_destroy");
    FreeFunc free_func = (FreeFunc)GetProcAddress(handle, "cipher_free");
    if (!create || !encrypt || !destroy || !free_func) {
        FreeLibrary(handle);
        throw runtime_error("Failed to get functions");
    }

    void* cipher = create(key.c_str());
    char* res_cstr = encrypt(cipher, text.c_str());
    string result(res_cstr);

    free_func(res_cstr);
    destroy(cipher);
    FreeLibrary(handle);

    return result;
}

string CipherLoader::decryptText(const string& text, const string& key) const {
    HMODULE handle = LoadLibraryA(lib_path.c_str());
    if (!handle) throw runtime_error("Failed to load DLL");

    CreateVigenereFunc create = (CreateVigenereFunc)GetProcAddress(handle, "cipher_create_vigenere");
    DecryptFunc decrypt = (DecryptFunc)GetProcAddress(handle, "cipher_decrypt");
    DestroyFunc destroy = (DestroyFunc)GetProcAddress(handle, "cipher_destroy");
    FreeFunc free_func = (FreeFunc)GetProcAddress(handle, "cipher_free");

    if (!create || !decrypt || !destroy || !free_func) {
        FreeLibrary(handle);
        throw runtime_error("Failed to get functions");
    }
    void* cipher = create(key.c_str());
    char* res_cstr = decrypt(cipher, text.c_str());

    string result(res_cstr);

    free_func(res_cstr);
    destroy(cipher);
    FreeLibrary(handle);

    return result;
}