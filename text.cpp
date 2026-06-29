#include "text.h"
#include <sstream>
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

void Text::appendText(const string& new_text) {
    if (lines.empty()) {
        startNewLine();
    }
    lines.back()->append(new_text);
    cursor_line = lines.size() - 1;
    cursor_pos = lines.back()->length();
}

void Text::insertText(int line_idx, int char_idx, const string& insert_str) {
    if (line_idx >= 0 && line_idx < lines.size()) {
        lines[line_idx]->insert(char_idx, insert_str);
    } else {
        cout << "err: line index out of range.\n";
    }
}
void Text::insertReplaceText(int line_idx, int char_idx, const string& insert_str) {
    if (line_idx >= 0 && line_idx < lines.size()) {
        lines[line_idx]->insertReplace(char_idx, insert_str);
    }
}
void Text::deleteText(int line_idx, int char_idx, int char_count) {
    if (line_idx >= 0 && line_idx < lines.size()) {
        lines[line_idx]->remove(char_idx, char_count);
    } else {
        cout << "err: line index out of range.\n";
    }
}

void Text::searchText(const string& search_str) const {
    bool found_any = false;
    for (size_t i = 0; i < lines.size(); ++i) {
        size_t pos = 0;
        while (lines[i]->contains(search_str, pos)) {
            cout << "text is present in this position: " << i << " " << pos << "\n";
            found_any = true;
            pos += search_str.length();
        }
    }
    if (!found_any) {
        cout << "not found\n";
    }
}

string Text::copyText(int line_idx, int char_idx, int count) const {
    if (line_idx >= 0 && line_idx < lines.size()) {
        return lines[line_idx]->extract(char_idx, count);
    }
    return "";
}

string Text::serialize() const {
    string full_data;
    for (const auto& line : lines) {
        full_data += line->serialize() + "\n";
    }
    return full_data;
}

Text Text::deserialize(const string& data) {
    Text new_text;
    stringstream ss(data);
    string line_data;

    while (getline(ss, line_data)) {
        if (!line_data.empty()) {
            new_text.addLine(Line::deserialize(line_data));
        }
    }
    return new_text;
}