#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>

/// Import string from std
using std::string;

/// Import stoi from std
using std::stoi;

/// Import pow from std, but for int
int pow(int x, int y) { return std::pow(x, y); }

/// Type of variable
enum type { 
    ERR, ///< Error
    INT, ///< Integer
    BOOL ///< Boolean
};

/// Gets the name of a type
static inline const string& name_of(type t) {
    static string names[] = { "<type error>", "int", "bool" };
    return names[t];
}

/// prints a type
static inline std::ostream& operator<< (std::ostream& out, type t) {
    return out << name_of(t);
}

/// adds a type to a string
static inline string operator+ (const string& s, type t) {
    return s + name_of(t);
}

/// Checks that two types are equal, throwing an error if not
static inline void check_equal(type t1, type t2, const string& msg) {
    if ( t1 == t2 ) return;
    throw msg + ": " + t1 + " != " + t2;
}

/// Checks that two types are unequal, throwing an error if not
static inline void check_not_equal(type t1, type t2, const string& msg) {
    if ( t1 != t2 ) return;
    throw msg;
}

/// Symbol table entry
struct entry {
    string name;  ///< Name of symbol
    type ty;      ///< Type of symbol
    int val;      ///< Value of symbol

    entry() = default;

    entry(type t, int v) : name(), ty(t), val(v) {}
    entry(type t, bool v) : name(), ty(t), val(v) {}

    entry(const string& n, type t, int v) : name(n), ty(t), val(v) {}
    entry(const string& n, type t, bool v) : name(n), ty(t), val(v) {}

    void print(std::ostream& out = std::cout) const {
        out << "\t" << name << " = " << val << " : " << ty << std::endl;
    }
};

/// Symbol table
using symtab = std::unordered_map<string, entry>;

/// Global symbol table
extern symtab global_symtab;
