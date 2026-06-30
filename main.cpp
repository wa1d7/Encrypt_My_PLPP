#include "text_editor.h"
#include <iostream>
#include <string>

CipherType getCipherType() {
    std::cout << "?hoose cipher (1: vigenere, 2: caesar, 3: atbash): ";
    int choice;
    std::cin >> choice;
    if (choice == 2) return CipherType::CAESAR;
    if (choice == 3) return CipherType::ATBASH;
    return CipherType::VIGENERE;
}

int main() {
    CipherLoader loader("cipher.dll");
    TextEditor editor(&loader);

    std::string cmd;
    std::cout << "available commands: print, append, move <l> <p>, insert <text>,\n"
              << "newline, encrypt, decrypt, del <count>, copy <count>, paste, undo, save, load, exit\n";

    while (true) {
        std::cout << "\n> ";
        std::cin >> cmd;

        if (cmd == "exit") break;

        try {
            if (cmd == "print") {
                editor.print();
            }
            else if (cmd == "append") {
                std::string text;
                std::getline(std::cin >> std::ws, text);
                editor.append(text);
            }
            else if (cmd == "move") {
                int l, p; std::cin >> l >> p;
                editor.setCursor(l, p);
            }
            else if (cmd == "insert") {
                std::string text;
                std::getline(std::cin >> std::ws, text);
                editor.insertText(text);
            }
            else if (cmd == "newline") {
                editor.insertNewLine();
            }
            else if (cmd == "del") {
                int count; std::cin >> count;
                editor.deleteText(count);
            }
            else if (cmd == "copy") {
                int count; std::cin >> count;
                editor.copy(count);
            }
            else if (cmd == "paste") {
                editor.paste();
            }
            else if (cmd == "undo") {
                editor.undo();
            }
            // --- ????? ??????? ?? PDF ---
            else if (cmd == "encrypt") {
                std::string key;
                std::cout << "Key: "; std::cin >> key;
                CipherType type = getCipherType();
                editor.encryptDocument(key, type);
                std::cout << "Document encrypted in memory!\n";
            }
            else if (cmd == "decrypt") {
                std::string key;
                std::cout << "Key: "; std::cin >> key;
                CipherType type = getCipherType();
                editor.decryptDocument(key, type);
                std::cout << "Document decrypted in memory!\n";
            }
            // -----------------------------
            else if (cmd == "save") {
                std::string path, key;
                std::cout << "File path: "; std::cin >> path;
                std::cout << "Key: "; std::cin >> key;
                CipherType type = getCipherType();
                editor.saveToFile(path, key, type);
                std::cout << "Saved successfully!\n";
            }
            else if (cmd == "load") {
                std::string path, key;
                std::cout << "File path: "; std::cin >> path;
                std::cout << "Key: "; std::cin >> key;
                CipherType type = getCipherType();
                editor.loadFromFile(path, key, type);
                std::cout << "Loaded successfully!\n";
            }
            else {
                std::cout << "Unknown command!\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "[ERROR] " << e.what() << "\n";
        }
    }
}