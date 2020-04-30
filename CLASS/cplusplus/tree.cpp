#include "tree.hpp"
#include <string>
#include <iostream>

using namespace std;

struct point {int x; int y;};


int main() {
    tree<int> left{7, nullptr, nullptr};
    tree<int> right{42, nullptr, nullptr};
    tree<int> root{11, &left, &right};

    cout << root << endl;
    cout << sum(root) << endl;


    tree<string> place{"world", nullptr, nullptr};
    tree<string> hello{"hello", nullptr, &place};
    cout << hello << endl;
    cout << sum(hello) << endl;

    tree<point> axis{point{1,0}, nullptr, nullptr};
    tree<point> origin{point{0,0}, &axis, nullptr};
    cout << endl;
    //point sum1 = sum(origin);
}