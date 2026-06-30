#include "text_editor.h"
#include <iostream>
#include <string>

CipherType getCipherType() {
    std::cout << "Choose cipher (1: Vigenere, 2: Caesar, 3: Atbash): ";
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
    std::cout << "Available commands:\n"
              << "[Text]: print, append, move <l> <p>, insert <text>, newline, del <count>, copy <count>, paste\n"
              << "[Tabs]: tabnew, tabs, tabswitch <id>, tabclose <id>\n"
              << "[File/Crypto]: encrypt, decrypt, save, load, undo, exit\n";

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
            else if (cmd == "tabnew") {
                editor.newTab();
                std::cout << "New tab created.\n";
                editor.listTabs();
            }
            else if (cmd == "tabs") {
                editor.listTabs();
            }
            else if (cmd == "tabswitch") {
                int idx; std::cin >> idx;
                editor.switchTab(idx);
            }
            else if (cmd == "tabclose") {
                int idx; std::cin >> idx;
                editor.closeTab(idx);
                editor.listTabs();
            }

            else if (cmd == "encrypt") {
                std::string key;
                std::cout << "Key: "; std::cin >> key;
                CipherType type = getCipherType();
                editor.encryptDocument(key, type);
                std::cout << "document encrypted in memory!\n";
            }
            else if (cmd == "decrypt") {
                std::string key;
                std::cout << "Key: "; std::cin >> key;
                CipherType type = getCipherType();
                editor.decryptDocument(key, type);
                std::cout << "document decrypted in memory!\n";
            }
            else if (cmd == "save") {
                std::string path, key;
                std::cout << "file path: "; std::cin >> path;
                std::cout << "key: "; std::cin >> key;
                CipherType type = getCipherType();
                editor.saveToFile(path, key, type);
                std::cout << "saved successfully!\n";
            }
            else if (cmd == "load") {
                std::string path, key;
                std::cout << "file path: "; std::cin >> path;
                std::cout << "key: "; std::cin >> key;
                CipherType type = getCipherType();
                editor.loadFromFile(path, key, type);
                std::cout << "loaded successfully!\n";
            }
            else {
                std::cout << "unknown command!\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "err " << e.what() << "\n";
        }
    }
    return 0;
}