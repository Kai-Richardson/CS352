#include <iostream>
#include <sstream>
#include <string>
#include "calc.hpp"
#include "parser.hpp"

/**
 * Simple desk calculator for CS 352 Lab 1
 * @author Aaron Moss
 */
int main(int argc, char** argv) {
    using namespace std;

    string line;
    while ( getline(cin, line) ) {
        if ( line.empty() ) continue;
        if ( line == "quit" ) break;

        stringstream input(line);
        parser::state ps(input);
        double result;

        if ( parser::bind(result, calc::expr)(ps) ) {
            cout << "\t" << result << endl;
        } else {
            const parser::error& err = ps.error();
			
			cout << "`" << line << "' DOESN'T MATCH  @" << err.pos.col() << endl;
        }
    }
}