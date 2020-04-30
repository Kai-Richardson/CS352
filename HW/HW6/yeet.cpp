using namespace std;
#include <iostream>

int f(int i) {
    if ( i % 2 == 0 ) {
        throw i;
    } else {
        f(i+1);
        return i*2;
    }
}

int g() {
    try {
        f(1);
    } catch (int x) {
        return f(10);
    }
    return 0;
}

int main(int argc, char** argv) {

try {
    g();
}
catch (int x) {
    cout << x;
}

}