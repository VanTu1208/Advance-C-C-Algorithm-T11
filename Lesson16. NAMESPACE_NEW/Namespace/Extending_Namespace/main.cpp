#include <iostream>

// Định nghĩa ban đầu của namespace MyNamespace
namespace MyNamespace {
    void sayHello() {
        std::cout << "Hello from MyNamespace!" << std::endl;
    }
}

// Mở rộng MyNamespace để thêm một hàm mới
namespace MyNamespace {
    void sayGoodbye() {
        std::cout << "Goodbye from MyNamespace!" << std::endl;
    }
}

int main() {
    MyNamespace::sayHello();   // Gọi hàm từ phần đầu tiên
    MyNamespace::sayGoodbye(); // Gọi hàm từ phần mở rộng
    return 0;
}