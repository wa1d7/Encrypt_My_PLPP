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
ContactLine::ContactLine(const string& n, const string& s, const string& e)
    : name(n), surname(s), email(e) {}
void ContactLine::print() const {
    cout << "Contact - " << name << " " << surname
         << ", E-mail: " << email << endl;
}

unique_ptr<Line> ContactLine::clone() const {
    return make_unique<ContactLine>(name, surname, email);
}

ChecklistLine::ChecklistLine(const string& i, bool c) : item(i), checked(c) {}

void ChecklistLine::print() const {
    cout << "[ " << (checked ? "x" : " ") << " ] " << item << endl;
}

unique_ptr<Line> ChecklistLine::clone() const {
    return make_unique<ChecklistLine>(item, checked);
}
void ChecklistLine::toggle() {
    checked = !checked;
}

string TextLine::serialize() const {
    return "TEXT:" + text;
}

string ContactLine::serialize() const {
    return "CONTACT:" + name + "|" + surname + "|" + email;
}

string ChecklistLine::serialize() const {
    return "CHECKLIST:" + to_string(checked ? 1 : 0) + "|" + item;
}

unique_ptr<Line> Line::deserialize(const string& data) {
    size_t colon_pos = data.find(':');
    if (colon_pos == string::npos) {
        return make_unique<TextLine>(data);
    }

    string type = data.substr(0, colon_pos);
    string payload = data.substr(colon_pos + 1);

    if (type == "TEXT") {
        return make_unique<TextLine>(payload);
    }
    else if (type == "CONTACT") {
        size_t first_pipe = payload.find('|');
        size_t second_pipe = payload.find('|', first_pipe + 1);

        if (first_pipe != string::npos && second_pipe != string::npos) {
            string n = payload.substr(0, first_pipe);
            string s = payload.substr(first_pipe + 1, second_pipe - first_pipe - 1);
            string e = payload.substr(second_pipe + 1);
            return make_unique<ContactLine>(n, s, e);
        }
    }
    else if (type == "CHECKLIST") {
        size_t pipe_pos = payload.find('|');
        if (pipe_pos != string::npos) {
            bool c = (payload.substr(0, pipe_pos) == "1");
            string i = payload.substr(pipe_pos + 1);
            return make_unique<ChecklistLine>(i, c);
        }
    }
    return make_unique<TextLine>(data);
}