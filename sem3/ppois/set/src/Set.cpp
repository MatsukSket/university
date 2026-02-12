#include <iostream>
#include <algorithm>
#include "Set.h"

Set::Set() = default;

bool is_valid_string(const std::string& str) {
    int balance = 0;
    for (int i = 0; i < str.size(); i++) {
        if (i != 0) {
            if (str[i - 1] == '}' && str[i] == '{') return false;
            if (str[i - 1] == ',' && str[i] == '}') return false;
            if (str[i - 1] == '{' && str[i] == ',') return false;
            if (str[i - 1] == ',' && str[i] == ',') return false;
            if (str[i - 1] == '}' && str[i] != ',' && str[i] != '}') return false;
            if (str[i - 1] != '{' && str[i - 1] != ',' && str[i] == '{') return false;
        } 

        if (str[i] == '{') balance++;
        if (str[i] == '}') balance--;

        if (balance < 0) return false;
    }
    return balance == 0;
}

std::vector<std::string> parse_elements(const std::string& str) {
    if(str == "{}") return {};

    std::vector<std::string> elements;
    int start = 1;
    int balance = 0;
    for (int i = 1; i < str.size() - 1; i++) {
        if (str[i] == '{') balance++;
        if (str[i] == '}') balance--;

        if (str[i] == ',' && balance == 0) {
            elements.push_back(str.substr(start, i - start));
            start = i + 1;
        }
    }
    
    elements.push_back(str.substr(start, str.size() - 1 - start));
    return elements;
}

Set::Set(const std::string& str) {
    if (str.empty()) 
        return;

    std::string clean_str = str;
    clean_str.erase(remove(clean_str.begin(), clean_str.end(), ' '), clean_str.end());

    if (clean_str.size() < 2 || clean_str[0] != '{' || clean_str[clean_str.size() - 1] != '}' || !is_valid_string(clean_str))
        throw std::invalid_argument("Invalid string format\n");
    
    if (clean_str == "{}")
        return;

    std::vector<std::string> elements_list;
    elements_list = parse_elements(clean_str);

    for (const auto& element : elements_list) {
        if(element[0] == '{')
            add_el(Set(element));
        else
            add_el(element);
    }
}

Set::Set(const char* str) : Set(std::string(str ? str : "")) {}

void Set::add_el(const std::string& new_el) {
    bool already_exists = false;
    for (const auto& el : elements) {
        if (new_el == el) {
            already_exists = true;
            break;
        }
    }

    if (!already_exists)
        elements.push_back(new_el);
}

void Set::add_el(const Set& new_el) {
    bool already_exists = false;
    for (const Set& el : subsets) {
        if (new_el == el) {
            already_exists = true;
            break;
        }
    }

    if (!already_exists)
        subsets.push_back(new_el);
}

void Set::delete_el(const std::string& el) {
    for (auto this_el = elements.begin(); this_el != elements.end(); this_el++)
        if (*this_el == el) {
            elements.erase(this_el);
            break;
        }
}

void Set::delete_el(const Set& el) {
    for (auto this_sub = subsets.begin(); this_sub != subsets.end(); this_sub++)
        if (*this_sub == el) {
            subsets.erase(this_sub);
            break;
        }
}

bool Set::operator ==(const Set& other) const {
    if (elements.size() != other.elements.size())   
        return false;
    for (const auto& this_el : elements) {
         if (std::find(other.elements.begin(), other.elements.end(), this_el) == other.elements.end())
            return false;
    }

    if (subsets.size() != other.subsets.size())   
        return false;
    for (const Set& this_set : subsets) {
        bool set_found = false;
        for (const Set& other_set : other.subsets) 
            if (this_set == other_set) {
                set_found = true;
                break;
            }
        
        if (!set_found)
            return false;
    }

    return true;
}

bool Set::operator [](const std::string& el) const {
    for (const auto& this_el : elements) {
        if (this_el == el) 
            return true;
    }
    return false;
}

bool Set::operator [](const Set& sub) const {
    for (const auto& this_sub : subsets) {
        if (this_sub == sub) 
            return true;
    }
    return false;
}

bool Set::operator !=(const Set& other) const {
    return !(*this == other);
}

Set& Set::operator +=(const Set& other) {
    for (const auto& other_el : other.elements) 
        add_el(other_el);

    for (const auto& other_sub : other.subsets)
        add_el(other_sub);

    return *this;
}

Set Set::operator +(const Set& other) const {
    Set res = *this;
    res += other;
    return res;
}

Set& Set::operator -=(const Set& other) {
    for (auto el = elements.begin(); el != elements.end(); ) 
        if (other[*el]) 
            el = elements.erase(el);
        else
            el++;
    
    for (auto sub = subsets.begin(); sub != subsets.end(); ) 
        if (other[*sub]) 
            sub = subsets.erase(sub);
        else
            sub++;
    
    return *this;
}

Set Set::operator -(const Set& other) const {
    Set res;
    for (const auto& this_el : elements)
        if (!other[this_el])
            res.add_el(this_el);

    for (const auto& this_sub : subsets)
        if (!other[this_sub])
            res.add_el(this_sub);

    return res;
}

Set Set::operator /(const Set& other) const {
    Set res;
    res = (*this - other) + (other - *this);
    return res;
}

Set Set::operator *(const Set& other) const {
    Set res;
    for (const auto& this_el : elements) 
        if (other[this_el]) 
            res.add_el(this_el); 
    for (const auto& this_sub : subsets)
        if (other[this_sub])
            res.add_el(this_sub);
    return res;
}

Set& Set::operator *=(const Set& other) {
    for (auto el = elements.begin(); el != elements.end(); ) {
        if (!other[*el]) 
            el = elements.erase(el);
        else
            el++;
    }

    for (auto sub = subsets.begin(); sub != subsets.end(); ) {
        if (!other[*sub]) 
            sub = subsets.erase(sub);
        else
            sub++;
    }
    return *this;
}

void Set::print() const {
    bool first = true;
    
    std::cout << "{ ";

    for (const auto& el : elements) {
        if (!first) std::cout << ", ";
        std::cout << el;
        first = false;
    }

    for (const auto& sub : subsets) {
        if (!first) std::cout << ", ";
        sub.print(); 
        first = false;
    }

    std::cout << " }";
}

int Set::get_power() const {
    return elements.size() + subsets.size();
}

bool Set::empty() const {
    return elements.empty() && subsets.empty();
}

Set Set::boolean() const {
    std::vector<std::string> this_elements = elements;
    std::vector<Set> this_subsets = subsets;

    Set res;
    res.add_el(Set());

    for (const auto& el : this_elements) {
        int curr_size = res.subsets.size();
        for (int i = 0; i < curr_size; i++) {
            Set new_sub = res.subsets[i];
            new_sub.add_el(el);
            res.add_el(new_sub);
        }
    }

    for (const auto& sub : this_subsets) {
        int curr_size = res.subsets.size();
        for (int i = 0; i < curr_size; i++) {
            Set new_sub = res.subsets[i];
            new_sub.add_el(sub);
            res.add_el(new_sub);
        }
    }

    return res;
}
