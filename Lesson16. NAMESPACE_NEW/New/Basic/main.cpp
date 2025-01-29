#include <iostream>
using namespace std;
int main() {
    // Cấp phát động một số nguyên
    int* ptr1 = new int;  
    int* ptr2 = new int(20);  
    
    
    cout << "Value 1: " << *ptr1 << endl;
    cout << "Value 2: " << *ptr2 << endl;

    *ptr1 = 42;  

    cout << "Value 1: " << *ptr1 << endl << endl;
    
    int num = 5;
    int* ptrArr = new int[num];

    for(int i = 0; i < num; i++){
        ptrArr[i] = i*2;
    }  

    for(int i = 0; i < num; i++){
        cout << "Arr[" << i << "]: " << ptrArr[i] << endl;
    }  


    // Giải phóng bộ nhớ
    delete ptr1, ptr2;  

    delete[] ptrArr;

    return 0;
}