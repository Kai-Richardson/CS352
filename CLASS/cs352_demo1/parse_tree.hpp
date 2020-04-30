#pragma once

#include <iostream>
#include <initializer_list>
#include <string>
#include <vector>

class parse_tree {
    std::string label;                ///< Identifier for this node
    std::vector<parse_tree> children; ///< Sub-nodes

    /// prints n copies of a character to the output stream
    static void print_n(std::ostream& out, char c, unsigned n) {
        for (unsigned i = 0; i < n; ++i) { out << c; }
    }

    /// calculates the location of the i'th stem where each stem has the given node_share
    static unsigned stem_at(unsigned i, unsigned node_share) {
        return i*(node_share + 1) + (node_share-1)/2;
    }

public:
    parse_tree() = default;
    parse_tree(const std::string& n, std::initializer_list<parse_tree> cs = {}) : label(n), children(cs) {}

    parse_tree& operator+= (const parse_tree& c) {
        children.emplace_back(c);
        return *this;
    }

    /// Prints this parse tree, dividing the specified width
    void print(std::ostream& out = std::cout, unsigned chars = 80) const {
        std::vector<const parse_tree*> nodes{this};
        std::vector<const parse_tree*> next_nodes{};
        std::vector<unsigned> next_runs{};
        unsigned node_share = chars;

        while(true) {
            // print node labels
            for ( unsigned i = 0; i < nodes.size(); ++i ) {
                const parse_tree* node = nodes[i];
                
                // print node-dividing space
                if ( i ) { out << ' '; }

                unsigned len = node->label.size();
                if ( len <= node_share ) {
                    // print node and add children
                    print_n(out, ' ', (node_share - len)/2);
                    out << node->label;
                    print_n(out, ' ', (node_share - len + 1)/2);
                    for ( const parse_tree& child : node->children ) { next_nodes.emplace_back(&child); }
                    next_runs.emplace_back(node->children.size());
                } else {
                    // print error marker
                    print_n(out, ' ', (node_share - 1)/2);
                    out << '*';
                    print_n(out, ' ', node_share/2);
                    next_runs.emplace_back(0);
                }
            }
            out << std::endl;

            // bail early if no next nodes
            if ( next_nodes.empty() ) break;

            // print trunks, skipping nodes with no children
            for ( unsigned i = 0; i < nodes.size(); ++i ) {
                if ( i ) { out << ' '; }

                if ( next_runs[i] ) {
                    print_n(out, ' ', (node_share - 1)/2);
                    out << '|';
                    print_n(out, ' ', node_share/2);
                } else {
                    print_n(out, ' ', node_share);
                }
            }
            out << std::endl;
            
            // calculate space available to each node on the next level
            const unsigned n_next = next_nodes.size();
            const unsigned next_node_share = ( n_next - 1 <= chars ) ? ( chars - (n_next - 1) ) / n_next : 0;
            // std::cerr << "next_node_share=" << next_node_share << std::endl;
            
            if ( next_node_share ) {
                // print branches to next level
                unsigned j = 0, used = 0;
                for ( unsigned i = 0; i < nodes.size(); ++i ) {
                    // skip empty runs
                    if ( ! next_runs[i] ) continue;

                    // calculate location of trunk, first drop stem, last drop stem, and final available index
                    unsigned trunk = stem_at(i, node_share);
                    unsigned first_drop = stem_at(j, next_node_share);
                    unsigned last_drop = stem_at(j + next_runs[i] - 1, next_node_share);
                    unsigned next_drop = stem_at(j + next_runs[i], next_node_share);
                    
                    // connect (early) trunk to branches
                    if ( trunk < used + 2 ) {
                        out << " <";
                        if ( first_drop > used + 2 ) { print_n(out, '-', first_drop - used); }
                    } else if ( trunk < first_drop ) {
                        print_n(out, ' ', trunk - used - 1);
                        out << '\\';
                        print_n(out, '-', first_drop - trunk);
                    } else {
                        print_n(out, ' ', first_drop - used);
                    }

                    // link branches
                    print_n(out, '-', last_drop - first_drop);

                    // connect (late) trunk to branches and updated used
                    if ( trunk + 2 > next_drop ) {
                        if ( last_drop < next_drop - 2 ) { print_n(out, '-', next_drop - 2 - last_drop); }
                        out << '>';
                        used = next_drop - 1;
                    } else if ( trunk > last_drop ) {
                        print_n(out, '-', trunk - last_drop);
                        out << '/';
                        used = trunk + 1;
                    } else {
                        out << '-';
                        used = last_drop + 1;
                    }

                    j += next_runs[i];
                }
                out << std::endl;
            } else {
                // no space for next level, print error nodes at end of trunks
                for ( unsigned i = 0; i < nodes.size(); ++i ) {
                    if ( i ) { out << ' '; }

                    if ( next_runs[i] ) {
                        print_n(out, ' ', (node_share - 1)/2);
                        out << '*';
                        print_n(out, ' ', node_share/2);
                    } else {
                        print_n(out, ' ', node_share);
                    }
                }
                out << std::endl;
                break;
            }

            // print next-level stems
            for (unsigned j = 0; j < n_next; ++j) {
                if ( j ) { out << ' '; }
                print_n(out, ' ', (next_node_share - 1)/2);
                out << '|';
                print_n(out, ' ', next_node_share/2);
            }
            out << std::endl;

            // reset for next round
            nodes.clear();
            nodes.swap(next_nodes);
            next_runs.clear();
            node_share = next_node_share;
        }
    }
};
