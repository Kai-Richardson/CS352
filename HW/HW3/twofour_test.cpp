#include <iostream>
#include <string>

#include "twofour.hpp"

int main() {
    ThreeNode<std::string> t1("hello", "goodbye");

    TwoNode<int> t2_1(1);
    TwoNode<int> t2_2(3);
    ThreeNode<int> t2_3(8,13);
    TwoNode<int> t2_4(34);
    FourNode<int> t2(2,5,21, &t2_1, &t2_2, &t2_3, &t2_4);

    std::cout << t1.size() << " " << t2.size() << std::endl;
}