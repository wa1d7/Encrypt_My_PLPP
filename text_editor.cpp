#include "text_editor.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

TextEditor::TextEditor(CipherLoader* c) : cipher(c), active_tab(0) {
    tabs.push_back(Tab());
}

void TextEditor::newTab() {
    tabs.push_back(Tab());
    active_tab = tabs.size() - 1;
}

void TextEditor::switchTab(int index) {
    if (index >= 0 && index < tabs.size()) {
        active_tab = index;
    } else {
        std::cout << "err: invalid tab index!\n";
    }
}

void TextEditor::closeTab(int index) {
    if (index >= 0 && index < tabs.size()) {
        if (tabs.size() == 1) {
            tabs[0].text.clear();
            while(!tabs[0].undo_stack.empty()) tabs[0].undo_stack.pop();
            while(!tabs[0].redo_stack.empty()) tabs[0].redo_stack.pop();
        } else {
            tabs.erase(tabs.begin() + index);
            if (active_tab >= tabs.size()) {
                active_tab = tabs.size() - 1;
            }
        }
    } else {
        std::cout << "err: invalid tab index!\n";
    }
}

void TextEditor::listTabs() const {
    std::cout << "--- Tabs ---\n";
    for (size_t i = 0; i < tabs.size(); ++i) {
        std::cout << (i == active_tab ? "[*] " : "[ ] ")
                  << "Tab " << i << " (Lines: " << tabs[i].text.getLineCount() << ")\n";
    }
}

void TextEditor::saveState() {
    tabs[active_tab].undo_stack.push(tabs[active_tab].text);
    while(!tabs[active_tab].redo_stack.empty()) tabs[active_tab].redo_stack.pop();
}

void TextEditor::append(const std::string& str) {
    saveState();
    tabs[active_tab].text.appendText(str);
}

void TextEditor::undo() {
    if (tabs[active_tab].undo_stack.empty()) return;
    tabs[active_tab].redo_stack.push(tabs[active_tab].text);
    tabs[active_tab].text = tabs[active_tab].undo_stack.top();
    tabs[active_tab].undo_stack.pop();
}

void TextEditor::redo() {
    if (tabs[active_tab].redo_stack.empty()) return;
    tabs[active_tab].undo_stack.push(tabs[active_tab].text);
    tabs[active_tab].text = tabs[active_tab].redo_stack.top();
    tabs[active_tab].redo_stack.pop();
}

void TextEditor::saveToFile(const std::string& filename, const std::string& key, CipherType type) {
    std::string data = tabs[active_tab].text.serialize();
    std::string encrypted = cipher->encryptText(data, key, type);

    std::ofstream out(filename, std::ios::binary);
    out << encrypted;
}

void TextEditor::loadFromFile(const std::string& filename, const std::string& key, CipherType type) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) throw std::runtime_error("could not open file for loading");

    std::string encrypted((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    std::string decrypted = cipher->decryptText(encrypted, key, type);
    tabs[active_tab].text = Text::deserialize(decrypted);
}

void TextEditor::encryptDocument(const std::string& key, CipherType type) {
    saveState();
    std::string data = tabs[active_tab].text.serialize();
    std::string encrypted = cipher->encryptText(data, key, type);
    tabs[active_tab].text.clear();
    tabs[active_tab].text.appendText(encrypted);
}

void TextEditor::decryptDocument(const std::string& key, CipherType type) {
    saveState();
    std::string encrypted_data;
    for (int i = 0; i < tabs[active_tab].text.getLineCount(); ++i) {
        const Line* line = tabs[active_tab].text.getLine(i);
        encrypted_data += line->extract(0, line->length());
        if (i < tabs[active_tab].text.getLineCount() - 1) encrypted_data += "\n";
    }
    std::string decrypted = cipher->decryptText(encrypted_data, key, type);
    tabs[active_tab].text = Text::deserialize(decrypted);
}

void TextEditor::print() const {
    std::cout << "\n=== TAB " << active_tab << " ===";
    tabs[active_tab].text.printText();
}

void TextEditor::setCursor(int line, int pos) {
    tabs[active_tab].text.setCursor(line, pos);
}

int TextEditor::getCursorLine() const {
    return tabs[active_tab].text.getCursorLine();
}

int TextEditor::getCursorPos() const {
    return tabs[active_tab].text.getCursorPos();
}

void TextEditor::insertText(const std::string& text) {
    saveState();
    tabs[active_tab].text.insertText(getCursorLine(), getCursorPos(), text);
}

void TextEditor::deleteText(int char_count) {
    saveState();
    tabs[active_tab].text.deleteText(getCursorLine(), getCursorPos(), char_count);
}

void TextEditor::insertNewLine() {
    saveState();
    tabs[active_tab].text.insertNewLine();
}

void TextEditor::copy(int count) {
    clipboard = tabs[active_tab].text.copyText(getCursorLine(), getCursorPos(), count);
}

void TextEditor::paste() {
    if (clipboard.empty()) return;
    saveState();
    tabs[active_tab].text.insertText(getCursorLine(), getCursorPos(), clipboard);
}