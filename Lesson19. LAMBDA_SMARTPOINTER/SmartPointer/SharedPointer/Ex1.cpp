#include <iostream>

using namespace std;

void test()
{
    int *ptr1 = new int(5);     // 0x01: 5 - cấp phát động trên Heap
    cout << "địa chỉ: " << ptr1 << endl;
    cout << "giá trị: " << *ptr1 << endl;
    {
        int *ptr2 = ptr1;
        cout << "địa chỉ: " << ptr2 << endl;
        cout << "giá trị: " << *ptr2 << endl;
        {
            int *ptr3 = ptr2;
            cout << "địa chỉ: " << ptr3 << endl;
            cout << "giá trị: " << *ptr3 << endl;
        }
    }
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}
