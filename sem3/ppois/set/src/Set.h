#ifndef MYSET_H
#define MYSET_H

#include <string>
#include <vector>

bool is_valid_string(const std::string& str);
std::vector<std::string> parse_elements(const std::string& str);

class Set{
private:
    std::vector<std::string> elements;
    std::vector<Set> subsets;

public:
    Set();
    explicit Set(const std::string& str);
    explicit Set(const char* str);

    int get_power() const;
    bool empty() const;

    void add_el(const std::string& new_el);
    void add_el(const Set& new_el);

    void delete_el(const std::string& el);
    void delete_el(const Set& el);

    void print() const;

    bool operator [](const std::string& el) const;
    bool operator [](const Set& sub) const;

    bool operator ==(const Set& other) const;
    bool operator !=(const Set& other) const;

    Set operator +(const Set& other) const; // union
    Set& operator +=(const Set& other);
    Set operator -(const Set& other) const; // difference
    Set& operator -=(const Set& other);
    Set operator /(const Set& other) const; // symmetric difference
    Set operator *(const Set& other) const; // intersection
    Set& operator *=(const Set& other);

    Set boolean() const;
};

#endif
