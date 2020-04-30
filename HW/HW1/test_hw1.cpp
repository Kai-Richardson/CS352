#include <sstream>
#include <string>

#include "hw1.hpp"
#include "parser.hpp"
#include "symtab.hpp"

/// Sets up the global symbol table
symtab global_symtab = {};

int main(int argc, char** argv) {
    using namespace std;

    {
        stringstream input("success := 1");
        parser::state ps(input);
        entry e;
        hw1::assn(ps, e);
        e.print();
    }
}
