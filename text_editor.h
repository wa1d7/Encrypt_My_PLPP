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
    void copy(int line, int pos, int count);
    void paste(int line, int pos);
    

    void saveToFile(const std::string& filename, const std::string& key);
    void loadFromFile(const std::string& filename, const std::string& key);
};

#endif