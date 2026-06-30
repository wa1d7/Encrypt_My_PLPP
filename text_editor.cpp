#include "text_editor.h"
#include <fstream>
#include <stdexcept>

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

void TextEditor::redo() {
    if (redo_stack.empty()) return;
    undo_stack.push(current_text);
    current_text = redo_stack.top();
    redo_stack.pop();
}

void TextEditor::saveToFile(const std::string& filename, const std::string& key, CipherType type) {
    std::string data = current_text.serialize();
    std::string encrypted = cipher->encryptText(data, key, type);

    std::ofstream out(filename, std::ios::binary);
    out << encrypted;
}

void TextEditor::loadFromFile(const std::string& filename, const std::string& key, CipherType type) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) throw std::runtime_error("could not open file for loading");

    std::string encrypted((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    std::string decrypted = cipher->decryptText(encrypted, key, type);
    current_text = Text::deserialize(decrypted);
}

void TextEditor::print() const {
    current_text.printText();
}

void TextEditor::setCursor(int line, int pos) {
    current_text.setCursor(line, pos);
}

int TextEditor::getCursorLine() const {
    return current_text.getCursorLine();
}

int TextEditor::getCursorPos() const {
    return current_text.getCursorPos();
}

void TextEditor::insertText(const std::string& text) {
    saveState();
    current_text.insertText(getCursorLine(), getCursorPos(), text);
}

void TextEditor::deleteText(int char_count) {
    saveState();
    current_text.deleteText(getCursorLine(), getCursorPos(), char_count);
}

void TextEditor::insertNewLine() {
    saveState();
    current_text.insertNewLine();
}

void TextEditor::copy(int count) {
    clipboard = current_text.copyText(getCursorLine(), getCursorPos(), count);
}

void TextEditor::paste() {
    if (clipboard.empty()) return;
    saveState();
    current_text.insertText(getCursorLine(), getCursorPos(), clipboard);
}