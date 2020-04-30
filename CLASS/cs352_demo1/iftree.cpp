#include <iostream>

#include "parse_tree.hpp"
#include "parser.hpp"
#include "iftree.hpp"

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
		parse_tree tree;
		
		if ( parser::bind(tree, iftree::IfStmt)(ps) ) {
			tree.print();
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