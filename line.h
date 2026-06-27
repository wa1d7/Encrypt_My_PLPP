#ifndef LINE_H
#define LINE_H

#include <string>
#include <iostream>
#include <memory>

class Line {
public:
    virtual ~Line() = default;

    virtual void print() const = 0;

    virtual std::unique_ptr<Line> clone() const = 0;
    virtual std::string serialize() const = 0;
    static std::unique_ptr<Line> deserialize(const std::string& data);

    virtual int length() const { return 0; }
    virtual void append(const std::string& str) {}
    virtual void insert(int char_idx, const std::string& str) {}
    virtual void remove(int char_idx, int count) {}
    virtual void insertReplace(int char_idx, const std::string& str) {}
    virtual std::string extract(int char_idx, int count) const { return ""; }
    virtual bool contains(const std::string& query, size_t& pos) const { return false; }
};

class TextLine : public Line {
    std::string text;
public:
    explicit TextLine(const std::string& t);
    void print() const override;
    std::unique_ptr<Line> clone() const override;
    std::string serialize() const override;

    int length() const override;
    void append(const std::string& str) override;
    void insert(int char_idx, const std::string& str) override;
    void remove(int char_idx, int count) override;
    void insertReplace(int char_idx, const std::string& str) override;
    std::string extract(int char_idx, int count) const override;
    bool contains(const std::string& query, size_t& pos) const override;
};
class ContactLine : public Line {
    std::string name;
    std::string surname;
    std::string email;
public:
    ContactLine(const std::string& n, const std::string& s, const std::string& e);
    void print() const override;
    std::unique_ptr<Line> clone() const override;
    std::string serialize() const override;
};

class ChecklistLine : public Line {
    std::string item;
    bool checked;
public:
    ChecklistLine(const std::string& i, bool c);
    void print() const override;
    std::unique_ptr<Line> clone() const override;
    void toggle();
    std::string serialize() const override;
};
#endif