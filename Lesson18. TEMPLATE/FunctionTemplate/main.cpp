#include <iostream>
using namespace std;

// Khai báo một function template
template <typename X>
X mul(X a, X b){
    X c = a * b;
    return c; 
}

// Khai báo một function template
template <typename T>
T findMax(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    cout << findMax(10, 20) << endl;       // Dữ liệu kiểu int
    cout << findMax(3.5, 2.8) << endl;     // Dữ liệu kiểu double
    cout << findMax('A', 'Z') << endl;     // Dữ liệu kiểu char
    
    cout << endl;
    
    cout << mul(3, 5) << endl;
    cout << mul(1.2, 0.2) << endl;
    return 0;
}