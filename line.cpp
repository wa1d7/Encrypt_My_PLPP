//
// Created by ignat on 13.07.2026.
//

#include "line.h"

using namespace std;

TextLine::TextLine(const string& t) : text(t) {}

void TextLine::print() const {
    cout << "Text: " << text << endl;
}

unique_ptr<Line> TextLine::clone() const {
    return make_unique<TextLine>(text);
}

int TextLine::length() const { return text.length(); }

void TextLine::append(const string& str) { text += str; }

void TextLine::insert(int char_idx, const string& str) {
    if (char_idx >= 0 && char_idx <= text.length()) {
        text.insert(char_idx, str);
    }
}

void TextLine::remove(int char_idx, int count) {
    if (char_idx >= 0 && char_idx <= text.length()) {
        text.erase(char_idx, count);
    }
}

void TextLine::insertReplace(int char_idx, const string& str) {
    if (char_idx >= 0 && char_idx <= text.length()) {
        text.replace(char_idx, str.length(), str);
    }
}

string TextLine::extract(int char_idx, int count) const {
    if (char_idx >= 0 && char_idx < text.length()) {
        return text.substr(char_idx, count);
    }
    return "";
}

bool TextLine::contains(const string& query, size_t& pos) const {
    pos = text.find(query, pos);
    return pos != string::npos;
}