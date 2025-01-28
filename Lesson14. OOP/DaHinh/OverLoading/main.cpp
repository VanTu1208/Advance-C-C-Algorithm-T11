#include <iostream>
using namespace std;

class AreaCalculator {
public:
    // Hàm tính diện tích hình vuông
    int area(int side) {
        return side * side;
    }

    // Hàm tính diện tích hình chữ nhật
    int area(int length, int width) {
        return length * width;
    }

    // Hàm tính diện tích hình tròn
    double area(double radius) {
        return 3.14159 * radius * radius;
    }
};

int main() {
    AreaCalculator s;

    // Gọi các hàm nạp chồng
    cout << "Diện tích hình vuông: " << s.area(5) << endl; // Gọi hàm area(int)
    cout << "Diện tích hình chữ nhật: " << s.area(4, 6) << endl; // Gọi hàm area(int, int)
    cout << "Diện tích hình tròn: " << s.area(3.5) << endl; // Gọi hàm area(double)

    return 0;
}