#include "text.h"

using namespace std;

Text::Text() : cursor_line(0), cursor_pos(0) {}

Text::Text(const Text& other) {
    cursor_line = other.cursor_line;
    cursor_pos = other.cursor_pos;
    for (const auto& line : other.lines) {
        lines.push_back(line->clone());
    }
}

void Text::startNewLine() {
    lines.push_back(make_unique<TextLine>(""));
    cursor_line = lines.size() - 1;
    cursor_pos = 0;
}
void Text::addLine(unique_ptr<Line> line) {
    lines.push_back(std::move(line));
    cursor_line = lines.size() - 1;
    cursor_pos = 0;
}

void Text::printText() const {
    if (lines.empty()) {
        cout << "buffer is empty\n";
        return;
    }
    cout << "\n[ CURSOR: line " << cursor_line << ", pos " << cursor_pos << " ]\n\n";
    for (const auto& line : lines) {
        line->print();
    }
}
void Text::clear() {
    lines.clear();
    cursor_line = 0;
    cursor_pos = 0;
}

void Text::setCursor(int line, int pos) {
    if (line >= 0 && line < lines.size()) {
        if (pos >= 0 && pos <= lines[line]->length()) {
            cursor_line = line;
            cursor_pos = pos;
            cout << "cursor moved.\n";
        } else {
            cout << "err: position out of bounds.\n";
        }
    } else {
        cout << "err: line out of bounds.\n";
    }
}

int Text::getCursorLine() const { return cursor_line; }
int Text::getCursorPos() const { return cursor_pos; }
int Text::getLineCount() const { return lines.size(); }

const Line* Text::getLine(int idx) const {
    if (idx >= 0 && idx < lines.size()) {
        return lines[idx].get();
    }
    return nullptr;
}

void Text::appendText(const string& new_text) {}
void Text::insertText(int line_idx, int char_idx, const string& insert_str) {}
void Text::insertReplaceText(int line_idx, int char_idx, const string& insert_str) {}
void Text::deleteText(int line_idx, int char_idx, int char_count) {}
void Text::searchText(const string& search_str) const {}
string Text::copyText(int line_idx, int char_idx, int count) const { return ""; }