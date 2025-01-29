#include <iostream>

using namespace std;

namespace A{
    char *name = (char*)"Van Tu";
    float point = 9.2;
    void display(){
        cout << "Name: " << name;
        cout << "  Point: " << point << endl;
    }
}

namespace B{
    char *name = (char*)"Thanh Tu";
    float point = 8.1;
    void display(){
        cout << "Name: " << name;
        cout << "  Point: " << point << endl;
    }
}

int main(int argc, char const *argv[])
{
    cout << "Name: " << A::name << endl;
    cout << "Name: " << B::name << endl;
    cout << endl;
    A::display();
    B::display();
    return 0;
}


