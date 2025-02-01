#include <iostream>

using namespace std;

void println()
{
    cout << endl;
}

template<typename T, typename... Rest>
void println(T first, Rest... rest) {
    cout << first << endl;
    println(rest...);
}


template <typename... Args>
void print(Args... args) {
 (cout << ... << args) << '\n';
}

int main() {
 print(1, 2, 3, "hello", 4.5, "Trung", 55);
 cout << "-------------------- \n" ;
 println(1, 2, 3, "hello", 4.5, "Trung", 55);
 return 0;
}

