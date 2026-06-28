
#ifndef ENCRYPT_TEXT_H
#define ENCRYPT_TEXT_H
#ifndef TEXT_H
#define TEXT_H

#include "line.h"
#include <vector>
#include <memory>
#include <string>

class Text {
    std::vector<std::unique_ptr<Line>> lines;
    int cursor_line;
    int cursor_pos;

public:
    Text();

    Text(const Text& other);

    Text& operator=(const Text& other) = delete;

    void startNewLine();
    void addLine(std::unique_ptr<Line> line);
    void printText() const;
    void clear();

    void setCursor(int line, int pos);
    int getCursorLine() const;
    int getCursorPos() const;
    int getLineCount() const;
    const Line* getLine(int idx) const;

    void appendText(const std::string& new_text);
    void insertText(int line_idx, int char_idx, const std::string& insert_str);
    void insertReplaceText(int line_idx, int char_idx, const std::string& insert_str);
    void deleteText(int line_idx, int char_idx, int char_count);
    void searchText(const std::string& search_str) const;
    std::string copyText(int line_idx, int char_idx, int count) const;
};

#endif // TEXT_H
#endif //ENCRYPT_TEXT_H
