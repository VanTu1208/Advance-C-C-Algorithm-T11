#include <iostream>
using namespace std;

class Test {
public:
    int value;

    void display() {
        cout << "Giá trị của Value: " << value << endl;
    }
};

int main() {
    Test Test1;
    Test* ptr = &Test1;  // Tạo con trỏ trỏ đến đối tượng Test1

    ptr->value = 100;  // Thay đổi giá trị thuộc tính thông qua con trỏ

    ptr->display();  // Gọi phương thức in ra giá trị value thông qua con trỏ

    return 0;
}