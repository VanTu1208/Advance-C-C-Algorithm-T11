#include <iostream>
using namespace std;

class Complex {
private:
    double real;   // Phần thực
    double imag;   // Phần ảo
public:
    // Constructor
    Complex(double r, double i){
        real = r;
        imag = i;
    }

    // Nạp chồng toán tử +
    Complex operator+(const Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) {
        return Complex(real - other.real, imag - other.imag);
    }

    // Hàm hiển thị số phức
    void display() const {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Complex c1(5.0, 9.0); // Số phức c1 = 3 + 4i
    Complex c2(1.5, 3.5); // Số phức c2 = 1.5 + 2.5i

    // Sử dụng toán tử + đã nạp chồng
    Complex c3 = c1 + c2;
    Complex c4 = c1 - c2;
    // Hiển thị kết quả
    cout << "C1 = ";
    c1.display();
    cout << "C2 = ";
    c2.display();
    cout << "C1 + C2 = ";
    c3.display();
    cout << "C1 - C2 = ";
    c4.display();

    return 0;
}