#include <iostream>
using namespace std;

class HinhChuNhat {

public:
    double chieuDai;
    double chieuRong;
    
    static int var;
};

int HinhChuNhat::var;

int main()
{
    HinhChuNhat hinh1;
    HinhChuNhat hinh2;
    HinhChuNhat hinh3;

    HinhChuNhat::var = 2;

    cout << "address of chieu dai: " << &hinh1.chieuDai << '\n'; 
    cout << "address of chieu dai: " << &hinh2.chieuDai << '\n'; 
    cout << "address of chieu dai: " << &hinh3.chieuDai << endl << endl; 

    cout << "address of var hinh1: " << &hinh1.var << '\n'; 
    cout << "address of var hinh2: " << &hinh2.var << '\n'; 
    cout << "address of var hinh3: " << &hinh3.var << endl << endl; 


    cout << "value of var hinh1: " << hinh1.var << '\n'; 
    cout << "value of var hinh2: " << hinh2.var << '\n'; 
    cout << "value of var hinh3: " << hinh3.var << endl << endl; 

    hinh1.var = 3;

    cout << "value of var hinh1: " << hinh1.var << '\n'; 
    cout << "value of var hinh2: " << hinh2.var << '\n'; 
    cout << "value of var hinh3: " << hinh3.var << endl << endl; 

    return 0;
}
