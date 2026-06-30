#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include "text.h"
#include "cipher_loader.h"
#include <vector>
#include <stack>

struct Tab {
    Text text;
    std::stack<Text> undo_stack;
    std::stack<Text> redo_stack;
};

class TextEditor {
    std::vector<Tab> tabs;
    int active_tab;
    std::string clipboard;
    CipherLoader* cipher;

    void saveState();

public:
    TextEditor(CipherLoader* c);

    void newTab();
    void switchTab(int index);
    void closeTab(int index);
    void listTabs() const;

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

    void encryptDocument(const std::string& key, CipherType type);
    void decryptDocument(const std::string& key, CipherType type);

    void saveToFile(const std::string& filename, const std::string& key, CipherType type);
    void loadFromFile(const std::string& filename, const std::string& key, CipherType type);
};

#endif