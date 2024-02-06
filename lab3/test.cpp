#include <iostream>
using std::string;
using std::cout;
using std::to_string;

int main() {
    string str = "0";

    for (int i=0; i < 10; i++) {
        str.append(to_string(static_cast<char>(i)));
    }


    cout << str;
    return 0;
}