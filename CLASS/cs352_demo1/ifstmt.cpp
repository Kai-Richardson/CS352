#include <iostream>

#include "parser.hpp"
#include "ifstmt.hpp"

/**
 * Test harness for phone grammar.
 * @author Aaron Moss
 */
int main(int argc, char** argv) {
	using namespace std;
	
	string line, s;
	while ( getline(cin, line) ) {
        if ( line.empty() ) continue;
        if ( line == "quit" ) break;

		stringstream input(line);
		parser::state ps(input);
		
		if ( parser::capture(s, ifstmt::IfStmt)(ps) ) {
			cout << "`" << s << "' MATCHES" << endl;
		} else {
			const parser::error& err = ps.error();
			
			cout << "`" << line << "' DOESN'T MATCH  @" << err.pos.col() << endl;
			for (auto msg : err.messages) {
				cout << "\t" << msg << endl;
			}
			for (auto exp : err.expected) {
				cout << "\tExpected " << exp << endl;
			}
		}
	}
}