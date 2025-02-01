#include <iostream>
using namespace std;
// Tạo template Expression cho phép cộng hai số
template <typename T1, typename T2>
class AddExpression {
    const T1& lhs;  // Biểu thức bên trái
    const T2& rhs;  // Biểu thức bên phải

public:
    // Khởi tạo biểu thức cộng
    AddExpression(const T1& l, const T2& r) : lhs(l), rhs(r) {}

    // Hàm trả về kết quả cộng hai số khi cần
    auto operator()() const {
        return lhs() + rhs();  // Cộng kết quả của hai biểu thức
    }
};

// Lớp biểu diễn một số đơn giản
class Constant {
    int value;

public:
    Constant(int v) : value(v) {}

    int operator()() const { return value; }  // Trả về giá trị
};

// Hàm gán phép cộng giữa hai số
template <typename T1, typename T2>
AddExpression<T1, T2> operator+(const T1& lhs, const T2& rhs) {
    return AddExpression<T1, T2>(lhs, rhs);
}

int main() {
    Constant a(3);  // Tạo một số 3
    Constant b(5);  // Tạo một số 5

    // Tạo biểu thức cộng (không tính ngay, chỉ lưu công thức)
    auto sum = a + b;  

    // In ra kết quả cộng
    cout << "Sum: " << sum() << endl;  // Kết quả: 8
    return 0;
}
