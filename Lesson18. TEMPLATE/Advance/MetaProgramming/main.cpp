#include <iostream>
using namespace std;

// Template đệ quy để tính giai thừa tại compile-time
template <int N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};

// Trường hợp cơ sở: Factorial<0> = 1
template <>
struct Factorial<0> {
    static const int value = 1;
};

int main() {
    cout << "5! = " << Factorial<5>::value << endl; 
    cout << "7! = " << Factorial<7>::value << endl; 
    return 0;
}