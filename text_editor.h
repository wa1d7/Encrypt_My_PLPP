#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include "text.h"
#include "cipher_loader.h"
#include <vector>
#include <stack>

class TextEditor {
    Text current_text;
    std::stack<Text> undo_stack;
    std::stack<Text> redo_stack;
    std::string clipboard;
    CipherLoader* cipher;

    void saveState();

public:
    TextEditor(CipherLoader* c);

    void append(const std::string& str);
    void undo();
    void redo();
    void print() const;

    void insertNewLine();
    void copy(int count);
    void paste();

    void setCursor(int line, int pos);
    int getCursorLine() const;
    int getCursorPos() const;
    void insertText(const std::string& text);
    void deleteText(int char_count);

    void saveToFile(const std::string& filename, const std::string& key, CipherType type);
    void loadFromFile(const std::string& filename, const std::string& key, CipherType type);
};

#endif