#include <iostream>
#include <memory>

using namespace std;

/***********************************************************************
 * shared pointer (shared_ptr) là một smart pointer hỗ trợ chia sẻ quyền 
 * sở hữu đối với một đối tượng.
 * 
 * Nhiều shared_ptr có thể cùng sở hữu một đối tượng. Đối tượng chỉ được
 * giải phóng khi không còn shared_ptr nào sở hữu nó (đếm tham chiếu đạt 
 * giá trị 0).
 **********************************************************************/

int main(int argc, char const *argv[])
{
    shared_ptr<int> sptr1 = make_shared<int>(20); // 0x01
    shared_ptr<int> sptr2 = sptr1;
    shared_ptr<int> sptr3 = sptr1;

    {
        shared_ptr<int> sptr4 = sptr1;
        cout << "Count: " << sptr1.use_count() << endl;
    }

    cout << "Count: " << sptr1.use_count() << endl;
    /***********************************************************************
    * use_count(): trả về số lượng shared_ptr đang cùng quản lý đối tượng
    * (kiểm tra số lượng tham chiếu)
    ***********************************************************************/


    cout << "sptr1 = " << *sptr1 << endl;
    cout << "sptr2 = " << *sptr2 << endl;
    cout << "sptr3 = " << *sptr3 << endl;

    
    int *sptr = sptr1.get();
    cout << "sptr: " << *sptr << endl;
    /***********************************************************************
    * trả về con trỏ thô (int*) trỏ tới vùng nhớ mà ptr1 đang quản lý
    ***********************************************************************/

    *sptr = 50;
    cout << "sptr: " << *sptr << endl;
    /***********************************************************************
    * thay đổi giá trị con trỏ thô (*ptr = 50) sẽ làm thay đổi giá trị của đối 
    * tượng được shared_ptr quản lý
    ***********************************************************************/

    shared_ptr<int> a = make_shared<int>(40);   // 0xa1
    shared_ptr<int> b = make_shared<int>(50);   // 0xb3
    a.swap(b);
    cout << "a = " << *a << endl;
    cout << "b = " << *b << endl;
    

    a = move(b);
    cout << "a = " << *a << endl;

    if (sptr1.unique()){
        cout << "true\n";
    } else {
        cout << "false\n";
    }
    
    return 0;
}