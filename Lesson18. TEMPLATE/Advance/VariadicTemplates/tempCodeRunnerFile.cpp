#include <iostream>

using namespace std;

void print1()
{
    cout << endl;
}

template<typename T, typename... Rest>
void print1(T first, Rest... rest) {
    cout << first << endl;
    print1(rest...);
}


template <typename... Args>
void print(Args... args) {
 (cout << ... << args) << '\n';
}

int main() {
 print(1, 2, 3, "hello", 4.5, "Trung", 55);
 return 0;
}

