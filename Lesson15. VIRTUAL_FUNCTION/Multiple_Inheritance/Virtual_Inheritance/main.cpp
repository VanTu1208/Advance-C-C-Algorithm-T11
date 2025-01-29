#include <iostream>
using namespace std;

class A {
public:
    A() { cout << "Constructor A\n"; }
    void hienThiA() { cout << "Day la lop A\n"; }
};

// Thêm virtual
class B : virtual public A {
public:
    B() { cout << "Constructor B\n"; }
    void hienThiB() { cout << "Day la lop B\n"; }
};

// Thêm virtual
class C : virtual public A {
public:
    C() { cout << "Constructor C\n"; }
    void hienThiC() { cout << "Day la lop C\n"; }
};

class D : public B, public C {
public:
    D() { cout << "Constructor D\n"; }
    void hienThiD() { cout << "Day la lop D\n"; }
};

int main() {
    D d;

    d.hienThiA(); // Không còn lỗi, chỉ có một bản sao của A
    d.hienThiB();
    d.hienThiC();
    d.hienThiD();

    return 0;
}