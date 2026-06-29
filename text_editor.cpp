#include "text_editor.h"
#include <fstream>

TextEditor::TextEditor(CipherLoader* c) : cipher(c) {}

void TextEditor::saveState() {
    undo_stack.push(current_text);
    while(!redo_stack.empty()) redo_stack.pop();
}

void TextEditor::append(const std::string& str) {
    saveState();
    current_text.appendText(str);
}

void TextEditor::undo() {
    if (undo_stack.empty()) return;
    redo_stack.push(current_text);
    current_text = undo_stack.top();
    undo_stack.pop();
}

void TextEditor::saveToFile(const std::string& filename, const std::string& key) {
    std::string data = current_text.serialize();
    std::string encrypted = cipher->encryptText(data, key);
    
    std::ofstream out(filename, std::ios::binary);
    out << encrypted;
}
void TextEditor::loadFromFile(const std::string& filename, const std::string& key) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) throw std::runtime_error("сould not open file for loading");

    std::string encrypted((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    std::string decrypted = cipher->decryptText(encrypted, key);
    current_text = Text::deserialize(decrypted);
}
void TextEditor::print() const {
    current_text.printText();
}