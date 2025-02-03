#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int x = 1; // 0x01
    int y = 2; // 0x05
    int z = 3; // 0xf4

    int a = 9;
    int b = 2;

    // Không sử dụng biến
    auto sum = [](int a, int b)
    {
        return a + b;
    };
    cout << "Tổng 2 số: " << sum(a, b) << endl;

    // Sử dụng hai biến x,y READ-ONLY
    auto sub = [x, y](int a, int b)
    {
        return (a + b) - (x + y);
    };
    cout << "Hiệu a+b - (x+y): " << sub(a, b) << endl;

    // Sử dụng tất cả các biến READ-ONLY
    auto sumAll = [=](int a, int b)
    {
        return a + b + x + y + z;
    };
    cout << "Tổng tất cả: " << sum(a, b) << endl;

    // Sử dụng biến y và z, READ-WRITE
    auto sumChange = [&y, &z](int a, int b)
    {
        y = 15; // read - write
        z = 9;  // read - write
        return a + b + y + z;
    };
    cout << "Tổng sau khi thay đổi a+b+y+z: " << sumChange(a, b) << endl;

    // Tham chiếu được tất cả các biến xung quanh
    auto sumAll1 = [&](int a, int b)
    {
        x = 5;  // read - write
        y = 10; // read - write
        z = 1;  // read - write
        return a + b + x + y + z;
    };
    cout << "Tổng tất cả: " << sumAll1(a, b) << endl;

    // Kết hợp.
    auto sumCombine = [x, &y, &z](int a, int b)
    {
        // x = 5;   // read - write
        y = 10; // read - write
        z = 1;  // read - write
        return a + b + x + y + z;
    };
    cout << "Tổng kết hợp: " << sumCombine(1, 2) << endl;

    // Lambda không có tham sôs

    auto display = []()
    {
        cout << "Hello, world\n";
    };

    display();

    // Sử dụng trực tiếp lambda
    //Có tham số
    cout << [](int a, int b)
    {
        return a + b;
    }(2, 3)
         << endl;
    // Không tham số
    []()
    {
        cout << "Hello, world\n";
    }();

    return 0;
}
