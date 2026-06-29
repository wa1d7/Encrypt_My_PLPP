#include "text_editor.h"
#include <iostream>

int main() {
    CipherLoader loader("cipher.dll");
    TextEditor editor(&loader);

    std::string cmd;
    std::cout << "editor commands: append, undo, save, load, print, exit" << std::endl;

    while (true) {
        std::cout << "> ";
        std::cin >> cmd;

        if (cmd == "exit") break;

        if (cmd == "append") {
            std::string text;
            std::getline(std::cin >> std::ws, text);
            editor.append(text);
        } else if (cmd == "undo") {
            editor.undo();
        } else if (cmd == "print") {
            editor.print();
        } else if (cmd == "save") {
            std::string path, key;
            std::cin >> path >> key;
            editor.saveToFile(path, key);
        } else if (cmd == "load") {
            std::string path, key;
            std::cin >> path >> key;
            editor.loadFromFile(path, key);
        }
    }
    return 0;
}