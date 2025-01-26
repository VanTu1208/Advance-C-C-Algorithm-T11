#include <iostream>
using namespace std;

class Test
{

private:
    int thuocTinh_A;
    float thuocTinh_B;

public:
    // Constructor có tham số, thực thi khi khởi tạo một đối tượng của Class, thường dùng để khởi tạo giá trị ban đầu của các thuộc tính

    int age;
    char *name;
    float score;

    Test(int init_A, float init_B, int init_age, char *init_name, float init_score)
    {
        thuocTinh_A = init_A;
        thuocTinh_B = init_B;
        age = init_age;
        name = init_name;
        score = init_score;
    }

    // Thiết lập giá trị các thuộc tính gián tiếp
    void setThuocTinh_A(int value)
    {
        thuocTinh_A = value;
    }

    void setThuocTinh_B(int value)
    {
        thuocTinh_B = value;
    }

    // Lấy giá trị thuộc tính gián tiếp thông qua hàm
    int getThuocTinh_A()
    {
        return thuocTinh_A;
    }

    float getThuocTinh_B()
    {
        return thuocTinh_B;
    }

    // Hiển thị giá trị hai thuộc tính của Class
    void display()
    {
        cout << "Giá trị của A: " << thuocTinh_A
             << "\nGiá trị của B: " << thuocTinh_B
             << "\nTuổi: " << age
             << "\nTên: " << name
             << "\nĐiểm: " << score << endl;
    }
};

int main()
{
    // Tạo đối tượng và khởi tạo giá trị cho hai thuộc tính
    Test Test1(0, 0, 0, "", 0);

    // Gọi phương thức in ra giá trị
    Test1.display();

    cout << endl
         << endl;

    // Thay đổi giá trị thuộc tính thông qua các hàm Public
    Test1.setThuocTinh_A(2);
    Test1.setThuocTinh_B(1);

    Test1.age = 20;
    Test1.name = "Van Tu";
    Test1.score = 8.2;

    Test1.display();

    return 0;
}