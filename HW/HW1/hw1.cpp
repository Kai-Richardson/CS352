#include <iostream>
#include <sstream>
#include <string>

#include "hw1.hpp"
#include "parser.hpp"
#include "symtab.hpp"

/// Sets up the global symbol table
symtab global_symtab = {};

/// Runs the CS 352 HW 1 parser one line at a time
int main(int argc, char** argv) {
    using namespace std;

    unsigned row = 1;
    string line;
    while ( getline(cin, line) ) {
        row++;
        if ( line.empty() ) continue;
        if ( line == "quit" ) break;

        stringstream input(line);
        parser::state ps(input);
        entry e{"<not initialized>", ERR, 0};
        try {
            if ( hw1::assn(ps, e) ) {
                e.print();
                global_symtab[e.name] = e;
            } else {
                const parser::error& err = ps.error();

                cout << "invalid expression @" << row << ":" << err.pos.col() << endl;
                for ( const auto& msg : err.messages ) {
                    cout << "\t" << msg << endl;
                }
                for ( const auto& exp : err.expected ) {
                    cout << "\tExpected" << exp << endl;
                }
            }
        } catch(const string& err) {
            cout << err << endl;
        }
    }
}