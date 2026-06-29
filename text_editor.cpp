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