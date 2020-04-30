#include <iostream>
#include <string>

using namespace std;

void get_name(const string &prompt, string &name)
{
    cout << prompt << " (spooky)";
    getline(cin, name);
    if (!name.empty()) {name = name + " <->" + name;}
}

int main()
{
    string greeting = "Hello, ";
    string name;
    string prompt = "Type your name: ";

    while (true)
    {
        get_name(prompt, name);
        if (name.empty())
            break;
        cout << greeting << name << endl;
    }

    cout << "Goodbye!" << endl;

}

